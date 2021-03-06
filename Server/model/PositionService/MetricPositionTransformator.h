//============================================================================
// Datei	: MetricPositionTransformator.h
// Autor	: Joel Bartelheimer
// Version	: 1.0
//============================================================================

#ifndef METRICPOSITIONTRANSFORMATOR__H_
#define METRICPOSITIONTRANSFORMATOR__H_

#include <stdint.h>

#include "LocatedObject.h"

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

    /** Methode zur Transformation von Pixeldaten in metrische Daten.
     * @param[in] origin        Referenzlandmarke
     * @param[in] tracked       Gefundenes Objekt
     * @return                  Positionsmatrix
     */
    cv::Mat transform(const LocatedObject &origin,const LocatedObject &tracked);

    /** Konstruktor
     * @param calibFilename     Parameterdatei
     * @param _dk               Dicke der Kalibrierplatte
     */
    MetricPositionTransformator(const String& calibFilename,const double& _dk);

    /**
    * Destruktor
    */
    ~MetricPositionTransformator();

};

#endif /* METRICPOSITIONTRANSFORMATOR__H_ */
