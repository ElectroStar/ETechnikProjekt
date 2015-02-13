#include "playercalib.h"

PlayerCalib::PlayerCalib(QObject *parent) : QThread(parent), picCnt(0), mode(Init), takePic(false)  {

    stopStream = true;
    calibrator = new Calibrator();

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

int PlayerCalib::getPicCnt() const
{
    return picCnt;
}

void PlayerCalib::setPicCnt(int value)
{
    picCnt = value;
}
void PlayerCalib::run() {

    int delay = (1000/frameRate);

    while(!stopStream) {

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

                calibrator->start();
                mode = Finished;

            }
            break;

        case Finished:

            stopStream = true;
            break;
        }

        Converter::convertMatToQImage(frame,img);
        emit processedImage(img);
        this->msleep(delay);
    }
}

PlayerCalib::~PlayerCalib() {

    mutex.lock();
    stopStream = true;
    capture.release();
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void PlayerCalib::msleep(int ms) {

    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}


Settings PlayerCalib::getSettings() const{

    return calibrator->getS();
}

