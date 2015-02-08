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

class LocatedObject {

public:

	Point position;
	int edgeLengthPx;
	LocatableObject spec;

public:

	LocatedObject();
	LocatedObject(Point _p, int _length, LocatableObject _spec);
	~LocatedObject();
};

#endif /* LOCATEDOBJECT_H_ */
