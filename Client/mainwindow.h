#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include "posdata.h"

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

    void guiNewPosition(PosData*);

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H