//============================================================================
// Datei	: PosData.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef POSDATA_H_
#define POSDATA_H_

#include <string>

using namespace std;

/**
 * Klasse zur Repraesendation eines Positionsdatensatzes
 * @author 	Sebastian Hollermann
 * @date	05.11.2014
 */
class PosData {
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
	string _mr;
	// Position des Randes in X-Richtung
	double _x2;
	// Position des Randes in Y-Richtung
	double _y2;
	// Koeffizient fuer reales Bild
	double _coef;
	// Datum
	long int _date;
public:
	/**
	 * Konsturktor
	 */
	PosData();

	/**
	 * Konsturktor zum laden eines Positionsdatensatzes in String Format
	 * @param data
	 */
	PosData(string data);

	/**
	 * Methode zum Zurueckgeben der Position in X-Richtung
	 * @return	Position in X-Richtung
	 */
	double getX() { return _x; }

	/**
	 * Methode zum Zurueckgeben der Position in Y-Richtung
	 * @return	Position in Y-Richtung
	 */
	double getY() { return _y; }

	/**
	 * Methode zum Zurueckgeben der Position in Z-Richtung
	 * @return	Position in Z-Richtung
	 */
	double getZ() { return _z; }

	/**
	 * Methode zum Zurueckgeben des Fehlers
	 * @return	Fehler der Position
	 */
	double getError() { return _error; }

	/**
	 * Methode zum Zurueckgeben des Markers
	 * @return	Marker fuer die die Positionsdaten gilt
	 */
	string getMarker() { return _mr; }

	/**
	 * Methode zum Zurueckgeben der Position des Randes in X-Richtung
	 * @return	Randposition in X-Richtung
	 */
	double getX2() { return _x2; }

	/**
	 * Methode zum Zurueckgeben der Position des Randes in Y-Richtung
	 * @return	Randposition in Y-Richtung
	 */
	double getY2() { return _y2; }

	/**
	 * Methode zum Zurueckgeben des Koeffizienten zwischen Bild und Positionsdaten
	 * @return	Bild zu Positionssystem Koeffizient
	 */
	double getCoefficient() { return _coef; }

	/**
	 * Methode zum Zurueckgeben des Datums der Positionsbestimmung
	 * @return	Zeitstempel zum Zeitpunkt wann die Position ermittelt wurde
	 */
	long int getDate() { return _date; }

	/**
	 * Operator zum Umwandeln des Positionsdatensatzen einen String
	 */
	operator string() const;
};

#endif /* POSDATA_H_ */
