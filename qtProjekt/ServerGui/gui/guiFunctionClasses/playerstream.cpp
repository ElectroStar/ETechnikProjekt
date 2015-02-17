
#include "playerstream.h"

#include <iostream>

PlayerStream::PlayerStream(QObject *parent) : QThread(parent),  mpt(NULL), tm(NULL),send(false), mode(Idle) {

    init();
    stopStream = true;
    fieldLoc = FieldLocator(LocatableObject((Form)landMarkShapeOrigin, landMarkColorOriginMin, landMarkColorOriginMax, landMarkSizeOrigin),
                            LocatableObject((Form)landMarkShapeReference, landMarkColorReferenceMin, landMarkColorReferenceMax, landMarkSizeReference));

    ips = new ObjectLocator();

    //tm = new Transmitter("Adress", 3478);

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


bool PlayerStream::getSend() const
{
    return send;
}

void PlayerStream::setSend(bool value)
{
    send = value;
}
void PlayerStream::run() {

    Mat undistorted, cropped;
    vector<LocatedObject> result;
    int delay = (1000/frameRate);

    while(!stopStream) {

        switch(mode) {

        case Init:

            init();
            mode = Idle;

            break;

        case Idle:

            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);

            Converter::convertMatToQImage(undistorted,img);
            emit processedImage(img);

            break;

        case FindLandMark:

            emit foundLandMarks(false);

            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);

            boundaries = fieldLoc.locateField(undistorted);

            for (size_t i = 0; i < boundaries.size(); i++){
                circle(undistorted, boundaries[i].position, undistorted.cols/100, Scalar(0, 0, 255));
                circle(undistorted, boundaries[i].position, undistorted.cols/150, Scalar(0, 255, 0),-1);
            }

            if (boundaries.size() == 2){
                mode = FoundLandMark;
            }

            Converter::convertMatToQImage(undistorted,img);
            emit processedImage(img);

            break;

        case FoundLandMark:
            emit foundLandMarks(true);
            break;

        case Tracking:

            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);


            cropFView.setFirst(boundaries[0].position);
            cropFView.setSecond(boundaries[1].position);

            cropFView.filter(undistorted,cropped);


            result = ips->getAllObjects(cropped, LocatableObject((Form) objectShape, objectColorMin, objectColorMax, objectSizeCM));

            for (size_t i = 0; i < result.size(); i++){
                circle(cropped, result[i].position, cropped.cols/100, Scalar(0, 0, 255), -1);
                circle(cropped, result[i].position, cropped.cols/150, Scalar(255, 0, 0), -1);
            }

            if(result.size()==0){

                emit newCord(QString("-"), QString("-"));
            }
            else {


                Mat temp = mpt->transform(boundaries[0],result[0]);
                double x = temp.at<double>(0,0);
                double y = temp.at<double>(1,0);

                if(send) {
                    tm->transmit(Point2d(x,y));
                }

                emit newCord(QString().setNum(x), QString().setNum(y));
            }

            Converter::convertMatToQImage(cropped,img);
            emit processedImage(img);

            break;

        }

        this->msleep(delay);
    }
}

PlayerStream::~PlayerStream() {

    mutex.lock();
    stopStream = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();

    delete ips;
    delete mpt;
    delete tm;
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
    mpt = new MetricPositionTransformator(cameraParmFile,calibPanelHeightMM);
    undist.readParam(cameraParmFile);

}


int PlayerStream::getImageHeight()  {
    return capture.get(CV_CAP_PROP_FRAME_HEIGHT);
}
int PlayerStream::getImageWidth()  {
    return capture.get(CV_CAP_PROP_FRAME_WIDTH);
}
