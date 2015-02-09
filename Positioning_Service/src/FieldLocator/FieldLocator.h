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

class FieldLocator{

private:

	LocatableObject origin;
	LocatableObject reference;
	IPositionService* ps;

public:

	FieldLocator();
	FieldLocator(LocatableObject _origin, LocatableObject _reference);
	vector<Point> locateField(Mat _src);

};

#endif        