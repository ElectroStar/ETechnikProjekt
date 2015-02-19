#include "imageupdater.h"

ImageUpdater::ImageUpdater(QObject *parent) : QObject(parent) {

    modelCreator = new ModelCreator(1280);
    // Thread erzeugen
    QThread* workerThread = new QThread();

    // Worker erzeugen
    PositioningReceiver* worker = new PositioningReceiver();

    //connect(newThread, SIGNAL(started()), obj, SLOT(doWork()));
    connect(worker, SIGNAL(newPosition(PosData*)), this, SLOT(NewPosition(PosData*)));
    worker->moveToThread(workerThread);

    workerThread->start();
}

ImageUpdater::~ImageUpdater() {

}

void ImageUpdater::NewPosition(PosData* data) {

    Point temp =modelCreator->calcPosition(data->getX(), data->getY(), data->getMaxX(), data->getMaxY());
    modelCreator->drawPosition(temp);

    Converter::convertMatToQImage(modelCreator->getModel(),img);
    emit processedImage(img,data);
}

