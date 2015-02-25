//============================================================================
// Datei	: mainwindow.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <iostream>

#include "gui/guiFunctionClasses/playerstream.h"
#include "cameracalibrationdialog.h"
#include "errordialog.h"
#include "infoeagleeyedialog.h"
#include "gui/settingsdialog.h"

namespace Ui {
class MainWindow;
}

/** Klasse fuer die zentrale Oberflaeche.
 *  @author		Eric
 *  @date		15.02.2015
 */
class MainWindow : public QMainWindow {

    Q_OBJECT

public:


    /** Konstruktor.
    */
    explicit MainWindow(QWidget *parent = 0);

    /** Destruktor.
    */
    ~MainWindow();

    /** Methode zum Verbinden mit dem Videostream.
    *   @return       Erfolgreich/N-Erfolgreich
    */
    bool connectWithStream();

    /** Getter fuer das Paramter-Gefunden-Flag.
    *   @return       Erfolgreich/N-Erfolgreich
    */
    bool getFoundConfig() const;

    /** Setter fuer  das Paramter-Gefunden-Flag.
    *  	@param[in] value 	Erfolgreich/N-Erfolgreich
    */
    void setFoundConfig(bool value);

    /** Getter fuer das Kalibrierdatei-Gefunden-Flag.
    * @return       Erfolgreich/N-Erfolgreich
    */
    bool getFoundCalib() const;

    /** Setter fuer das Kalibrierdatei-Gefunden-Flag.
    *  	@param[in] value 	Erfolgreich/N-Erfolgreich
    */
    void setFoundCalib(bool value);

private slots:

    /** Actionhandler zum Aktualisieren der Anzeige.
    *  @param[in] img       Aktuelles Bild
    */
    void updatePlayerStream(QImage img);

    /** Actionhandler zum Aktualisieren des Tracking-Buttons
    *  @param[in] flag       Freischalten/Blockieren
    */
    void updateTrackingButton(bool flag);

    /** Actionhandler zum Aktualisieren der Positionsanzeige.
    *  @param[in] posX       X-Koordinate
    *  @param[in] posY       Y-Koordinate
    */
    void updatePosLabel(const QString posX, const QString posY);

    /** Actionhandler bei Klick auf 'Starte Stream'.
    */
    void on_buttonStarteStream_clicked();

    /** Actionhandler bei Klick auf 'Kamerakalibirerung'.
    */
    void on_actionKamerakalibrierung_triggered();

    /** Actionhandler bei Klick auf 'Info'.
    */
    void on_action_ber_EagleEye_triggered();

    /** Actionhandler bei Klick auf 'Finde Landmarken'.
    */
    void on_buttonFindLandMark_clicked();

    /** Actionhandler bei Klick auf 'Starte Tracking'.
    */
    void on_buttonStartTracking_clicked();

    /** Actionhandler zum Aktualisieren der Senden-Checkbox.
    *  @param[in] checked       Aktiv/Inaktiv
    */
    void on_checkBoxSend_clicked(bool checked);

    /** Actionhandler bei Klick auf 'Einstellungen'.
    */
    void on_actionIP_EInstellungen_triggered();

private:
    bool foundConfig;
    bool foundCalib;
    Ui::MainWindow *ui;
    PlayerStream* myPlayer;

};
#endif // MAINWINDOW_H
