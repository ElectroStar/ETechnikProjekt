#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "positioningreceiver.h"
#include "posdata.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::guiNewPosition(PosData* data) {
    //qDebug()<<"Update Labe in thread: "<<QThread::currentThreadId();
    ui->lbl_label->setText("X: " + QString::number(data->getX()) + " Y: " + QString::number(data->getY()) + " Z: " + QString::number(data->getZ()));
}

void MainWindow::on_cmd_start_clicked()
{
    //qDebug()<<"From main Window thread: "<<QThread::currentThreadId();
    ui->lbl_label->setText(QString("Start"));

    // Thread erzeugen
    QThread* workerThread = new QThread();

    // Worker erzeugen
    PositioningReceiver* worker = new PositioningReceiver();

    //connect(newThread, SIGNAL(started()), obj, SLOT(doWork()));
    connect(worker, SIGNAL(newPosition(PosData*)), this, SLOT(guiNewPosition(PosData*)));
    worker->moveToThread(workerThread);

    workerThread->start();

    // Button deaktivieren
    ui->cmd_start->setEnabled(false);
}

void MainWindow::on_cmd_ende_clicked()
{
    this->close();
}
