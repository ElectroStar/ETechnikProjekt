#include "cameracalibrationdialog.h"
#include "ui_cameracalibrationdialog.h"

cameraCalibrationDialog::cameraCalibrationDialog(QWidget *parent) : QDialog(parent), ui(new Ui::cameraCalibrationDialog) {

    myPlayer = new PlayerStream();
    QObject::connect(myPlayer, SIGNAL(processedImage(QImage)),this, SLOT(updatePlayerStream(QImage)));

    myPlayer->loadVideo("/home/user/Desktop/drop.avi");
    myPlayer->play();

    ui->setupUi(this);
}

void cameraCalibrationDialog::updatePlayerStream(QImage img) {

    if (!img.isNull()) {
        ui->showCalibLabel->setAlignment(Qt::AlignCenter);
        ui->showCalibLabel->setPixmap(QPixmap::fromImage(img).scaled(ui->showCalibLabel->size(),Qt::KeepAspectRatio, Qt::FastTransformation));
    }
}

cameraCalibrationDialog::~cameraCalibrationDialog() {
    delete ui;
}
