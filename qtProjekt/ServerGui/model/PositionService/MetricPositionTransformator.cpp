//============================================================================
// Datei	: MetricPositionTransformator.cpp
// Autor	: Joel Bartelheimer
// Version	: 1.0
//============================================================================

#include "MetricPositionTransformator.h"
#include "opencv2/opencv.hpp"

cv::Mat MetricPositionTransformator::transform(const LocatedObject &origin, const LocatedObject &tracked)
{
    //Eventuelle verbesserungen:
    // - Erste berechunungen schon im Konstruktor (z.B. tz / f )
    // - Transponierte Rotationsmatrix als Konstante

    cv::Mat t(3, 1, CV_64F);					//Verschiebevektor
    cv::Mat Pw(3, 1, CV_64F);					//Tracked in Weltkoordinaten

    double uw = origin.position.x;				//x-Position vom Ursprung
    double vw = origin.position.y;				//y-Position vom Ursprung

    double u0 = tracked.position.x;			//x-Position vom Punkt
    double v0 = tracked.position.y;			//y-Position vom Punkt
    double p = tracked.edgeLengthPx;			//Breite des Objektes in px
    double b = tracked.spec.sizeInCm * 10;	//Breite des Objektes in mm
    double H = 0;									//Hoehe des Objektes in mm

    //Bestimmung Verschiebevektor t
    t.at<double>(0, 0) = ((this->tz) / (this->f)) * (uw - (this->cx));
    t.at<double>(1, 0) = ((this->tz) / (this->f)) * (vw - (this->cy));
    t.at<double>(2, 0) = this->tz;

    //Rotationsmatrix mit Phi = 0
    cv::Mat Rz = cv::Mat::zeros(3, 3, CV_64F);
    Rz.at<double>(0, 0) = 1.;
    Rz.at<double>(1, 1) = 1.;
    Rz.at<double>(2, 2) = 1.;

    //Bestimmung der hoehe
    H = (((-b) * f) + (p * tz)) / (p);

    std::cout << H << std::endl;

    cv::Mat Pk(3, 1, CV_64F);	//Punktvektor
    Pk.at<double>(0, 0) = ((this->tz - H) / this->f) * (u0 - this->cx);
    Pk.at<double>(1, 0) = ((this->tz - H) / this->f) * (v0 - this->cy);
    Pk.at<double>(2, 0) = this->tz - H;

    //Umrechnung in Weltkoordinaten
    Pw = Rz.t() * (Pk - t);

    //TODO: ggf. Z-Komponente durch H ersetzen
    return Pw;
}

//Konstruktor
MetricPositionTransformator::MetricPositionTransformator(const String& calibFilename, const double& _dk) {

    //Zuweisung
    this->dk = _dk;

    //Deklaration
    cv::Mat r(3, 1, CV_64F);	//Rodrigues-Vector	(rotation)
    cv::Mat t(3, 1, CV_64F);	//Verschiebungs-Vector (translation)
    cv::Mat R(3, 3, CV_64F);	//Rodrigues-Maxtrix
    cv::Mat ZK(3, 1, CV_64F);	//Zentralpunkt

    //Einlesen der Kalibrierdatei
    cv::FileStorage fs(calibFilename, cv::FileStorage::READ);
    fs["Extrinsic_Parameters"] >> this->Ex;
    fs["Camera_Matrix"] >> this->Cm;
    fs.release();

    //Zuweisung der Eingelesenen Parameter
    this->f = Cm.at<double>(0, 0);
    this->cx = Cm.at<double>(0, 2);
    this->cy = Cm.at<double>(1, 2);

    this->tz = 0;

    double tz_tmp = 0;
    //Iteration ueber die Extrinsischen Parameter
    //von jedem Bild aus der Kalibration
    for (int i = 0; i < this->Ex.rows; i++)
    {
        //Extrahieren von r und t (vom i. Bild)
        r = this->Ex.row(i).colRange(0, 3).t();
        t = this->Ex.row(i).colRange(3, 6).t();

        //Rotations-Matrix
        cv::Rodrigues(r, R);

        //Zentralpunkt
        ZK = R.t() * (-t);

        //Entfernung zum Optischen Mittelpunkt
        float ZK_lenth = sqrt((ZK.at<double>(0, 0)*ZK.at<double>(0, 0)) +
            (ZK.at<double>(1, 0)*ZK.at<double>(1, 0)) +
            (ZK.at<double>(2, 0)*ZK.at<double>(2, 0)));

        //groesstes tz waehlen
        tz_tmp = (ZK_lenth + dk);
        if (tz_tmp > (this->tz))
        {
            this->tz = tz_tmp;
        }
    }
}

MetricPositionTransformator::~MetricPositionTransformator() {

}
