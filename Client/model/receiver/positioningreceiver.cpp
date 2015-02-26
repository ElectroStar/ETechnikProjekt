#include "positioningreceiver.h"
#include <QtNetwork/QUdpSocket>

PositioningReceiver::PositioningReceiver(QObject *parent) : QObject(parent)
{
    //qDebug()<<"Create in thread: "<<QThread::currentThreadId();
    socket = new QUdpSocket(this);
    socket->bind(50729, QUdpSocket::ShareAddress);
    var = 0;
    connect(socket, SIGNAL(readyRead()), this, SLOT(processPendingDatagrams()));
}

PositioningReceiver::~PositioningReceiver()
{

}

void PositioningReceiver::processPendingDatagrams() {
    //qDebug()<<"Processing Datagrams in thread: "<<QThread::currentThreadId();
    while (socket->hasPendingDatagrams()) {
        QByteArray datagram;
        datagram.resize(socket->pendingDatagramSize());
        socket->readDatagram(datagram.data(), datagram.size());
        //qDebug()<< (tr("Received datagram: \"%1\"").arg(datagram.data()));

        var++;
        PosData* data = new PosData();
        QString dataStr(datagram);

        qint32 startIndex = 0;
        qint32 searchIndex = dataStr.indexOf("$");
        if(searchIndex < 0)
            continue;

        // Alle Felder aus dem Datensatz exthrahieren
        bool error = false;
        qint32 numberOfElements = 9;
        for(qint32 i = 1; i <= numberOfElements; i++) {
            startIndex = searchIndex+1;
            // Beim letzten Element nach <CR><LF> suchen
            if(i == numberOfElements)
                searchIndex = dataStr.indexOf("\r\n", startIndex);
            else // Sonst nach einen Komma
                searchIndex = dataStr.indexOf(",", startIndex);

            if(searchIndex < 0) {
                error = true;
                break;
            }

            switch (i) {
            case 1:
                data->setX(dataStr.mid(startIndex, searchIndex-startIndex).toDouble());
                break;
            case 2:
                data->setY(dataStr.mid(startIndex, searchIndex-startIndex).toDouble());
                break;
            case 3:
                data->setZ(dataStr.mid(startIndex, searchIndex-startIndex).toDouble());
                break;
            case 4:
                data->setError(dataStr.mid(startIndex, searchIndex-startIndex).toDouble());
                break;
            case 5:
                data->setMarker(dataStr.mid(startIndex, searchIndex-startIndex));
                break;
            case 6:
                data->setMaxX(dataStr.mid(startIndex, searchIndex-startIndex).toDouble());
                break;
            case 7:
                data->setMaxY(dataStr.mid(startIndex, searchIndex-startIndex).toDouble());
                break;
            case 8:
                data->setCoefficient(dataStr.mid(startIndex, searchIndex-startIndex).toDouble());
                break;
            case 9:
                data->setDate(dataStr.mid(startIndex, searchIndex-startIndex).toDouble());
                break;
            default:
                break;
            }
        }

        if(error)
            continue;

        emit newPosition(data);
    }
}
