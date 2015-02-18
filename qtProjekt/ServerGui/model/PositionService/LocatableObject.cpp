//============================================================================
// Datei	: LocatableObject.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "LocatableObject.h"

LocatableObject::LocatableObject(){

}

LocatableObject::LocatableObject(Form _form, int _colorMin, int _colorMax, double _sizeInCm) {
	
	form = _form;
	colorMin = _colorMin;
	colorMax = _colorMax;
	sizeInCm = _sizeInCm;

}

LocatableObject::~LocatableObject() {

}

