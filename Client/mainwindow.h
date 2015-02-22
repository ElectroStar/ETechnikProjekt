//============================================================================
// Datei	: mainwindow.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QString>
#include <fstream>
#include <iostream>
#include <iomanip>

#include "posdata.h"
#include "imageupdater.h"
#include "infoeagleeyedialog.h"
#include "showimagedialog.h"
#include "positioningreceiver.h"
#include "posdata.h"


namespace Ui {
class MainWindow;
}

/** Hauptoberflaeche fuer den Client
 *  @author		Eric Buschermoehle
 *  @date		22.02.2015
 */
class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    /** Konstruktor.
    */
    explicit MainWindow(QWidget *parent = 0);

    /**
    * Destruktor
    */
    ~MainWindow();

private slots:

    /** Slot zum anzeigen der aktuellen Position
    *  	@param[in] data		aktuelle Objektposition
    */
    void NewPosition(PosData *data);

    /** Slot zum starten Positionsanzeige
    */
    void on_cmd_start_clicked();

    /** Slot zum beenden des Clients
    */
    void on_cmd_ende_clicked();

    /** Slot zum starten des Informationsfensters
    */
    void on_actionUeber_Eagle_Eye_triggered();

    /** Slot zum starten der Grafischen Positionsanzeige
    */
    void on_showModelButton_clicked();

private:

    PositioningReceiver* positionReceiver;
    ShowImageDialog* showImageDialog;
    Ui::MainWindow *ui;

    int maxSizeTable;
    int currentSizeTable;

    std::ofstream file;
};

#endif // MAINWINDOW_H
