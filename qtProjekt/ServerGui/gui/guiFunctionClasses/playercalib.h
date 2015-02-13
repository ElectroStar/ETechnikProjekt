#ifndef PLAYERCALIB_H
#define PLAYERCALIB_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "converter.h"
#include "player.h"
#include "model/Calibrator/Calibrator.h"

using namespace cv;

enum Mode {
    TakePicture = 0,
    Calib = 1,
    Finished = 2,
    Init = 3
};

class PlayerCalib : public QThread, public Player {

    Q_OBJECT

private:

    int frameRate;

    VideoCapture capture;
    Calibrator* calibrator;

    int picCnt;
    Mode mode;
    bool takePic;

signals:
      void processedImage(const QImage &image);
      void picCntSend(int i);

protected:
     void run();
     void msleep(int ms);

public:

    PlayerCalib(QObject *parent = 0);
    ~PlayerCalib();
    bool loadVideo(string filename);
    void play();

    Settings getSettings() const;

    bool getTakePic() const;
    void setTakePic(bool value);

    int getMode() const;
    void setMode(int value);

    int getPicCnt() const;
    void setPicCnt(int value);

};

#endif // PLAYERCALIB_H
