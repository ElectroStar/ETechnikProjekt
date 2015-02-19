#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "positioningreceiver.h"
#include "posdata.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) {

    ui->setupUi(this);
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
    ui->lbl_label->setText("X: " + QString::number(data->getX()) + " Y: " + QString::number(data->getY()) + " Z: " + QString::number(data->getZ()));
}

void MainWindow::on_cmd_start_clicked()
{

    //qDebug()<<"From main Window thread: "<<QThread::currentThreadId();
    ui->lbl_label->setText(QString("Start"));

    imageProcessing = new QThread();

    // Worker erzeugen
    ImageUpdater* worker = new ImageUpdater();

    //connect(newThread, SIGNAL(started()), obj, SLOT(doWork()));
    connect(worker, SIGNAL(processedImage(QImage, PosData*)), this, SLOT(updatePlayerStream(QImage, PosData*)));
    worker->moveToThread(imageProcessing);

    imageProcessing->start();

    // Button deaktivieren
    ui->cmd_start->setEnabled(false);

}

void MainWindow::on_cmd_ende_clicked() {
    this->close();
}
