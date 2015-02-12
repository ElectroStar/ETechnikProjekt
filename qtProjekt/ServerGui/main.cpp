#include "login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login* login = new Login();
    login->setAttribute(Qt::WA_DeleteOnClose, true);
    login->show();

    return a.exec();
}
