#ifndef PLAYER_H
#define PLAYER_H


#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


class Player {

public:
    Player();
    ~Player();
protected:

    bool stopStream;
    QMutex mutex;
    QWaitCondition condition;
    cv::Mat frame;
    QImage img;

signals:
     void processedImage(const QImage &image);

public:
     void stop();
     bool isStopped() const;
};

#endif // PLAYER_H
