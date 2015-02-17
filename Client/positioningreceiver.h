#ifndef POSITIONINGRECEIVER_H
#define POSITIONINGRECEIVER_H

#include <QObject>
#include <QThread>
#include <QtNetwork/QUdpSocket>
#include "posdata.h"

class PositioningReceiver : public QObject
{
    Q_OBJECT
public:
    explicit PositioningReceiver(QObject *parent = 0);
    ~PositioningReceiver();
private:
    QUdpSocket* socket;
    qint32 var;
signals:
   void newPosition(PosData*);
private slots:
   void processPendingDatagrams();
public slots:
};

#endif // POSITIONINGRECEIVER_H
