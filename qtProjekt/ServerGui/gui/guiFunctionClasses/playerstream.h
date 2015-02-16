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
#include "config.h"

#include "model/PositionService/IPositionService.h"
#include "model/PositionService/LocatableObject.h"
#include "model/PositionService/LocatedObject.h"
#include "model/PositionService/ObjectLocator.h"
#include "model/Filters/CropFieldView.h"
#include "model/Filters/Undistorter.h"
#include "model/FieldLocator/FieldLocator.h"


using namespace cv;
class PlayerStream : public QThread, public Player {

    Q_OBJECT

private:

    int frameRate;
    VideoCapture capture;

    Undistorter undist;
    FieldLocator fieldLoc;
    CropFieldView cropFView;
    IPositionService* ips;

    vector<Point> boundaries;


public:
    enum Mode {
        Idle,
        FindLandMark,
        FoundLandMark,
        Tracking
    };

     Mode mode;

signals:
      void processedImage(const QImage &image);
      void foundLandMarks(const bool flag);
      void newCord(const QString posX, const QString posY);

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

    int getMode() const;
    void setMode(const int value);
};
#endif
