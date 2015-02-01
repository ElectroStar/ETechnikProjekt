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

class LocatedObject {

private:
	cv::Point position;
	uint32_t lengthPixel;

public:

	LocatedObject();
	~LocatedObject();
};

#endif /* LOCATEDOBJECT_H_ */
