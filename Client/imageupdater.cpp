#include "imageupdater.h"
#include "mainwindow.h"

ImageUpdater::ImageUpdater(QObject *parent) : QObject(parent) {

    modelCreator = new ModelCreator(1280);
}

ImageUpdater::~ImageUpdater() {

}

void ImageUpdater::NewPosition(PosData* data) {

    if(!(modelCreator==NULL)){

    Point temp = modelCreator->calcPosition(data->getX(), data->getY(), data->getMaxX(), data->getMaxY());
    modelCreator->drawPosition(temp);

    Converter::convertMatToQImage(modelCreator->getModel(),img);
    emit processedImage(img);

    }
}




