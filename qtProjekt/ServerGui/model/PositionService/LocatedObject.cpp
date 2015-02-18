//============================================================================
// Datei	: LocatedObject.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "LocatedObject.h"

LocatedObject::LocatedObject() {

}

LocatedObject::LocatedObject(Point2d _p, double _length, LocatableObject _spec) {
	
	position = _p;
	edgeLengthPx = _length;
	spec = _spec;

}

LocatedObject::~LocatedObject() {

}

