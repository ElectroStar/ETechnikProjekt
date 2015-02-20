#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "posdata.h"
#include "imageupdater.h"
#include "infoeagleeyedialog.h"


namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:

    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:

    void on_cmd_start_clicked();
    void on_cmd_ende_clicked();

    void updatePlayerStream(QImage img, PosData* data);

    void on_resetButton_clicked();

    void on_actionUeber_Eagle_Eye_triggered();

private:

    QThread* imageProcessing;
    ImageUpdater* worker;
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
