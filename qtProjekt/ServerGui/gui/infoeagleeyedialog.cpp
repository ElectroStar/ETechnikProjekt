#include "infoeagleeyedialog.h"
#include "ui_infoeagleeyedialog.h"

InfoEagleEyeDialog::InfoEagleEyeDialog(QWidget *parent) : QDialog(parent), ui(new Ui::InfoEagleEyeDialog) {

    ui->setupUi(this);

    ui->labelProject->setText("<b>Kamerabasiertes Indoor-Navigationssystem</b><br>(Elektrotechnik Projekt WS 14/15)");

    ui->labelNames->setText("Eric Buschermöhle\n"
                            "Sebastian Hollermann\n"
                            "Joel Bartelheimer"
                            "Benjamin Augenstein\n"
                            "Tung Pham\n"
                            "Michael Over\n"
                            "Christian Jungblut");
    ui->labelVersion->setText(currentVersion);

}

InfoEagleEyeDialog::~InfoEagleEyeDialog() {
    delete ui;
}

void InfoEagleEyeDialog::on_ButtonCloseInfo_clicked() {
    this->close();
}
