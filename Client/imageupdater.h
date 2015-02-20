#ifndef IMAGEUPDATER_H
#define IMAGEUPDATER_H

#include <QObject>
#include <QThread>
#include <QtNetwork/QUdpSocket>
#include <opencv2/core/core.hpp>

#include "positioningreceiver.h"
#include "posdata.h"
#include "guifunctionclasses/ModelCreator.h"
#include "guifunctionclasses/converter.h"

class ImageUpdater : public QObject
{
    Q_OBJECT
public:

    ModelCreator *modelCreator;
    ImageUpdater(QObject *parent = 0);
    ~ImageUpdater();


signals:
    void processedImage(const QImage &image, PosData* data);

private slots:

    void NewPosition(PosData*);

private:

    QImage img;
};

#endif // IMAGEUPDATER_H
