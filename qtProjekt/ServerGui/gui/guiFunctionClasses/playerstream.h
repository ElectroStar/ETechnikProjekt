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
#include "Settings.h"

#include "model/PositionService/IPositionService.h"
#include "model/PositionService/LocatableObject.h"
#include "model/PositionService/LocatedObject.h"
#include "model/PositionService/ObjectLocator.h"
#include "model/Filters/CropFieldView.h"
#include "model/Filters/Undistorter.h"
#include "model/FieldLocator/FieldLocator.h"
#include "model/PositionService/MetricPositionTransformator.h"
#include "model/Transmitter/Transmitter.h"


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
    MetricPositionTransformator* mpt;
    Transmitter* tm;

    vector<LocatedObject> boundaries;

    bool send;


public:
    enum Mode {
        Init,
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

    void init();
    int getImageHeight();
    int getImageWidth();

    int getMode() const;
    void setMode(const int value);
    bool getSend() const;
    void setSend(bool value);
};
#endif
