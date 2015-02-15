#include "playertracking.h"


PlayerTracking::PlayerTracking(QObject *parent) : QThread(parent) {
    stopStream = true;
}

void PlayerTracking::play() {

    if (!isRunning()) {

        if (isStopped()){
            stopStream = false;
        }
        start(LowPriority);
    }
}

void PlayerTracking::run() {
    int delay = 1000;
    while(!stopStream){

        Converter::convertMatToQImage(frame,img);
        emit processedImage(img);
        this->msleep(delay);
    }
}

PlayerTracking::~PlayerTracking() {

    mutex.lock();
    stopStream = true;
    condition.wakeOne();
    mutex.unlock();
    wait();
}

void PlayerTracking::msleep(int ms) {

    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

void PlayerTracking::createNewBlackImage() {
    frame = Mat::zeros(imageHeight, imageWidth, CV_8UC3);
    circle( frame ,Point(640,360),200,Scalar( 255, 255, 255 ),2,1);
}

void PlayerTracking::setImageHeight(uint32_t _imageHeight) {
    imageHeight=_imageHeight;
}

void PlayerTracking::setImageWidth(uint32_t _imageWidth) {
    imageWidth=_imageWidth;
}
