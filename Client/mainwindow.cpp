#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "positioningreceiver.h"
#include "posdata.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
    ui->resetButton->setEnabled(false);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::updatePlayerStream(QImage img, PosData *data) {

    if (!img.isNull())
    {
        ui->showStreamLabel->setAlignment(Qt::AlignCenter);
        ui->showStreamLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->showStreamLabel->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
    ui->lbl_label->setText("Position X: " + QString::number(data->getX()) + " Position Y: " + QString::number(data->getY()));
}

void MainWindow::on_cmd_start_clicked()
{

    imageProcessing = new QThread();

    // Worker erzeugen
    worker = new ImageUpdater();

    connect(worker, SIGNAL(processedImage(QImage, PosData*)), this, SLOT(updatePlayerStream(QImage, PosData*)));
    worker->moveToThread(imageProcessing);

    imageProcessing->start();

    // Button updaten
    ui->cmd_start->setEnabled(false);
    ui->resetButton->setEnabled(true);
}

void MainWindow::on_cmd_ende_clicked() {
    this->close();
}


void MainWindow::on_resetButton_clicked()
{
    /////////////////////////////////////////////////////////ACHTUNG: SEGMENTATION FAULT MOEGLICH -> MUTEX?! ////////
    ////////////////// EMPFAENGR MUSS GESTOPPT WERDEN!!
    delete worker->modelCreator;
    worker->modelCreator = new ModelCreator(1280);
}

void MainWindow::on_actionUeber_Eagle_Eye_triggered() {

    InfoEagleEyeDialog InfoEagleEyeDialog;
    InfoEagleEyeDialog.setModal(true);
    InfoEagleEyeDialog.exec();

}
