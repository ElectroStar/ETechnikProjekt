#ifndef SHOWIMAGEDIALOG_H
#define SHOWIMAGEDIALOG_H

#include <QDialog>

#include "imageupdater.h"

namespace Ui {
class ShowImageDialog;
}

class ShowImageDialog : public QDialog {
    Q_OBJECT

private slots:
    void updatePlayerStream(QImage img);

    void on_resetButton_clicked();

    void on_closeButton_clicked();

public:
    explicit ShowImageDialog(QWidget *parent = 0);
    ~ShowImageDialog();

    void start(PositioningReceiver *pr);

private:
    Ui::ShowImageDialog *ui;
    QThread* imageProcessing;
    ImageUpdater* worker;
};

#endif // SHOWIMAGEDIALOG_H
