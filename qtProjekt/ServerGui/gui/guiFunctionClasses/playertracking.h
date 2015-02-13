#ifndef PLAYERTRACKING_H
#define PLAYERTRACKING_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "converter.h"
#include "player.h"
#include <stdint.h>

using namespace cv;
class PlayerTracking : public QThread, public Player {

    Q_OBJECT

 private:

    uint32_t imageHeight;
    uint32_t imageWidth;

 signals:
      void processedImage(const QImage &image);

 protected:
     void run();
     void msleep(int ms);

 public:

    PlayerTracking(QObject *parent = 0);
    ~PlayerTracking();
    void play();

    void setImageHeight(uint32_t _imageHeight);
    void setImageWidth(uint32_t _imageWidth);

    void createNewBlackImage();

};

#endif // PLAYERTRACKING_H
