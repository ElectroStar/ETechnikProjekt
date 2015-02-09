//============================================================================
// Datei	: ObjectLocator.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef OBJECTLOCATOR_H_
#define OBJECTLOCATOR_H_

#include "IPositionService.h"

class ObjectLocator : public IPositionService {

private:

	/// Corner detection parameters
	int blockSize = 4;
	int apertureSize = 3;
	double k = 0.1;
	int thresh = 180;
	int max_thresh = 255;

	//Circle and Corner storage
	vector<Point> cornerP;
	vector<Vec3f> circles;

public:
	ObjectLocator();
	~ObjectLocator();
	vector<LocatedObject> getAllObjects(Mat src, LocatableObject spec);
};

#endif /* OBJECTLOCATOR_H_ */
