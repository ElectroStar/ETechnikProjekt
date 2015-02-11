//============================================================================
// Datei	: PosData.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef POSDATA_H_
#define POSDATA_H_

#include <string>
#include <cv.h>

using namespace std;
using namespace cv;

/**
 * Klasse zur Repraesendation eines Positionsdatensatzes
 * @author 	Sebastian Hollermann
 * @date	05.11.2014
 */
class PosData {
private:
	// Position in X-Richtung
	string _x;
	// Position in Y-Richtung
	string _y;
	// Position in Z-Richtung
	string _z;
public:
	/**
	 * Konsturktor zum laden eines Positionsdatensatzes in String Format
	 * @param data
	 */
	PosData(string data);

	/**
	 * Konstruktor zum erzeugen eines Positionsdatensatzes aus einen Double Point
	 * @param pos
	 */
	PosData(Point2d pos);

	/**
	 * Methode zum Zurueckgeben der Position in X-Richtung
	 * @return	Position in X-Richtung
	 */
	string getX() { return _x; }

	/**
	 * Methode zum Zurueckgeben der Position in Y-Richtung
	 * @return	Position in Y-Richtung
	 */
	string getY() { return _y; }

	/**
	 * Methode zum Zurueckgeben der Position in Z-Richtung
	 * @return	Position in Z-Richtung
	 */
	string getZ() { return _z; }

	/**
	 * Operator zum Umwandeln des Positionsdatensatzen einen String
	 */
	operator string() const;
};

#endif /* POSDATA_H_ */
