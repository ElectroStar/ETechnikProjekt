//============================================================================
// Datei	: player.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef PLAYER_H
#define PLAYER_H

#include <QMutex>
#include <QThread>
#include <QImage>
#include <QWaitCondition>
#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>


/** Klasse zum Abspielen des Videostreams.
 *  @author		Eric
 *  @date		12.02.2015
 */
class Player {

public:

    /** Konstruktor.
    */
    Player();

    /** Destruktor.
    */
    ~Player();

protected:

    bool stopStream;
    QMutex mutex;
    QWaitCondition condition;
    cv::Mat frame;
    QImage img;

signals:
     void processedImage(const QImage &image);

public:

     /** Methode zum Anhalten des Streams.
     */
     void stop();

     /** Methode zur Statusabfrage.
     * 	@return     Gestartet/Gestoppt
     */
     bool isStopped() const;
};

#endif // PLAYER_H
