//============================================================================
// Datei	: showimagedialog.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef SHOWIMAGEDIALOG_H
#define SHOWIMAGEDIALOG_H

#include <QDialog>

#include "controller/imageupdater.h"
#include "errordialog.h"

namespace Ui {
class ShowImageDialog;
}

/** Hauptoberflaeche fuer die Grafische Positionsanzeige.
 *  @author		Eric Buschermoehle
 *  @date		22.02.2015
 */
class ShowImageDialog : public QDialog {
    Q_OBJECT

public:

    /** Konstruktor.
    */
    explicit ShowImageDialog(QWidget *parent = 0);

    /**
    * Destruktor
    */
    ~ShowImageDialog();

    /** Methode zum starten der Grafischen Positionsverfolgung.
    *  	@param[in] pr		Positionsverfolgungsempfaenger
    */
    void start(PositioningReceiver *pr);

private slots:

    /** Slot zum aktualisieren/neu zeichnen der Zeichenflaeche.
    *  	@param[in] img		aktuelle Objektposition
    */
    void updatePlayerStream(QImage img);

    /** Slot zum ruecksetzen der Zeichenfeldes.
    */
    void on_resetButton_clicked();

    /** Slot zum schliessen der Grafischen Positionsanzeige.
    */
    void on_closeButton_clicked();

    /** Slot zeichnen einer Linie ins Bild.
    */
    void on_pushButton_2_clicked();

    /** Slot ob zeichnen erfolgreich war.
    */
    void validData(bool value);

    /** Slot zum anzeigen des neuen Abstandes.
    *  	@param[in] value		aktueller Abstand zur Geraden.
    */
    void setDistance(double value);

signals:

    /** Signal zum zeichnes einer Linie
    *  	@param[in] x1		Start x
    *   @param[in] x1		Start y
    *   @param[in] x1		Ende x
    *   @param[in] x1		Ende y
    */
     void sendDrawNewLine(double x1, double y1, double x2, double y2);

private:
    Ui::ShowImageDialog *ui;
    QThread* imageProcessing;
    ImageUpdater* worker;
};

#endif // SHOWIMAGEDIALOG_H
