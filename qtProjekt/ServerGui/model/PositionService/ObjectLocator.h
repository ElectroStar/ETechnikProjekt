//============================================================================
// Datei	: ObjectLocator.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef OBJECTLOCATOR_H_
#define OBJECTLOCATOR_H_

#include "IPositionService.h"

/** Klasse zur Erkennung von Objekten.
 *  @author		Christian
 *  @date		11.02.2015
 */
class ObjectLocator : public IPositionService {

private:

	//Parameter zur Kantenerkennung
    int blockSize;
    int apertureSize;
    double k;
    int thresh;

	//Gefundene Kreise und Kanten
	vector<Point> cornerP;
	vector<Vec3f> circles;

public:

	/** Konstruktor.
	*/
	ObjectLocator();
	
	/** Methode zur Addition zweier Zahlen.
	*  	@param[in] _src		Ausgangsbild
	*  	@param[in] _spec 	Objektspezifikation
	*  	@return 			Erkannte Objekte
	*/
	vector<LocatedObject> getAllObjects(Mat _src, LocatableObject _spec);
	
	/** Destruktor.
	*/
	~ObjectLocator();
	
};

#endif /* OBJECTLOCATOR_H_ */
