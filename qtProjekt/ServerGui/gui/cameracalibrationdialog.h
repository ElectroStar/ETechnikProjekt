#ifndef CAMERACALIBRATIONDIALOG_H
#define CAMERACALIBRATIONDIALOG_H

#include <QDialog>

#include "guiFunctionClasses/playerstream.h"

namespace Ui {
class cameraCalibrationDialog;
}

class cameraCalibrationDialog : public QDialog
{
    Q_OBJECT

public:
    explicit cameraCalibrationDialog(QWidget *parent = 0);
    ~cameraCalibrationDialog();

private slots:

    void updatePlayerStream(QImage img);

private:
    Ui::cameraCalibrationDialog *ui;
    PlayerStream* myPlayer;
};

#endif // CAMERACALIBRATIONDIALOG_H
