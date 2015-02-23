//============================================================================
// Datei	: line.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef LINE_H
#define LINE_H

#include <cmath>

/** Klasse um den Abstand eines Punktes P zu einer Gerade g zu berechnen.
*  @author		Eric
*  @date		23.02.2015
*/
class Line {

private:

    //SSteigung m
    double m;
    double n;

public:

    /** Konstruktor.
    *  	@param[in] p1x 	Punkt 1 x
    *  	@param[in] p1y 	Punkt 1 y
    *  	@param[in] p2x 	Punkt 2 x
    *  	@param[in] p2y  Punkt 2 y
    */
    Line(double p1x, double p1y, double p2x, double p2y);
    ~Line();

    /** Methode zum Berechnen der Distanz d.
    *  	@param[in] px 	Punkt x
    *  	@param[in] py 	Punkt y
    */
    double calcDistance(double px, double py);
};

#endif // LINE_H
