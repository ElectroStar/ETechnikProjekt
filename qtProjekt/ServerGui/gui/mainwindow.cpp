#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    myPlayer = new PlayerStream();

    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerStream(QImage)));
    QObject::connect(myPlayer, SIGNAL(foundLandMarks(bool)),this, SLOT(updateTrackingButton(bool)));

    //toDo relativenPfad angeben
    FileStorage fs(cameraParmFile, FileStorage::READ);

    if (!fs.isOpened())
    {
        newCalib = true;
    }
    else newCalib = false;

    fs.release();

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

bool MainWindow::connectWithStream() {

    if (!myPlayer->loadVideo(cameraAdress))
    {
        return false;
    }
    return true;
}

void MainWindow::on_buttonStarteStream_clicked() {

    if(newCalib)
    {
        ErrorDialog err;
        err.setMsg("Konnte Kalibrierungsdatei nicht öffnen! Bitte füren Sie \neine Kalibrierung durch.");
        err.setModal(true);
        err.exec();
    }

    if (myPlayer->isStopped())
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

    cameraCalibrationDialog cameraDialog;
    cameraDialog.setModal(true);
    cameraDialog.exec();

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
