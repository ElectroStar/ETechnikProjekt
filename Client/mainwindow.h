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

class MainWindow : public QMainWindow {
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void NewPosition(PosData*data);

    void on_cmd_start_clicked();
    void on_cmd_ende_clicked();

    void on_actionUeber_Eagle_Eye_triggered();

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


 //   void updatePlayerStream(QImage img, PosData* data);
