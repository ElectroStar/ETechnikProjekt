#ifndef CAMERACALIBRATIONDIALOG_H
#define CAMERACALIBRATIONDIALOG_H

#include <QDialog>

#include "guiFunctionClasses/playercalib.h"
#include "model/Exception/exception.h"
#include "gui/errordialog.h"
#include "Settings.h"

namespace Ui {
class cameraCalibrationDialog;
}

class cameraCalibrationDialog : public QDialog {
    Q_OBJECT

public:
    explicit cameraCalibrationDialog(QWidget *parent = 0);
    ~cameraCalibrationDialog();

    bool getCalibSuccess() const;
    void setCalibSuccess(bool value);

private slots:

    void updatePlayerStream(QImage img);
    //  void getExeptionForGui(eagleeye::EeException e);
    void updateCalibSuccess(int e);

    void on_buttonTakePicture_clicked();
    void on_buttonStartCalib_2_clicked();
    void on_buttonStartStream_clicked();

    void setCntShowlabel(int _i);

    void on_buttonBox_rejected();

private:

    bool calibSuccess;
    Ui::cameraCalibrationDialog *ui;
    PlayerCalib* myPlayer;

};

#endif // CAMERACALIBRATIONDIALOG_H
