//============================================================================
// Datei	: LocatedObject.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "LocatedObject.h"

LocatedObject::LocatedObject() {

}

LocatedObject::LocatedObject(Point _p, int _length, LocatableObject _spec) {
	
	position = _p;
	edgeLengthPx = _length;
	spec = _spec;

}

LocatedObject::~LocatedObject() {

}

