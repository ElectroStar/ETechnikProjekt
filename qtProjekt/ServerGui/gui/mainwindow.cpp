//============================================================================
// Datei	: mainwindow.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    myPlayer = new PlayerStream();

    //Verbindung der Slots mit den Signalen aus dem PlayerStream
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerStream(QImage)));
    QObject::connect(myPlayer, SIGNAL(foundLandMarks(bool)),this, SLOT(updateTrackingButton(bool)));
    QObject::connect(myPlayer, SIGNAL(newCord(QString,QString)), this, SLOT(updatePosLabel(QString,QString)));

    ui->setupUi(this);

    ui->buttonFindLandMark->setEnabled(false);
    ui->buttonStartTracking->setEnabled(false);
    ui->checkBoxSend->setEnabled(false);
}

MainWindow::~MainWindow(){

    delete myPlayer;
    delete ui;
}

void MainWindow::updatePlayerStream(QImage img) {

    if (!img.isNull())
    {
        ui->showStreamLabel->setAlignment(Qt::AlignCenter);
        ui->showStreamLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->showStreamLabel->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void MainWindow::updateTrackingButton(bool flag){

    ui->buttonStartTracking->setEnabled(flag);
}

void MainWindow::updatePosLabel(const QString posX, const QString posY) {

    ui->labelPosX->setText(QString("Pos X: ")+posX);
    ui->labelPosY->setText(QString("Pos Y: ")+posY);
}

bool MainWindow::connectWithStream() {

    if (!myPlayer->loadVideo(cameraAdress))
    {
        return false;
    }
    return true;
}

void MainWindow::on_buttonStarteStream_clicked() {

    if(!foundCalib)
    {
        ErrorDialog err;
        err.setMsg("Konnte Kalibrierungsdatei nicht öffnen! Bitte führen Sie \neine Kalibrierung durch.");
        err.setModal(true);
        err.exec();
    }

    else if (myPlayer->isStopped())
    {
        myPlayer->play();
        ui->buttonStarteStream->setText(tr("Stoppe Stream"));
        ui->buttonFindLandMark->setEnabled(true);

        if(myPlayer->getMode()==PlayerStream::Tracking) {
            ui->buttonStartTracking->setEnabled(true);
            ui->checkBoxSend->setEnabled(true);
        }
    }

    else
    {
        myPlayer->stop();
        ui->buttonStarteStream->setText(tr("Starte Stream"));
        ui->buttonFindLandMark->setEnabled(false);
        ui->checkBoxSend->setEnabled(false);
        ui->buttonStartTracking->setEnabled(false);
    }
}

void MainWindow::on_actionKamerakalibrierung_triggered() {

    if(!foundConfig) {

        ErrorDialog err;
        err.setMsg("Konnte Konfigurationsdatei nicht finden!");
        err.setModal(true);
        err.exec();
    }

    else {

        cameraCalibrationDialog cameraDialog;
        cameraDialog.setModal(true);
        myPlayer->stop();
        cameraDialog.exec();

        if(cameraDialog.getCalibSuccess()) {

            foundCalib = true;
            myPlayer->setMode(PlayerStream::Init);

            ui->buttonStarteStream->setText(tr("Starte Stream"));
            ui->buttonFindLandMark->setEnabled(false);
            ui->checkBoxSend->setEnabled(false);
            ui->buttonStartTracking->setEnabled(false);
        }
        myPlayer->start();
    }
}

void MainWindow::on_action_ber_EagleEye_triggered() {

    InfoEagleEyeDialog InfoEagleEyeDialog;
    InfoEagleEyeDialog.setModal(true);
    InfoEagleEyeDialog.exec();
}

void MainWindow::on_buttonFindLandMark_clicked() {

    ui->checkBoxSend->setEnabled(false);
    ui->checkBoxSend->setChecked(false);
    ui->buttonStartTracking->setText("Starte Tracking");
    myPlayer->setMode(PlayerStream::FindLandMark);
}

void MainWindow::on_buttonStartTracking_clicked() {

    if (myPlayer->getMode() == PlayerStream::Tracking) {

        myPlayer->setMode(PlayerStream::Idle);
        ui->buttonStartTracking->setEnabled(false);
        ui->checkBoxSend->setEnabled(false);
        ui->checkBoxSend->setChecked(false);
        ui->buttonStartTracking->setText("Starte Tracking");
    }
    else {
         myPlayer->setMode(PlayerStream::Tracking);
         ui->checkBoxSend->setEnabled(true);
         ui->buttonStartTracking->setText("Stoppe Tracking");
    }

}

bool MainWindow::getFoundCalib() const {
    return foundCalib;
}

void MainWindow::setFoundCalib(bool value) {
    foundCalib = value;
}

bool MainWindow::getFoundConfig() const {
    return foundConfig;
}

void MainWindow::setFoundConfig(bool value) {
    foundConfig = value;
}

void MainWindow::on_checkBoxSend_clicked(bool checked) {

    if(checked) {
        myPlayer->setSend(true);
    }

    else {
        myPlayer->setSend(false);
    }
}

void MainWindow::on_actionIP_EInstellungen_triggered() {

    if(!foundConfig) {
        ErrorDialog err;
        err.setMsg("Konnte Konfigurationsdatei nicht finden!");
        err.setModal(true);
        err.exec();
    }

    else {

        SettingsDialog settingsDialog;
        settingsDialog.setModal(true);
        myPlayer->stop();

        settingsDialog.exec();

        if(!settingsDialog.getCanceled()) {

            myPlayer->setMode(PlayerStream::Init);
            ui->buttonStarteStream->setText(tr("Starte Stream"));
            ui->buttonFindLandMark->setEnabled(false);
            ui->checkBoxSend->setEnabled(false);
            ui->buttonStartTracking->setEnabled(false);
        }
        else {
            myPlayer->play();
        }
    }
}
