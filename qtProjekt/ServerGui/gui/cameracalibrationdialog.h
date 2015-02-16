#ifndef CAMERACALIBRATIONDIALOG_H
#define CAMERACALIBRATIONDIALOG_H

#include <QDialog>

#include "guiFunctionClasses/playercalib.h"
#include "model/Exception/exception.h"
#include "gui/errordialog.h"
#include "config.h"

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
    void getExeptionForGui(eagleeye::EeException e);
    void on_buttonTakePicture_clicked();
    void on_buttonStartCalib_2_clicked();
    void on_buttonStartStream_clicked();

    void setCntShowlabel(int _i);


private:
    Ui::cameraCalibrationDialog *ui;
    PlayerCalib* myPlayer;

};

#endif // CAMERACALIBRATIONDIALOG_H
