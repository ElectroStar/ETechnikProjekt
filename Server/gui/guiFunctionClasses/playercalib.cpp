//============================================================================
// Datei	: playercalib.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "playercalib.h"

PlayerCalib::PlayerCalib(QObject *parent) : QThread(parent), picCnt(0), takePic(false), mode(Init) {

    calibrator = new Calibrator();
    stopStream = true;
}

PlayerCalib::~PlayerCalib() {

    mutex.lock();
    stopStream = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

bool PlayerCalib::loadVideo(string filename) {

    capture.open(filename);

    if (capture.isOpened()) {
        frameRate = (int) capture.get(CV_CAP_PROP_FPS);
        return true;
    }
    else return false;
}

void PlayerCalib::play() {

    if (!isRunning()) {

        if (isStopped()){
            stopStream = false;
        }
        start(HighPriority);
    }
}

void PlayerCalib::run() {

    int delay = (1000/frameRate);

    while(!stopStream) {

        //Statemachine
        switch(mode) {

        case Init:
            calibrator->reset();

            picCnt = 0;
            picCntSend(picCnt);

            mode = TakePicture;
            takePic = false;
            break;

        case TakePicture:

            if (!capture.read(frame)) {
                stopStream = true;
            }

            if(takePic) {

                calibrator->takePicture(frame);
                takePic=false;
                picCnt++;
                picCntSend(picCnt);
            }
            break;

        case Calib:

            if(picCnt > 0) {
                frame = calibrator->getImgAt(picCnt-1);
                calibrator->process(frame);
                picCnt--;
            }
            else {
                try {
                    calibrator->start();
                    mode = Finished;
                }

                catch (cv::Exception& e) {
                    mode=Error;
                }
            }
            break;

        case Finished:

            emit sendCalibStatus(calibrator->getImagePointsSize());
            stopStream = true;
            break;

        case Error:
            stopStream = true;
            emit sendCalibStatus(false);
            break;
        }

        //Konvertierung und Uebertragung an Oberflaeche
        Converter::convertMatToQImage(frame,img);
        emit processedImage(img);
        this->msleep(delay);
    }
}

void PlayerCalib::msleep(int ms) {

    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}


bool PlayerCalib::getTakePic() const {
    return takePic;
}

void PlayerCalib::setTakePic(bool value) {
    takePic = value;
}

int PlayerCalib::getMode() const {
    return mode;
}

void PlayerCalib::setMode(int value) {
    mode = (Mode)value;
}

int PlayerCalib::getPicCnt() const {
    return picCnt;
}

void PlayerCalib::setPicCnt(int value) {
    picCnt = value;
}
