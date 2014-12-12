//============================================================================
// Datei	: FieldLocator.h
// Autor	: Christian Jungblut
// Version	: 1.0
//============================================================================

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#ifndef FIELDLOCATOR_H
#define	FIELDLOCATOR_H

class FieldLocator{

private:

	LocatableObject origin;
	LocatableObject fieldBoundaries;

public:

	FieldLocator();
	vector<Point> locateField(Mat in);

};

#endif        