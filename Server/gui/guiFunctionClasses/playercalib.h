//============================================================================
// Datei	: playercalib.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef PLAYERCALIB_H
#define PLAYERCALIB_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "converter.h"
#include "player.h"
#include "model/Calibrator/Calibrator.h"
#include "Settings.h"

using namespace cv;

/** Klasse zum Abspielen des Videostreams im Kalibriermodus.
 *  @author		Eric
 *  @date		12.02.2015
 */
class PlayerCalib : public QThread, public Player {

    Q_OBJECT

private:

    int frameRate;
    VideoCapture capture;
    Calibrator* calibrator;
    int picCnt;
    bool takePic;

public:
    enum Mode {
        TakePicture,
        Calib,
        Finished,
        Init,
        Error
    };

     Mode mode;

signals:
      void processedImage(const QImage &image);
      void picCntSend(int i);
      void sendCalibStatus(const int value);
      void progressBar(const int value);

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
    PlayerCalib(QObject *parent = 0);

    /** Destruktor.
    */
    ~PlayerCalib();

    /** Methode zum Oeffnen des Videocapture.
    *  @param[in] filename  Adresse Netzwerkstream
    */
    bool loadVideo(string filename);

    /** Methode zum Starten des Threads.
    */
    void play();

    /** Getter fuer den Ausloeser.
    * @return    Status 1/0
    */
    bool getTakePic() const;

    /** Setter fuer den Ausloeser.
    *  	@param[in] value 	Status 1/0
    */
    void setTakePic(bool value);

    /** Getter fuer den aktuellen Modus.
    * @return    Modus der Statemachine
    */
    int getMode() const;

    /** Setter fuer den Modus.
    *  	@param[in] value 	Modus der Statemachine
    */
    void setMode(int value);

    /** Getter fuer die Anzahl der Aufnahmen.
    * @return    Zaehler Bilder
    */
    int getPicCnt() const;

    /** Setter fuer die Anzahl der Bilder.
    *  	@param[in] value 	Zaehler Bilder
    */
    void setPicCnt(int value);

};

#endif // PLAYERCALIB_H
