#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QFileDialog>
#include <QMessageBox>
#include <QString>
#include <iostream>

#include "gui/guiFunctionClasses/playerstream.h"
#include "gui/guiFunctionClasses/playertracking.h"
#include "cameracalibrationdialog.h"
#include "errordialog.h"
#include "infoeagleeyedialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow {
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

    bool connectWithStream();

private slots:

    void updatePlayerStream(QImage img);
    void updateTrackingButton(bool flag);

    void on_buttonStarteStream_clicked();

    void on_actionKamerakalibrierung_triggered();
    void on_action_ber_EagleEye_triggered();

    void on_buttonFindLandMark_clicked();

    void on_buttonStartTracking_clicked();

private:
    bool newCalib;
    Ui::MainWindow *ui;
    PlayerStream* myPlayer;

};
#endif // MAINWINDOW_H
