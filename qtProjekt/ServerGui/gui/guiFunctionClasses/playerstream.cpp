#include <QLabel>
#include "playerstream.h"

PlayerStream::PlayerStream(QObject *parent) : QThread(parent), mode(Idle) {
    stopStream = true;

    undist.readParam(cameraParmFile);
    fieldLoc = FieldLocator(LocatableObject(TRIANGLE, 0, 127, 10), LocatableObject(TRIANGLE, 128, 255, 10));
    ips = new ObjectLocator();

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
        start(HighestPriority);
    }
}


int PlayerStream::getMode() const {
    return mode;
}

void PlayerStream::setMode(const int value) {
    mode = (Mode)value;
}
void PlayerStream::run() {

    Mat undistorted, cropped;
    vector<LocatedObject> result;
    int delay = (1000/frameRate);

    while(!stopStream) {

        switch(mode) {

        case Idle:

            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);

            Converter::convertMatToQImage(undistorted,img);
            emit processedImage(img);

            break;

        case FindLandMark:

            foundLandMarks(false);

            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);

            boundaries = fieldLoc.locateField(undistorted);
            for (size_t i = 0; i < boundaries.size(); i++){
                circle(undistorted, boundaries[i], undistorted.cols/100, Scalar(0, 0, 255));
                circle(undistorted, boundaries[i], undistorted.cols/150, Scalar(0, 255, 0),-1);
            }

            if (boundaries.size() == 2){
                mode = FoundLandMark;
            }

            Converter::convertMatToQImage(undistorted,img);
            emit processedImage(img);

            break;

        case FoundLandMark:

            foundLandMarks(true);


            break;

        case Tracking:


            if (!capture.read(frame)) {
                stopStream = true;
            }

            undist.filter(frame, undistorted);


            cropFView.setFirst(boundaries[0]);
            cropFView.setSecond(boundaries[1]);

            cropFView.filter(undistorted,cropped);


            result = ips->getAllObjects(cropped, LocatableObject(RECTANGLE, 0, 128, 10));

            for (int i = 0; i < result.size(); i++){
                circle(cropped, result[i].position, cropped.cols/100, Scalar(0, 0, 255), -1);
                circle(cropped, result[i].position, cropped.cols/150, Scalar(255, 0, 0), -1);
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
