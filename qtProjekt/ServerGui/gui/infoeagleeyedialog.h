#ifndef INFOEAGLEEYEDIALOG_H
#define INFOEAGLEEYEDIALOG_H

#include <QDialog>

#include "config.h"

namespace Ui {
class InfoEagleEyeDialog;
}

class InfoEagleEyeDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InfoEagleEyeDialog(QWidget *parent = 0);
    ~InfoEagleEyeDialog();

private slots:
    void on_ButtonCloseInfo_clicked();

private:
    Ui::InfoEagleEyeDialog *ui;
};

#endif // INFOEAGLEEYEDIALOG_H
