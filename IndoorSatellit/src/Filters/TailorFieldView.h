/*
 * TailorFieldView.h
 *
 *  Created on: Dec 12, 2014
 *      Author: user
 */

#ifndef TAILORFIELDVIEW_H_
#define TAILORFIELDVIEW_H_

#include "opencv2/core/core.hpp"

#include "ImageFilter.h"

class TailorFieldView : ImageFilter {

private:
	Point lowerLeft;
	Point upperRight;

public:
	TailorFieldView(const Point _lowerLeft, const Point _upperRight);
	~TailorFieldView();
	void filter(Mat &input, Mat &output) const;

	void setlowerLeft(const Point &_lowerLeft);
	void setupperRight(const Point &_upperRight);

};

#endif /* TAILORFIELDVIEW_H_ */
