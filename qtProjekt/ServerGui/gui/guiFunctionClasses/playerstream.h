#ifndef PLAYERSTREAM_H
#define PLAYERSTREAM_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "converter.h"

using namespace cv;
class PlayerStream : public QThread {

    Q_OBJECT
 private:

    bool stopStream;
    QMutex mutex;
    QWaitCondition condition;
    Mat frame;
    int frameRate;
    VideoCapture capture;
    QImage img;

 signals:
      void processedImage(const QImage &image);

 protected:
     void run();
     void msleep(int ms);

 public:

    PlayerStream(QObject *parent = 0);
    ~PlayerStream();
    bool loadVideo(string filename);
    void play();
    void stop();
    bool isStopped() const;

    QImage getCurrentImage() const;

    int getImageHeight();
    int getImageWidth();
};
#endif
