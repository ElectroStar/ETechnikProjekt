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
#include "player.h"

using namespace cv;
class PlayerStream : public QThread, public Player {

    Q_OBJECT

private:

    int frameRate;
    VideoCapture capture;

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

    QImage getCurrentImage() const;

    int getImageHeight();
    int getImageWidth();
};
#endif
