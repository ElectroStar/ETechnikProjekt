//============================================================================
// Datei	: playerstream.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

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
#include "model/Transmitter/PosData.h"

using namespace cv;

/** Klasse zum Abspielen des Videostreams im Hauptfenster.
 *  @author		Eric
 *  @date		12.02.2015
 */
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


      /** Hauptfunktion des Threads (Statemachine).
      */
     void run();

     /** Methode zum Schlafenlegen des Threads.
     *  @param[in] ms       Millisekunden
     */
     void msleep(int ms);

public:

     /** Konstruktor.
     */
    PlayerStream(QObject *parent = 0);

    /** Destruktor.
    */
    ~PlayerStream();

    /** Methode zum Oeffnen des Videocapture.
    *  @param[in] filename  Adresse Netzwerkstream
    */
    bool loadVideo(string filename);

    /** Methode zum Starten des Threads.
    */
    void play();

    /** Getter fuer das aktuelle QImage.
    * @return       QImage
    */
    QImage getCurrentImage() const;

    /** Methode zum Initialisieren der noetigen Komponenten.
    */
    void init();

    /** Getter fuer die Bildhoehe.
    * @return       Hoehe in Px
    */
    int getImageHeight();

    /** Getter fuer die Bildbreite.
    * @return       Breite in PX
    */
    int getImageWidth();

    /** Getter fuer den aktuellen Modus
    * @return       Status der Statemachine
    */
    int getMode() const;

    /** Setter fuer den aktuellen Modus.
    *  	@param[in] value 	Status der Statemachine
    */
    void setMode(const int value);

    /** Getter fuer das Send-Flag.
    * @return       Aktiv/Inaktiv
    */
    bool getSend() const;

    /** Setter fuer das Send-Flag.
    *  	@param[in] value 	Aktiv/Inaktiv
    */
    void setSend(bool value);
};
#endif
