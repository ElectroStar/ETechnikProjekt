//============================================================================
// Datei	: main.cpp
// Projekt	: Kamerabasiertes Indoor-Navigationssystem
// Modul	: Elektrotechnik Projekt WS 2014/2015
// Prof 	: Prof. Dr. Arno Ruckelshausen
// Autoren	: Christian Jungblut, Eric Buschermoehle, Joel Bartelheimer,
//            Michael Over, Benjamin Augenstein, Thanh Tung Pham
// Version	: 1.0
//============================================================================

#include "gui/login.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Login* login = new Login();
    login->setAttribute(Qt::WA_DeleteOnClose, true);
    login->show();

    return a.exec();
}
