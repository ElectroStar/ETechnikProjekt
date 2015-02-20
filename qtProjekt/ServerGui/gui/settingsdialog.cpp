#include "settingsdialog.h"
#include "ui_settingsdialog.h"

#include <iostream>

SettingsDialog::SettingsDialog(QWidget *parent) : QDialog(parent), ui(new Ui::SettingsDialog), canceled(true) {

    ui->setupUi(this);

    //Einstellungen fuer den Ursprung
    if(Settings::instance().landMarkShapeOrigin == 4) {
        ui->comboBox_1->setCurrentText("Viereck");
    }
    else {
        ui->comboBox_1->setCurrentText("Dreieck");
    }

    if(Settings::instance().landMarkColorOriginMin == 0 && Settings::instance().landMarkColorOriginMax == 127) {
        ui->comboBox_2->setCurrentText("Schwarz");
    }

    else {
        ui->comboBox_2->setCurrentText("Weiss");
    }
    ui->lineEdit_1->setText(QString().number(Settings::instance().landMarkSizeOrigin));

    //Einstellungen fuer die Referenz
    if(Settings::instance().landMarkShapeReference == 4) {
        ui->comboBox_3->setCurrentText("Viereck");
    }
    else {
        ui->comboBox_3->setCurrentText("Dreieck");
    }

    if(Settings::instance().landMarkColorReferenceMin == 0 && Settings::instance().landMarkColorReferenceMax == 127) {
        ui->comboBox_4->setCurrentText("Schwarz");
    }

    else {
        ui->comboBox_4->setCurrentText("Weiss");
    }
    ui->lineEdit_2->setText(QString().number(Settings::instance().landMarkSizeReference));

    //Einstellungen fuer die Objektmarke
    if(Settings::instance().objectShape == 4) {
        ui->comboBox_5->setCurrentText("Viereck");
    }
    else {
        ui->comboBox_5->setCurrentText("Dreieck");
    }

    if(Settings::instance().objectColorMin == 0 && Settings::instance().objectColorMax == 127) {
        ui->comboBox_6->setCurrentText("Schwarz");
    }

    else {
        ui->comboBox_6->setCurrentText("Weiss");
    }
    ui->lineEdit_3->setText(QString().number(Settings::instance().objectSizeCM));


    //Kantenerkennung
    ui->lineEdit_4->setText(QString().number(Settings::instance().harrisCornerBlockSize));
    ui->lineEdit_5->setText(QString().number(Settings::instance().harrisCornerApertureSize));
    ui->lineEdit_6->setText(QString().number(Settings::instance().harrisCornerVariance)); //float?! geht das so?
    ui->lineEdit_7->setText(QString().number(Settings::instance().harrisCornerThresh));
    ui->lineEdit_8->setText(QString().number(Settings::instance().harrisCornerMergeArea));

    //Kreiserkennung
    ui->lineEdit_9->setText(QString().number(Settings::instance().houghCircleThreshold));

    //Gaussfilter
    ui->lineEdit_10->setText(QString().number(Settings::instance().gaussianSize));
    ui->lineEdit_11->setText(QString().number(Settings::instance().gaussianStandardDeviation));

    //Kamerakalibrierung
    ui->lineEdit_12->setText(QString().number(Settings::instance().boardSize.width));
    ui->lineEdit_13->setText(QString().number(Settings::instance().boardSize.height));
    ui->lineEdit_14->setText(QString().number(Settings::instance().calibPanelHeightMM));
    ui->lineEdit_15->setText(QString().number(Settings::instance().squareSize));
    ui->lineEdit_16->setText(QString().number(Settings::instance().nrFrames));

}

SettingsDialog::~SettingsDialog() {
    delete ui;
}

void SettingsDialog::on_buttonBox_accepted() {

    //Einstellungen fuer den Ursprung
    if(ui->comboBox_1->currentText()=="Dreieck") {
        Settings::instance().landMarkShapeOrigin = 3;
    }

    else {
        Settings::instance().landMarkShapeOrigin = 4;
    }

    if(ui->comboBox_2->currentText()=="Schwarz") {
        Settings::instance().landMarkColorOriginMin = 0;
        Settings::instance().landMarkColorOriginMax = 127;
    }

    else {
        Settings::instance().landMarkColorOriginMin = 128;
        Settings::instance().landMarkColorOriginMax = 255;
    }

    Settings::instance().landMarkSizeOrigin = (ui->lineEdit_1->text()).toInt();


    //Einstellungen fuer die Referenz
    if(ui->comboBox_3->currentText()=="Dreieck") {
        Settings::instance().landMarkShapeReference = 3;
    }
    else {
        Settings::instance().landMarkShapeReference = 4;
    }

    if(ui->comboBox_4->currentText()=="Schwarz") {
        Settings::instance().landMarkColorReferenceMin = 0;
        Settings::instance().landMarkColorReferenceMax = 127;
    }

    else {
        Settings::instance().landMarkColorReferenceMin = 128;
        Settings::instance().landMarkColorReferenceMax = 255;
    }
    Settings::instance().landMarkSizeReference = (ui->lineEdit_2->text()).toInt();

    //Einstellungen fuer die Objektmarke
    if(ui->comboBox_5->currentText()=="Dreieck") {
        Settings::instance().objectShape = 3;
    }
    else {
        Settings::instance().objectShape = 4;
    }

    if(ui->comboBox_6->currentText()=="Schwarz") {
        Settings::instance().objectColorMin = 0;
        Settings::instance().objectColorMax = 127;
    }

    else {
        Settings::instance().objectColorMin = 128;
        Settings::instance().objectColorMax = 255;
    }

    Settings::instance().objectSizeCM = (ui->lineEdit_3->text()).toInt();

    //Kantenerkennung
    Settings::instance().harrisCornerBlockSize = (ui->lineEdit_4->text()).toInt();
    Settings::instance().harrisCornerApertureSize = (ui->lineEdit_5->text()).toInt();
    Settings::instance().harrisCornerVariance = (ui->lineEdit_6->text()).toFloat();
    Settings::instance().harrisCornerThresh = (ui->lineEdit_7->text()).toInt();
    Settings::instance().harrisCornerMergeArea = (ui->lineEdit_8->text()).toInt();

    //Kreiserkennung
    Settings::instance().houghCircleThreshold = (ui->lineEdit_9->text()).toInt();

    //Gaussfilter
    Settings::instance().gaussianSize = (ui->lineEdit_10->text()).toInt();
    Settings::instance().gaussianStandardDeviation = (ui->lineEdit_11->text()).toInt();

    //Kamerakalibrierung
    Settings::instance().boardSize.width = (ui->lineEdit_12->text()).toInt();
    Settings::instance().boardSize.height = (ui->lineEdit_13->text()).toInt();
    Settings::instance().calibPanelHeightMM = (ui->lineEdit_14->text()).toInt();
    Settings::instance().squareSize = (ui->lineEdit_15->text()).toFloat();
    Settings::instance().nrFrames = (ui->lineEdit_16->text()).toInt();

    Settings::instance().writeSettings();

    canceled = false;
}

bool SettingsDialog::getCanceled() const {
    return canceled;
}



