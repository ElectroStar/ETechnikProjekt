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
void PlayerTracking::stop() {
    stopStream = true;
}

void PlayerTracking::msleep(int ms) {

    struct timespec ts = { ms / 1000, (ms % 1000) * 1000 * 1000 };
    nanosleep(&ts, NULL);
}

bool PlayerTracking::isStopped() const {
    return this->stopStream;
}

void PlayerTracking::createNewBlackImage() {
    frame = Mat::zeros(imageHeight, imageWidth, CV_8UC3);

    line(frame, Point(imageWidth/2, 0), Point(imageWidth/2, imageHeight), Scalar( 255, 255, 255 ),0.1,1);
    line(frame, Point(0, imageHeight-1), Point(imageWidth, imageHeight-1), Scalar( 255, 255, 255 ),0.1,1);

    const uint32_t step = 50;

    for(int32_t i = imageHeight /10; i >= 0; i--) {

        line(frame, Point(imageWidth/2-5, i*step), Point(imageWidth/2+5, i*step), Scalar( 255, 255, 255 ),0.1,1);
    }
}

void PlayerTracking::setImageHeight(uint32_t _imageHeight) {
    imageHeight=_imageHeight;
}

void PlayerTracking::setImageWidth(uint32_t _imageWidth) {
    imageWidth=_imageWidth;
}
