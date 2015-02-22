//============================================================================
// Datei	: showimagedialog.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "showimagedialog.h"
#include "ui_showimagedialog.h"

ShowImageDialog::ShowImageDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ShowImageDialog) {

    ui->setupUi(this);

    QRegExp rx("\\d*\\.\\d+");
    QValidator *validator = new QRegExpValidator(rx, this);

    ui->lineEditPos1x->setValidator(validator);
    ui->lineEditPos1y->setValidator(validator);
    ui->lineEditPos2x->setValidator(validator);
    ui->lineEditPos2y->setValidator(validator);

}

ShowImageDialog::~ShowImageDialog() {
    delete ui;
}

void ShowImageDialog::start(PositioningReceiver* pr) {

    imageProcessing = new QThread();

    // Worker erzeugen
    worker = new ImageUpdater();

    connect(pr, SIGNAL(newPosition(PosData*)), worker, SLOT(NewPosition(PosData*)));
    connect(worker, SIGNAL(processedImage(QImage)), this, SLOT(updatePlayerStream(QImage)));

    connect(worker, SIGNAL(sendDistance(double)), this, SLOT(setDistance(double)));
    connect(this, SIGNAL(sendDrawNewLine(int,int,int,int), worker, SLOT(drawNewLine(int,int,int,int)));

    worker->moveToThread(imageProcessing);

    imageProcessing->start();

}

void ShowImageDialog::updatePlayerStream(QImage img) {

    if (!img.isNull()) {
        ui->showImagelabel->setAlignment(Qt::AlignCenter);
        ui->showImagelabel->setPixmap(QPixmap::fromImage(img).scaled(ui->showImagelabel->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

void ShowImageDialog::on_resetButton_clicked() {
    worker->modelCreator->redraw();
}

void ShowImageDialog::on_closeButton_clicked() {

    imageProcessing->terminate();
    this->close();
}

void ShowImageDialog::on_pushButton_2_clicked() {

    if(ui->lineEditPos1x->text().isEmpty() || ui->lineEditPos1y->text().isEmpty()
            || ui->lineEditPos2x->text().isEmpty()  || ui->lineEditPos2y->text().isEmpty()) {

        ErrorDialog err;
        err.setMsg("Ein oder mehrere Felder sind leer!");
        err.exec();
    }

    else {
        int x1 = ui->lineEditPos1x->text().toInt();
        int y1 = ui->lineEditPos1y->text().toInt();
        int x2 = ui->lineEditPos2x->text().toInt();
        int y2 = ui->lineEditPos1y->text().toInt();

        emit sendDrawNewLine(x1,y1,x2,y2);

    }
}

void ShowImageDialog::validData(bool value) {

    if(!value) {
        ErrorDialog err;
        err.setMsg("Die Koordinaten liegen außerhalb des Bildes!");
        err.exec();
    }
}

void ShowImageDialog::setDistance(double value) {
    ui->labelDistance->setText(QString::number(value));
}
