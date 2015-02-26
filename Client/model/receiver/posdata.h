#ifndef POSDATA_H
#define POSDATA_H

#include <QObject>

class PosData : public QObject
{
    Q_OBJECT
public:
    explicit PosData(QObject *parent = 0);
    ~PosData();

    /**
     * Gibt die Position in X-Richtung zurueck
     * @return Position in X-Richtung
     */
    double getX() const { return _x; }

    /**
     * Gibt die Position in Y-Richtung zurueck
     * @return Position in Y-Richtung
     */
    double getY() const { return _y; }

    /**
     * Gibt die Position in Z-Richtung zurueck
     * @return Position in Z-Richtung
     */
    double getZ() const { return _z; }

    /**
     * Gibt den Fehler fuer diese Position zurueck
     * @return Fehler fuer diese Position
     */
    double getError() const { return _error; }

    /**
     * Gibt den Marker-Erkennungsstring zurueck
     * @return Marker-Erkennungsstring
     */
    QString getMarker() const { return _mr; }

    /**
     * Gibt den Maximalen Wert der Position in X-Richtung zurueck
     * @return Maximaler Wert der Position in X-Richtung
     */
    double getMaxX() const { return _x2; }

    /**
     * Gibt den Maximalen Wert der Position in Y-Richtung zurueck
     * @return Maximaler Wert der Position in Y-Richtung
     */
    double getMaxY() const { return _y2; }

    /**
     * Gibt den Umrechnungskoeffizienten fuer ein reales Bild zurueck
     * @return Umrechnungskoeffiziet fuer ein reales Bild
     */
    double getCoefficient() const { return _coef; }

    /**
     * Gibt das Datum der Versendung im ISO-Format bis 4 Stellen nach der Sekunde zurueck
     * @return Datum der Versendung
     */
    quint64 getDate() const { return _date; }

    /**
     * Setzt die Position in X-Richtung
     * @param value Position in X-Richtung
     */
    void setX(double value) { _x = value; }

    /**
     * Setzt die Position in Y-Richtung
     * @param value Position in Y-Richtung
     */
    void setY(double value) { _y = value; }

    /**
     * Setzt die Position in Z-Richtung
     * @param value Position in Z-Richtung
     */
    void setZ(double value) { _z = value; }


    /**
     * Setzt den Fehler der Positionsdaten
     * @param Fehler der Positionsdaten
     */
    void setError(double value) { _error = value; }

    /**
     * Setzt den Marker der Positionsdaten
     * @param value Maker der Positionsdaten
     */
    void setMarker(QString value) { _mr = value; }

    /**
     * Setzt die Maximale Position in X-Richtung
     * @param value Maximale Position in X-Richtung
     */
    void setMaxX(double value) { _x2 = value; }

    /**
     * Setzt die Maximale Position in Y-Richtung
     * @param value
     */
    void setMaxY(double value) { _y2 = value; }

    /**
     * Setzt den Koeffizienten zur Umrechnung fuer ein Reales Bild
     * @param value Umrechnungskoeffizient
     */
    void setCoefficient(double value) { _coef = value; }

    /**
     * Setzt den Wert des Sendedatums
     * @param value Sendedatum
     */
    void setDate(quint64 value) { _date = value; }
private:
    // Position in X-Richtung
    double _x;
    // Position in Y-Richtung
    double _y;
    // Position in Z-Richtung
    double _z;
    // Fehler
    double _error;
    // Marker
    QString _mr;
    // Position des Randes in X-Richtung (Maximaler X-Wert)
    double _x2;
    // Position des Randes in Y-Richtung (Maximaler Y-Wert)
    double _y2;
    // Koeffizient zur Umrechnung eines realen Bild
    double _coef;
    // Datumwert
    quint64 _date;

signals:

public slots:
};

#endif // POSDATA_H
