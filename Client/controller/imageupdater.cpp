//============================================================================
// Datei	: imageupdater.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "imageupdater.h"
#include "gui/mainwindow.h"

ImageUpdater::ImageUpdater(QObject *parent) : QObject(parent), showDistanze(false), line(NULL) {

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

        if(showDistanze) {
            double temp = line->calcDistance(data->getX(), data->getY());
            emit sendDistance(temp);
        }
    }
}

void ImageUpdater::drawNewLine(int x1, int y1, int x2, int y2) {

    Point p1 = modelCreator->calcNewPositionWithoutUpdate(x1,y1);
    Point p2 = modelCreator->calcNewPositionWithoutUpdate(x2,y2);

    if (p1.x >= modelCreator->getPixelFieldWidth() || p2.x >= modelCreator->getPixelFieldWidth() || p1.x < 0 || p2.x < 0
            || p1.y >= modelCreator->getPixelFieldHeight() || p2.y >= modelCreator->getPixelFieldHeight() || p1.y < 0 || p2.y <0) {

        showDistanze = false;
        emit validData(false);
    }

    else {
        delete line;
        line = new Line(x1,y1,x2,y2);

        modelCreator->drawLine(p1,p2);
        showDistanze = true;
        emit validData(true);
    }
}




