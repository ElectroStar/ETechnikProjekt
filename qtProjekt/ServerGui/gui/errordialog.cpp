#include "errordialog.h"
#include "ui_errordialog.h"

ErrorDialog::ErrorDialog(QWidget *parent) : QDialog(parent),ui(new Ui::ErrorDialog) {
    ui->setupUi(this);
}

void ErrorDialog::setMsg(QString _msg) {
    ui->errorlabel->setText(_msg);
}

ErrorDialog::~ErrorDialog() {
    delete ui;
}
