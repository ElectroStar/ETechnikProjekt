//============================================================================
// Datei	: CropFieldView.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "CropFieldView.h"

CropFieldView::CropFieldView(const Point _first, const Point _second) : first(_first), second(_second) {}

CropFieldView::~CropFieldView() {}

void CropFieldView::filter(Mat &_input, Mat &_output) const {

	_output = _input(Rect(first,second));
}
