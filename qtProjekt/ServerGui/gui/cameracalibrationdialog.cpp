#include "cameracalibrationdialog.h"
#include "ui_cameracalibrationdialog.h"

cameraCalibrationDialog::cameraCalibrationDialog(QWidget *parent) : QDialog(parent), ui(new Ui::cameraCalibrationDialog) {

    myPlayer = new PlayerCalib();
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerStream(QImage)));
    QObject::connect(myPlayer, SIGNAL(picCntSend(int)),this, SLOT(setCntShowlabel(int)));

    myPlayer->loadVideo("http://192.168.0.1:8080/?action=stream&amp;type=.mjpg");


    ui->setupUi(this);
    ui->buttonStartCalib_2->setEnabled(false);
    ui->buttonTakePicture->setEnabled(false);
}

void cameraCalibrationDialog::updatePlayerStream(QImage img) {

    if (!img.isNull()) {
        ui->showCalibLabel->setAlignment(Qt::AlignCenter);
        ui->showCalibLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->showCalibLabel->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

cameraCalibrationDialog::~cameraCalibrationDialog() {
    delete ui;
}

void cameraCalibrationDialog::on_buttonTakePicture_clicked() {
    myPlayer->setTakePic(true);

    if(myPlayer->getPicCnt() >= myPlayer->getSettings().nrFrames-1)
    {
        ui->buttonStartCalib_2->setEnabled(true);
    }
}

void cameraCalibrationDialog::on_buttonStartCalib_2_clicked() {
    myPlayer->setMode(Calib);
}

void cameraCalibrationDialog::on_buttonStartStream_clicked() {

        myPlayer->play();

        myPlayer->setMode(Init);
        ui->buttonStartStream->setText("Neustart");
        ui->buttonStartCalib_2->setEnabled(false);
        ui->buttonTakePicture->setEnabled(true);

}

 void cameraCalibrationDialog::setCntShowlabel(int _i) {
     ui->labelShowPicCnt->setText(QString("Aufnahmen: ")+QString().setNum(_i));
 }

