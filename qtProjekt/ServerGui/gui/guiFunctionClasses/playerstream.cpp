
#include "playerstream.h"
#include "model/Transmitter/ConnectionException.h"
#include "model/Transmitter/TransmittingException.h"

#include <iostream>

PlayerStream::PlayerStream(QObject *parent) : QThread(parent),  mpt(NULL), tm(NULL), send(false), mode(Init) {

    stopStream = true;

    ips = new ObjectLocator();
    fieldLoc = FieldLocator(ips);

    tm = NULL;

}

bool PlayerStream::loadVideo(string filename) {

    capture.open(filename);

    if (capture.isOpened()) {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else return false;
}

void PlayerStream::play() {

    if (!isRunning()) {

        if (isStopped()){
            stopStream = false;
        }
        start(HighPriority);
    }
}

int PlayerStream::getMode() const {
    return mode;
}

void PlayerStream::setMode(const int value) {
    mode = (Mode)value;
}


bool PlayerStream::getSend() const {
    return send;
}

void PlayerStream::setSend(bool value) {
    send = value;
}

void PlayerStream::run() {

    Mat undistorted, cropped;
    vector<LocatedObject> result;
    int delay = (1000/frameRate);

    while(!stopStream) {

        if(mode == Init){

            init();
            mode = Idle;
        }

        else if(mode == Idle){

            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);

            Converter::convertMatToQImage(undistorted,img);
            emit processedImage(img);

         }

        else if(mode == FindLandMark){

            emit foundLandMarks(false);

            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);

            LocatableObject originTemp((Form) Settings::instance().landMarkShapeOrigin, Settings::instance().landMarkColorOriginMin,Settings::instance().landMarkColorOriginMax, Settings::instance().landMarkSizeOrigin);
            LocatableObject referenceTemp((Form) Settings::instance().landMarkShapeReference, Settings::instance().landMarkColorReferenceMin,Settings::instance().landMarkColorReferenceMax, Settings::instance().landMarkSizeReference);

            boundaries = fieldLoc.locateField(undistorted,originTemp,referenceTemp);


            for (size_t i = 0; i < boundaries.size(); i++){
                circle(undistorted, boundaries[i].position, boundaries[i].edgeLengthPx, Scalar(0, 0, 255),-1);
                circle(undistorted, boundaries[i].position,  boundaries[i].edgeLengthPx/2, Scalar(0, 255, 0),-1);
            }

            if (boundaries.size() == 2){
                mode = FoundLandMark;
            }

            Converter::convertMatToQImage(undistorted,img);
            emit processedImage(img);

        }

        else if(mode == FoundLandMark){
            emit foundLandMarks(true);
         }

        else if(mode == Tracking){

            LocatableObject objectTemp((Form) Settings::instance().objectShape, Settings::instance().objectColorMin,
                                                                             Settings::instance().objectColorMax, Settings::instance().objectSizeCM);
            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);


            cropFView.setFirst(boundaries[0].position);
            cropFView.setSecond(boundaries[1].position);

            cropFView.filter(undistorted,cropped);

            result = ips->getAllObjects(cropped, objectTemp);

            for (size_t i = 0; i < result.size(); i++){
                circle(cropped, result[i].position, boundaries[i].edgeLengthPx, Scalar(0, 0, 255), -1);
                circle(cropped, result[i].position, boundaries[i].edgeLengthPx/2, Scalar(255, 0, 0), -1);
            }

            if(result.size()==0){

                emit newCord(QString(""), QString(""));
            }
            else {


                if(boundaries[0].position.x < boundaries[1].position.x) {
                    result[0].position.x+=boundaries[0].position.x;
                }
                else {
                    result[0].position.x+=boundaries[1].position.x;
                }

                if(boundaries[0].position.y < boundaries[1].position.y) {
                    result[0].position.y+=boundaries[0].position.y;
                }
                else {
                     result[0].position.y+=boundaries[1].position.y;
                }

                Mat temp = mpt->transform(boundaries[0],result[0]);
                double x = temp.at<double>(0,0)/10;
                double y = temp.at<double>(1,0)/10;
                double z = temp.at<double>(2,0)/10;

                Mat temp2 = mpt->transform(boundaries[0], boundaries[1]);
                double x2 = temp2.at<double>(0,0)/10;
                double y2 = temp2.at<double>(1,0)/10;

                if( x2 < 0)
                    x2 *= -1;
                if( y2 < 0)
                    y2 *= -1;

                PosData* pos = new PosData();
                pos->setX(x);
                pos->setY(y);
                pos->setZ(z);
                pos->setX2(x2);
                pos->setY2(y2);

                if(send) {
                    if(tm == NULL) {
                        try {
                            tm = new Transmitter("127.0.0.1", 50728);
                            tm->transmit(*pos);
                        } catch (ConnectionException& e) {

                        } catch (TransmittingException& e) {
                            if(tm != NULL)
                            delete tm;

                            tm = NULL;
                        }
                    } else
                        tm->transmit(*pos);

                    delete pos;
                }

                emit newCord(QString().setNum((int)x) + QString(" cm"), QString().setNum((int)y)+ QString(" cm"));
            }

            Converter::convertMatToQImage(cropped,img);
            emit processedImage(img);
        }
        this->msleep(delay);
    }
}

PlayerStream::~PlayerStream() {

    mutex.lock();
    stopStream = true;
    capture.release();
    condition.wakeOne();
    delete ips;
    delete mpt;
    delete tm;
    mutex.unlock();

    wait();
}

void PlayerStream::msleep(int ms) {

    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

QImage PlayerStream::getCurrentImage() const {
    return img;
}

void PlayerStream::init(){

    delete mpt;
    mpt = new MetricPositionTransformator(cameraParmFile,Settings::instance().calibPanelHeightMM);
    undist.readParam(cameraParmFile);

}

int PlayerStream::getImageHeight()  {
    return capture.get(CV_CAP_PROP_FRAME_HEIGHT);
}

int PlayerStream::getImageWidth()  {
    return capture.get(CV_CAP_PROP_FRAME_WIDTH);
}
