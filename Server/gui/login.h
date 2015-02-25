//============================================================================
// Datei	: login.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef LOGIN_H
#define LOGIN_H

#include <stdint.h>
#include <QDialog>

#include "login.h"
#include "ui_login.h"
#include "mainwindow.h"
#include "Settings.h"

namespace Ui {
class Login;
}

/** Klasse fuer die Oberflaeche bei Programmstart.
 *  @author		Eric
 *  @date		12.02.2015
 */
class Login : public QDialog
{
    Q_OBJECT

public:  

    /** Konstruktor.
    */
    explicit Login(QWidget *parent = 0);

    /** Destruktor.
    */
    ~Login();

    /** Methode zur Ueberpruefung der Datenverfuegbarkeit.
    *  	@param[in] _path	Dateipfad
    *   @return             Alles da/Fehler
    */
    bool checkFile(String _path) const;

private slots:

    /** Actionhandler bei Klick auf 'Verbinden'.
    */
    void on_pushButton_clicked();

private:
    Ui::Login *ui;
};

#endif // LOGIN_H
