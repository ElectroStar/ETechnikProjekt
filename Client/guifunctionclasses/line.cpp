//============================================================================
// Datei	: line.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "line.h"

Line::Line(double p1x, double p1y, double p2x, double p2y) {

    m = (p2y-p1y)/(p2x-p1x);
    n = p1y-m*p1x;

}

Line::~Line() {

}

double Line::calcDistance(double px, double py) {

    double zaehler = m*px-py+n;
    double nenner = sqrt(m*m+1);
    return std::abs(zaehler/nenner);

}

