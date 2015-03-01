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

#include "model/receiver/positioningreceiver.h"
#include "model/receiver/posdata.h"
#include "model/ModelCreator.h"
#include "model/converter.h"
#include "model/line.h"

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

    /** Slot zur Lokalisierung Objekten eines bestimmbaren Typs.
    *  	@param[in] _posData			Neue Position
    */
    void NewPosition(PosData*);

    /** Slot zum zeichnen einer Linie in die Graphische Oberflaeche.
    *  	@param[in] x1			Start x
    *   @param[in] y1			Start y
    *   @param[in] x2			Ende x
    *   @param[in] y1			Ende y
    */
    void drawNewLine(double x1, double y1, double x2, double y2);

private:

    QImage img;
    bool showDistanze;
    Line *line;
};

#endif // IMAGEUPDATER_H
