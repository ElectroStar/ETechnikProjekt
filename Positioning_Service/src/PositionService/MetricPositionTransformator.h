//============================================================================
// Datei	: MetricPositionTransformator.h
// Autor	: Joel Bartelheimer
// Version	: 1.0
//============================================================================

#ifndef METRICPOSITIONTRANSFORMATOR__H_
#define METRICPOSITIONTRANSFORMATOR__H_

#include <stdint.h>

/** Klasse zur Berechnung der metrischen Position.
 *  @author		Joel Bartelheimer
 *  @date		16.02.2015
 */
class MetricPositionTransformator {

private:
	cv::Mat Cm;			//Kamera Matrix
	cv::Mat Ex;			//Extrinsische Parameter

	double dk;			//dicke der Kalibrierplatte
	double tz;			//Entfernung zum Optischen Mittelpunkt

	double f;			//Fokuaslaenge fx = fy
	double cx;
	double cy;

public:
	cv::Mat Transform(LocatedObject origin, LocatedObject tracked);

	MetricPositionTransformator(String calibFilename);
	~MetricPositionTransformator();

};

#endif /* METRICPOSITIONTRANSFORMATOR__H_ */
