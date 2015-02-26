//============================================================================
// Datei	: infoeagleeyedialog.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef INFOEAGLEEYEDIALOG_H
#define INFOEAGLEEYEDIALOG_H

#include <QDialog>

namespace Ui {
class InfoEagleEyeDialog;
}

/** Klasse fuer die Oberflaeche des Infobereichs.
 *  @author		Eric
 *  @date		12.02.2015
 */
class InfoEagleEyeDialog : public QDialog
{
    Q_OBJECT

public:

    /** Konstruktor.
    */
    explicit InfoEagleEyeDialog(QWidget *parent = 0);

    /** Destruktor.
    */
    ~InfoEagleEyeDialog();

private slots:

    /** Actionhandler bei OK.
    */
    void on_ButtonCloseInfo_clicked();

private:
    Ui::InfoEagleEyeDialog *ui;
};

#endif // INFOEAGLEEYEDIALOG_H
