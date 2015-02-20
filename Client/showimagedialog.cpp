#include "showimagedialog.h"
#include "ui_showimagedialog.h"

ShowImageDialog::ShowImageDialog(QWidget *parent) : QDialog(parent), ui(new Ui::ShowImageDialog) {
    ui->setupUi(this);

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
