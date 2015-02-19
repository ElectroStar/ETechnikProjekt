//============================================================================
// Datei	: ModelCreator.h
// Autor	: Christian Jungblut
// Version	: 1.0
//============================================================================

#include <stdio.h>
#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"

using namespace std;
using namespace cv;

#ifndef MODELCREATOR_H_
#define MODELCREATOR_H_

/** Klasse zur Modellierung des Tracking-Felds.
*  @author		Christian
*  @date		14.02.2015
*/
class ModelCreator
{

private:

	Mat model;
    double metricFieldWidth;
    double metricFieldHeight;
    int pixelFieldWidth;
    int pixelFieldHeight;

public:

	/** Konstruktor.
	*/
	ModelCreator(int);

	/** Methode zum Berechnen der Objektposition.
	*  	@param[in] _x 	Metrische Position auf der x-Achse
	*  	@param[in] _y 	Metrische Position auf der y-Achse
	*  	@param[in] _x2 	Metrische Breite des Feldes
	*  	@param[in] _y2 	Metrische Hoehe des Feldes
	*/
    Point calcPosition(double _x, double _y, double _x2, double _y2);

	/** Methode zum Zeichnen der Objektposition.
	*  	@param[in] _p	Position im Bild
	*/
	void drawPosition(Point _p);

	/** Getter fuer das aktuelle Bild.
	*  	@return 	Aktuelles Bild
	*/
    Mat& getModel();
	
	/** Getter fuer die reale Feldbreite.
	*  	@return 	Feldbreite in cm
	*/
    double getMetricFieldWidth();

	/** Setter fur die reale Feldbreite.
	*  	@param[in] _x 	Feldbreite in cm
	*/
    void setMetricFieldWidth(double _x);

	/** Getter fuer die reale Feldhoehe.
	*  	@return 	Feldhoehe in cm
	*/
    double getMetricFieldHeight();

	/** Setter fur die reale Feldhoehe.
	*  	@param[in] _y 	Feldhoehe in cm
	*/
    void setMetricFieldHeight(double _y);

	/** Getter fuer die Bildbreite.
	*  	@return 	Bildbreite in Pixel
	*/
	int getPixelFieldWidth();

	/** Setter fuer die Bildbreite.
	*  	@param[in] _x 	Bildbreite in Pixel
	*/
	void setPixelFieldWidth(int _x);

	/** Getter fuer die Bildhoehe.
	*  	@return 	Bildhoehe in Pixel
	*/
	int getPixelFieldHeight();

	/** Setter fuer die Bildhoehe.
	*  	@param[in] _x 	Bildhoehe in Pixel
	*/
	void setPixelFieldHeight(int _y);


	/** Destruktor.
	*/
	~ModelCreator();
};

#endif /* MODELCREATOR_H_ */
