/*
 * ImageFilter.h
 *
 *  Created on: Dec 12, 2014
 *      Author: user
 */

#ifndef IMAGEFILTER_H_
#define IMAGEFILTER_H_

#include "opencv2/core/core.hpp"

using namespace cv;

class ImageFilter {

private:

public:
	virtual ~ImageFilter() {};
	virtual void filter(Mat &input, Mat &output) const = 0;
};

#endif /* IMAGEFILTER_H_ */
