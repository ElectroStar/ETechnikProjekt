//============================================================================
// Datei	: cameracalibrationdialog.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "cameracalibrationdialog.h"
#include "ui_cameracalibrationdialog.h"

cameraCalibrationDialog::cameraCalibrationDialog(QWidget *parent) : QDialog(parent), calibSuccess(false), ui(new Ui::cameraCalibrationDialog) {

    myPlayer = new PlayerCalib();

    //Verbindung der Slots mit den Signalen aus dem PlayerCalib
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerStream(QImage)));
    QObject::connect(myPlayer, SIGNAL(picCntSend(int)),this, SLOT(setCntShowlabel(int)));
    QObject::connect(myPlayer, SIGNAL(sendCalibStatus(int)),this, SLOT(updateCalibSuccess(int)));

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

void cameraCalibrationDialog::updateCalibSuccess(int e) {

    calibSuccess=(bool)e;
    ErrorDialog err;
    setCursor(QCursor(Qt::ArrowCursor));

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
    setCursor(QCursor(Qt::WaitCursor));
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

void cameraCalibrationDialog::on_buttonBox_accepted() {

    const char *old = Settings::instance().outputFileName.c_str();
    const char *work = String(cameraParmFile).c_str();

    rename(old, work);
}
