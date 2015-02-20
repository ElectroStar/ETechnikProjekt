#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "positioningreceiver.h"
#include "posdata.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow), maxSizeTable(20), currentSizeTable(0) {

    ui->setupUi(this);
    ui->showModelButton->setEnabled(false);

    ui->tableWidget->setEditTriggers(QAbstractItemView::NoEditTriggers);
    ui->tableWidget->setRowCount(1);

    ui->tableWidget->setSizePolicy(QSizePolicy::Expanding,QSizePolicy::Expanding);

    ui->tableWidget->setColumnWidth(0,  90);
    ui->tableWidget->setColumnWidth(1,  90);
    ui->tableWidget->setColumnWidth(2,  90);
    ui->tableWidget->setColumnWidth(3,  90);
    ui->tableWidget->setColumnWidth(4,  200);
    ui->tableWidget->resize(90+90+90+90+200+19,ui->tableWidget->size().height());

    file.open("dataoutput.txt", std::ios::out);

    file << std::setw(8) << "x";
    file << std::setw(8) << "y";
    file << std::setw(8) << "z";
    file << std::setw(8) << "error";
    file << std::setw(18) << "Uhrzeit und Datum";
    file << std::endl;


/*
    for(int i = 0; i<10; i++) {
          currentSizeTable++;

          ui->tableWidget->setRowCount(currentSizeTable);

          QTableWidgetItem *newItem1 = new QTableWidgetItem("Test");
          QTableWidgetItem *newItem2 = new QTableWidgetItem("Test");
          QTableWidgetItem *newItem3 = new QTableWidgetItem("Test");

          ui->tableWidget->setItem(currentSizeTable-1,0, newItem1);
          ui->tableWidget->setItem(currentSizeTable-1,1, newItem2);
          ui->tableWidget->setItem(currentSizeTable-1,2, newItem3);
      }
*/

}

MainWindow::~MainWindow() {
    delete ui;
    file.close();
}

void MainWindow::NewPosition(PosData* data) {

   currentSizeTable++;

   ui->tableWidget->setRowCount(currentSizeTable);

   QTableWidgetItem *newItem1 = new QTableWidgetItem(QString::number(data->getX()));
   QTableWidgetItem *newItem2 = new QTableWidgetItem(QString::number(data->getY()));
   QTableWidgetItem *newItem3 = new QTableWidgetItem(QString::number(data->getZ()));

   QTableWidgetItem *newItem4 = new QTableWidgetItem(QString::number(data->getError()));
   QTableWidgetItem *newItem5 = new QTableWidgetItem(QString::number(data->getDate()));

   ui->tableWidget->setItem(currentSizeTable-1,0, newItem1);
   ui->tableWidget->setItem(currentSizeTable-1,1, newItem2);
   ui->tableWidget->setItem(currentSizeTable-1,2, newItem3);
   ui->tableWidget->setItem(currentSizeTable-1,3, newItem4);
   ui->tableWidget->setItem(currentSizeTable-1,4, newItem5);

   file << std::setw(8) << std::setprecision(4) << data->getX();
   file << std::setw(8) << std::setprecision(4) << data->getY();
   file << std::setw(8) << std::setprecision(4) << data->getZ();
   file << std::setw(8) << data->getError();
   file << std::setw(18) << data->getDate();
   file << std::endl;
}

void MainWindow::on_cmd_start_clicked() {

    // Button updaten
    ui->cmd_start->setEnabled(false);

    // Thread erzeugen
    QThread* workerThread = new QThread();
    // Worker erzeugen
    positionReceiver = new PositioningReceiver();

    //connect(newThread, SIGNAL(started()), obj, SLOT(doWork()));
    connect(positionReceiver, SIGNAL(newPosition(PosData*)), this, SLOT(NewPosition(PosData*)));

    positionReceiver->moveToThread(workerThread);
    workerThread->start();
    ui->showModelButton->setEnabled(true);
}

void MainWindow::on_cmd_ende_clicked() {
    this->close();
}

void MainWindow::on_actionUeber_Eagle_Eye_triggered() {

    InfoEagleEyeDialog InfoEagleEyeDialog;
    InfoEagleEyeDialog.setModal(true);
    InfoEagleEyeDialog.exec();

}

void MainWindow::on_showModelButton_clicked() {

    showImageDialog = new ShowImageDialog();
    showImageDialog->start(this->positionReceiver);
    showImageDialog->setModal(true);
    showImageDialog->show();
}
