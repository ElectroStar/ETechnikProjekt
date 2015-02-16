//============================================================================
// Datei	: FieldLocator.h
// Autor	: Christian Jungblut
// Version	: 1.0
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>
#include "../PositionService/LocatableObject.h"
#include "../PositionService/IPositionService.h"

using namespace std;
using namespace cv;

#ifndef FIELDLOCATOR_H
#define	FIELDLOCATOR_H

/** Klasse zur Erkennung der Landmarken.
 *  @author		Christian
 *  @date		11.02.2015
 */
class FieldLocator{

private:

	//Beschreibung der gesuchten Landmarken
	LocatableObject origin;
	LocatableObject reference;
	IPositionService* ps;

public:

	/** Konstruktor.
	*/
	FieldLocator();
	
	/** Erweiterter Konstruktor.
	*  	@param[in] _origin 		Landmarke(Ursprung)
	*  	@param[in] _reference 	Landmarke(Referenz)
	*/
	FieldLocator(LocatableObject _origin, LocatableObject _reference);
	
	/** Methode zur Lokalisierung der Landmarken.
	*  	@param[in] _src 		Ausgangsbild
	*  	@return 				Gefundene Objekte gemaess Muster
	*/
	vector<Point> locateField(Mat _src);

};

#endif        