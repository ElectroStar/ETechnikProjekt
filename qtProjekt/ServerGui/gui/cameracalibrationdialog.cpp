#include "cameracalibrationdialog.h"
#include "ui_cameracalibrationdialog.h"

cameraCalibrationDialog::cameraCalibrationDialog(QWidget *parent) : QDialog(parent), ui(new Ui::cameraCalibrationDialog) {

    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerStream(QImage)));
    QObject::connect(myPlayer, SIGNAL(picCntSend(int)),this, SLOT(setCntShowlabel(int)));
    QObject::connect(myPlayer, SIGNAL(sendExceptionToGui(eagleeye::Exception e)),this, SLOT(getExeptionForGui(eagleeye::Exception e)));


    myPlayer = new PlayerCalib();
    myPlayer->loadVideo(cameraAdress);

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

void cameraCalibrationDialog::getExeptionForGui(eagleeye::Exception e) {

    ErrorDialog err;

    if(e.getType() == eagleeye::Exception::ERROR_OPEN_CONFIGURATIONFILE) {
        err.setMsg("Konnte Konfigurationsdatei nicht öffnen!");
    }

    else if (e.getType() == eagleeye::Exception::INVALID_CONFIGURATIONFILE) {
        err.setMsg("Parameter in Konfigurationsdatei ungültig!");
    }

    else if (e.getType() == eagleeye::Exception::ERROR_DURING_CALIBRATION) {
        err.setMsg("Es ist ein Fehler waerend der Kalibrierung aufgetreten!");
    }

    myPlayer->setMode(PlayerCalib::Init);
    ui->buttonStartStream->setText("Neustart");
    ui->buttonStartCalib_2->setEnabled(false);
    ui->buttonTakePicture->setEnabled(true);

    err.setModal(true);
    err.exec();

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
    myPlayer->setMode(PlayerCalib::Calib);
}

void cameraCalibrationDialog::on_buttonStartStream_clicked() {

        myPlayer->play();

        myPlayer->setMode(PlayerCalib::Init);
        ui->buttonStartStream->setText("Neustart");
        ui->buttonStartCalib_2->setEnabled(false);
        ui->buttonTakePicture->setEnabled(true);

}

 void cameraCalibrationDialog::setCntShowlabel(int _i) {
     ui->labelShowPicCnt->setText(QString("Aufnahmen: ")+QString().setNum(_i));
 }

