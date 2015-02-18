//============================================================================
// Datei	: LocatedObject.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef LOCATEDOBJECT_H_
#define LOCATEDOBJECT_H_

#include "opencv2/core/core.hpp"
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <stdint.h>
#include "LocatableObject.h"

using namespace cv;

/** Klasse zur Speicherung gefundener Objekte.
 *  @author		Christian
 *  @date		11.02.2015
 */
class LocatedObject {

public:
	
    Point2d position;
    double edgeLengthPx;
	LocatableObject spec;

public:

	/** Konstruktor.
	*/
	LocatedObject();
	
	/** Erweiterter Konstruktor.
	*  	@param[in] _p 		Position
	*  	@param[in] _length 	Laenge der Objektkante
	*  	@param[in] _spec 	Objektspezifikaion
	*/
    LocatedObject(Point2d _p, double _length, LocatableObject _spec);
	
	/** Destruktor.
	*/
	~LocatedObject();
};

#endif /* LOCATEDOBJECT_H_ */
