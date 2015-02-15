//============================================================================
// Datei	: TailorFieldView.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "TailorFieldView.h"

TailorFieldView::TailorFieldView(const Point _first, const Point _second) : first(_first), second(_second) {}

TailorFieldView::~TailorFieldView() {}

void TailorFieldView::filter(Mat &_input, Mat &_output) const {

	_output = _input(Rect(first,second));
}

void TailorFieldView::setlowerLeft(const Point _first) {

	first = _first;
}

void TailorFieldView::setupperRight(const Point _second) {

	second =_second;
}
