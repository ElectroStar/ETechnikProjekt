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
    /**
     * Konsturktor
     * @param parent Vaterobjekt
     */
    explicit PositioningReceiver(QObject *parent = 0);
    /**
     * Dekonsturktor
     */
    ~PositioningReceiver();
private:
    QUdpSocket* socket;
    qint32 var;
signals:
   /**
    * Signal wenn ein neues Positionspaket eingetroffen ist
    * @param pos Positionsdaten
    */
   void newPosition(PosData* pos);
private slots:
   /**
    * Verarbeitet eingehende UDP-Datagrams
    */
   void processPendingDatagrams();
public slots:
};

#endif // POSITIONINGRECEIVER_H
