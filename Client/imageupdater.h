//============================================================================
// Datei	: imageupdater.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

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
#include "guifunctionclasses/line.h"

/** Klasse um Position des Objekts in Fenster anzuzeigen.
 *  @author		Eric
 *  @date		22.02.2015
 */
class ImageUpdater : public QObject
{
    Q_OBJECT
public:

    /** Konstruktor.
    */
    ImageUpdater(QObject *parent = 0);

    /** Destruktor.
    */
    ~ImageUpdater();

     ModelCreator *modelCreator;

signals:
    void processedImage(const QImage &image);
    void sendDistance(double d);
    void validData(bool valid);

private slots:

    /** Methode zur Lokalisierung Objekten eines bestimmbaren Typs.
    *  	@param[in] _posData			Neue Position
    */
    void NewPosition(PosData*);
    void drawNewLine(int x1, int y1, int x2, int y2);

private:

    QImage img;
    bool showDistanze;
    Line *line;
};

#endif // IMAGEUPDATER_H
