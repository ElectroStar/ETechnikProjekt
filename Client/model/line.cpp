//============================================================================
// Datei	: line.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "line.h"
#include <climits>
#include <float.h>

Line::Line(double p1x, double p1y, double p2x, double p2y) {

    if (p2y-p1y == 0) {
        m=0;
        n = p1y;
    }

    else if (p2x-p1x == 0) {
        m = (p2y-p1y)/0.0000001;
        n = p1y-m*p1x;
    }

    else {
        m = (p2y-p1y)/(p2x-p1x);
        n = p1y-m*p1x;
    }
}

Line::~Line() {

}

double Line::calcDistance(double px, double py) {

    double zaehler = m*px-py+n;
    double nenner = sqrt(m*m+1);
    return std::abs(zaehler/nenner);

}

void Line::getMax(double &minX, double &minY, double &maxX, double &maxY, int ImCordX, int ImCordY) {

    double yMaxTemp = m*ImCordX+n;
    double xMaxTemp = (ImCordY-n)/m;

    double yMinTemp = n;
    double xMinTemp = -n/m;

    if(yMaxTemp > ImCordY) {
        maxY = ImCordY;
        maxX = xMaxTemp;
    }
    else {
        maxY = yMaxTemp;
        maxX = ImCordX;
    }

    if(yMinTemp < 0) {
        minY = 0;
        minX = xMinTemp;
    }
    else {
        minY = yMinTemp;
        minX = 0;
    }
}

