#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    myTracking = new PlayerTracking();
    myPlayer = new PlayerStream();

    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerStream(QImage)));
    QObject::connect(myTracking, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerTracking(QImage)));

    //toDo relativenPfad angeben
    FileStorage fs("/home/user/ServerGui/configFiles/out_camera_data.xml", FileStorage::READ);

    if (!fs.isOpened())
    {
        newCalib = true;
    }
    else newCalib = false;

    fs.release();

    ui->setupUi(this);
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

void MainWindow::updatePlayerTracking(QImage img) {

    if (!img.isNull())
    {
        ui->showTrackingLabel->setAlignment(Qt::AlignCenter);
        ui->showTrackingLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->showTrackingLabel->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

bool MainWindow::connectWithStream() {

    if (!myPlayer->loadVideo("/home/user/Desktop/drop.avi"))
    {
        return false;
    }

    myTracking->setImageHeight(myPlayer->getImageHeight());
    myTracking->setImageWidth(myPlayer->getImageWidth());
    myTracking->createNewBlackImage();

    return true;
}

void MainWindow::on_buttonStarteStream_clicked() {

    if (myPlayer->isStopped())
    {
        myPlayer->play();
        ui->buttonStarteStream->setText(tr("Stoppe Stream"));
    }

    else
    {
        myPlayer->stop();
        ui->buttonStarteStream->setText(tr("Starte Stream"));
    }
}

void MainWindow::on_buttonStartTracking_clicked() {

    if(newCalib)
    {
        ErrorDialog err;
        err.setMsg("Konnte Kalibrierungsdatei nicht öffnen! Bitte füren Sie \neine Kalibrierung durch.");
        err.setModal(true);
        err.exec();
    }

    else
    {

        if (myTracking->isStopped())
        {
            myTracking->play();
            ui->buttonStartTracking->setText(tr("Stoppe Tracking"));
        }

        else
        {
            myTracking->stop();
            ui->buttonStartTracking->setText(tr("Starte Tracking"));
        }
    }
}

void MainWindow::on_actionKamerakalibrierung_triggered() {

    cameraCalibrationDialog cameraDialog;
    cameraDialog.setModal(true);
    cameraDialog.exec();
}

void MainWindow::on_buttonResetWindow_clicked() {
    myTracking->createNewBlackImage();
}
