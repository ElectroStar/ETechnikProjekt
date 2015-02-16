#ifndef LOGIN_H
#define LOGIN_H

#include <stdint.h>
#include <QDialog>

#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "config.h"

namespace Ui {
class Login;
}

class Login : public QDialog
{
    Q_OBJECT

public:
    explicit Login(QWidget *parent = 0);
    ~Login();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H