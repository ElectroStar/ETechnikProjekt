#include "login.h"

Login::Login(QWidget *parent) : QDialog(parent),ui(new Ui::Login)
{
    ui->setupUi(this);
}

Login::~Login()
{
    delete ui;
}

void Login::on_pushButton_clicked()
{
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

        w->move(x,y);
        w->show();
        this->close();
    }
}
