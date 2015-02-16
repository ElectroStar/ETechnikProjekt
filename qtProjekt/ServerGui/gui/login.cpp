#include "login.h"

Login::Login(QWidget *parent) : QDialog(parent),ui(new Ui::Login){
    ui->setupUi(this);
    ui->label_2->setText(currentVersion);
}

Login::~Login(){
    delete ui;
}

bool Login::checkFile(String _path) const {

    FileStorage fs(_path, FileStorage::READ);

    if (!fs.isOpened())
    {
        return false;
    }

    fs.release();
    return true;
}

void Login::on_pushButton_clicked() {
    MainWindow* w = new MainWindow();

    if (!w->connectWithStream()) {
        QMessageBox msgBox;
        msgBox.setText("Es konnte keine Verbidnung aufgebaut werden!");
        msgBox.exec();
    }
    else {

        w->setAttribute(Qt::WA_DeleteOnClose, true);

        uint16_t x = this->x();
        uint16_t y = this->y();

        w->setFoundCalib(checkFile(cameraParmFile));
        w->setFoundConfig(checkFile(calibConfigFile));

        w->move(x,y);
        w->show();
        this->close();
    }
}
