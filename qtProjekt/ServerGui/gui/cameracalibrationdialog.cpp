#include "cameracalibrationdialog.h"
#include "ui_cameracalibrationdialog.h"

cameraCalibrationDialog::cameraCalibrationDialog(QWidget *parent) : QDialog(parent), calibSuccess(false), ui(new Ui::cameraCalibrationDialog) {

    myPlayer = new PlayerCalib();

    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerStream(QImage)));
    QObject::connect(myPlayer, SIGNAL(picCntSend(int)),this, SLOT(setCntShowlabel(int)));
    QObject::connect(myPlayer, SIGNAL(sendCalibStatus(int)),this, SLOT(updateCalibSuccess(int)));

    //QObject::connect(myPlayer, SIGNAL(sendExceptionToGui(eagleeye::EeException)),this, SLOT(getExeptionForGui(eagleeye::EeException)));
    //qRegisterMetaType<eagleeye::EeException>("eagleeye::EeException");

    ui->setupUi(this);
    ui->buttonStartCalib_2->setEnabled(false);
    ui->buttonTakePicture->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);

    myPlayer->loadVideo(cameraAdress);
}

void cameraCalibrationDialog::updatePlayerStream(QImage img) {

    if (!img.isNull()) {
        ui->showCalibLabel->setAlignment(Qt::AlignCenter);
        ui->showCalibLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->showCalibLabel->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}
/*
void cameraCalibrationDialog::getExeptionForGui(eagleeye::EeException e) {

    ErrorDialog err;

    if(e.getType() == eagleeye::EeException::ERROR_OPEN_CONFIGURATIONFILE) {
        err.setMsg("Konnte Konfigurationsdatei nicht öffnen!");
    }

    else if (e.getType() == eagleeye::EeException::INVALID_CONFIGURATIONFILE) {
        err.setMsg("Parameter in Konfigurationsdatei ungültig!");
    }

    else if (e.getType() == eagleeye::EeException::ERROR_DURING_CALIBRATION) {
        err.setMsg("Es ist ein Fehler waerend der Kalibrierung aufgetreten!");
        calibSuccess = false;
    }

    myPlayer->setMode(PlayerCalib::Error);
    ui->buttonStartStream->setText("Neustart");
    ui->buttonStartCalib_2->setEnabled(false);
    ui->buttonTakePicture->setEnabled(true);

    err.setModal(true);
    err.exec();

}
*/
void cameraCalibrationDialog::updateCalibSuccess(int e) {

    calibSuccess=(bool)e;
    ErrorDialog err;

    if(!e) {
        err.setMsg("Es ist ein Fehler waerend der Kalibrierung aufgetreten!");
        err.setWindowTitle("Error");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
    }
    else {

        err.setMsg(QString("Kalibrierung erfolgreich! Es wurden ") + QString().setNum(e) + QString(" Bilder erkannt"));
        err.setWindowTitle("Erfolgreich");
        ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(true);
    }

    ui->buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(true);
    ui->buttonStartStream->setText("Neustart");
    ui->buttonStartCalib_2->setEnabled(false);
    ui->buttonTakePicture->setEnabled(false);

    err.setModal(true);
    err.exec();

}

cameraCalibrationDialog::~cameraCalibrationDialog() {
    delete ui;
}

void cameraCalibrationDialog::on_buttonTakePicture_clicked() {
    myPlayer->setTakePic(true);

    if(myPlayer->getPicCnt() >= Settings::instance().nrFrames-1)
    {
        ui->buttonStartCalib_2->setEnabled(true);
    }
}

void cameraCalibrationDialog::on_buttonStartCalib_2_clicked() {
    myPlayer->setMode(PlayerCalib::Calib);
    ui->buttonBox->button(QDialogButtonBox::Cancel)->setEnabled(false);
    ui->buttonBox->button(QDialogButtonBox::Ok)->setEnabled(false);
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


 bool cameraCalibrationDialog::getCalibSuccess() const {
     return calibSuccess;
 }

 void cameraCalibrationDialog::setCalibSuccess(bool value) {
     calibSuccess = value;
 }

void cameraCalibrationDialog::on_buttonBox_rejected() {
    calibSuccess = false;
}
