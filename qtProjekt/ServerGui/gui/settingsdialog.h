//============================================================================
// Datei	: settingsdialog.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef SETTINGSDIALOG_H
#define SETTINGSDIALOG_H

#include <QDialog>
#include "Settings.h"

namespace Ui {
class SettingsDialog;
}

/** Klasse fuer die Oberflaeche der Programmeinstellungen.
 *  @author		Eric
 *  @date		15.02.2015
 */
class SettingsDialog : public QDialog {

    Q_OBJECT

public:

    /** Konstruktor.
    */
    explicit SettingsDialog(QWidget *parent = 0);

    /** Destruktor.
    */
    ~SettingsDialog();

    /** Getter fuer die Nutzerreaktion.
    * @return       OK/Cancel
    */
    bool getCanceled() const;

private slots:

    /** Actionhandler bei Klick auf OK.
    */
    void on_buttonBox_accepted();

private:

    Ui::SettingsDialog *ui;
    bool canceled;
};

#endif // SETTINGSDIALOG_H
