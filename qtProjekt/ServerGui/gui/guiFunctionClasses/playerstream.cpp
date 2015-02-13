
#include "playerstream.h"

PlayerStream::PlayerStream(QObject *parent) : QThread(parent) {
    stopStream = true;
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
        start(LowPriority);
    }
}

void PlayerStream::run() {

    int delay = (1000/frameRate);
    while(!stopStream) {

        if (!capture.read(frame)) {
            stopStream = true;
        }

        Converter::convertMatToQImage(frame,img);
        emit processedImage(img);
        this->msleep(delay);
    }
}

PlayerStream::~PlayerStream() {

    mutex.lock();
    stopStream = true;
    capture.release();
    condition.wakeOne();
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

int PlayerStream::getImageHeight()  {
    return capture.get(CV_CAP_PROP_FRAME_HEIGHT);
}
int PlayerStream::getImageWidth()  {
    return capture.get(CV_CAP_PROP_FRAME_WIDTH);
}
