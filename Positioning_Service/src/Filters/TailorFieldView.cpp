/*
 * TailorFieldView.cpp
 *
 *  Created on: Dec 12, 2014
 *      Author: user
 */

#include "TailorFieldView.h"

TailorFieldView::TailorFieldView(const Point _lowerLeft, const Point _upperRight) : lowerLeft(_lowerLeft), upperRight(_upperRight) {}

TailorFieldView::~TailorFieldView() {}

void TailorFieldView::filter(Mat &input, Mat &output) const {

	uint32_t hight = upperRight.y - lowerLeft.y;
	uint32_t width = upperRight.x - lowerLeft.x;

	output = input(Rect(lowerLeft.x, lowerLeft.y, hight, width));
}

void TailorFieldView::setlowerLeft(const Point &_lowerLeft) {

	lowerLeft=_lowerLeft;
}

void TailorFieldView::setupperRight(const Point &_upperRight) {

	upperRight=_upperRight;
}
