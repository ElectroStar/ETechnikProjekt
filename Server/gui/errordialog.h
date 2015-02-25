//============================================================================
// Datei	: errordialog.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef ERRORDIALOG_H
#define ERRORDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class ErrorDialog;
}

/** Klasse zur Anzeige von Meldungen.
 *  @author		Eric
 *  @date		12.02.2015
 */
class ErrorDialog : public QDialog
{
    Q_OBJECT

public:

    /** Konstruktor.
    */
    explicit ErrorDialog(QWidget *parent = 0);

    /** Destruktor.
    */
    ~ErrorDialog();

    /** Setter fuer den Nachrichtentext.
    *  	@param[in] _msg 	Message
    */
    void setMsg(QString _msg);

private slots:

    /** Actionhandler bei OK.
    */
    void on_pushButton_clicked();

private:
    Ui::ErrorDialog *ui;
};

#endif // ERRORDIALOG_H
