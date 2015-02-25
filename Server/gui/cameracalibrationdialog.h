//============================================================================
// Datei	: cameracalibrationdialog.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef CAMERACALIBRATIONDIALOG_H
#define CAMERACALIBRATIONDIALOG_H

#include <QDialog>
#include <stdio.h>

#include "guiFunctionClasses/playercalib.h"
#include "gui/errordialog.h"
#include "Settings.h"

namespace Ui {
class cameraCalibrationDialog;
}

/** Klasse fuer die Oberflaeche des Kalibrierprogramms.
 *  @author		Eric
 *  @date		12.02.2015
 */
class cameraCalibrationDialog : public QDialog {
    Q_OBJECT

public:

    /** Konstruktor.
    */
    explicit cameraCalibrationDialog(QWidget *parent = 0);

    /** Destruktor.
    */
    ~cameraCalibrationDialog();

    /** Getter fuer den Kalibrierstatus.
    * @return       Erfolgreich/N-Erfolgreich
    */
    bool getCalibSuccess() const;

    /** Setter fuer den Kalibrierstatus.
    *  	@param[in] value 	Erfolgreich/N-Erfolgreich
    */
    void setCalibSuccess(bool value);

private slots:

    /** Actionhandler zum Aktualisieren der Anzeige.
    *  @param[in] img       Aktuelles Bild
    */
    void updatePlayerStream(QImage img);

    /** Actionhandler zum Anzeigen des Kalibrierergebnisses.
    *  @param[in] e         Erfolgreich/N-Erfolgreich
    */
    void updateCalibSuccess(int e);

    /** Actionhandler zum Aufnehmen von Bildern.
    */
    void on_buttonTakePicture_clicked();

    /** Actionhandler zum Starten der Kalibrierung.
    */
    void on_buttonStartCalib_2_clicked();

    /** Actionhandler zum Starten des Videostreams.
    */
    void on_buttonStartStream_clicked();

    /** Actionhandler zur Anzeige des Bildzaehlers.
    *  @param[in] i         Anzahl
    */
    void setCntShowlabel(int _i);

    /** Actionhandler bei OK.
    */
    void on_buttonBox_rejected();

    /** Actionhandler bei Cancel.
    */
    void on_buttonBox_accepted();

private:

    bool calibSuccess;
    Ui::cameraCalibrationDialog *ui;
    PlayerCalib* myPlayer;
};

#endif // CAMERACALIBRATIONDIALOG_H
