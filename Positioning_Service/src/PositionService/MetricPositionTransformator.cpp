//============================================================================
// Datei	: MetricPositionTransformator.cpp
// Autor	: Joel Bartelheimer
// Version	: 1.0
//============================================================================

#include "MetricPositionTransformator.h"

cv::Mat MetricPositionTransformator::Transform(LocatedObject* origin, LocatedObject* tracked)
{
	cv::Mat t(3, 1, CV_64F);			//Verschiebevektor
	cv::Mat Pw(3, 1, CV_64F);			//Tracked in Weltkoordinaten

	double uw = origin->position.x;		//x-Position vom Ursprung
	double vw = origin->position.y;		//y-Position vom Ursprung

	double u0 = tracked->position.x;	//x-Position vom Punkt
	double v0 = tracked->position.y;	//y-Position vom Punkt

	//Bestimmung Verschiebevektor t
	t.at<double>(0, 0) = (tz / f) * (uw - cx);
	t.at<double>(1, 0) = (tz / f) * (vw - cy);
	t.at<double>(2, 0) = tz;

	//Rotationsmatrix mit Phi = 0
	cv::Mat Rz = cv::Mat::zeros(3, 3, CV_64F);
	Rz.at<double>(2, 2) = 1.;

	//Bestimmung der hoehe
	H = ((-b) * fl + p * tz) / (p);

	cv::Mat Pk(3, 1, CV_64F);	//Punktvektor
	Pk.at<double>(0, 0) = ((tz - H) / f) * (u0 - cx);
	Pk.at<double>(1, 0) = ((tz - H) / f) * (v0 - cy);
	Pk.at<double>(2, 0) = tz - H;

	//Umrechnung in Weltkoordinaten
	Pw = Rz.t() * (Pk - t);

	//TODO: ggf. Z-Komponente durch H ersetzen
	return Pw;
}

//Konstruktor
MetricPositionTransformator::MetricPositionTransformator(String calibFilename, double _fl) {
	
	//Einlesen der Kalibrierdatei
	cv::FileStorage fs(calibFilename, cv::FileStorage::READ);
	fs["Extrinsic_Parameters"] >> Ex;
	fs["Camera_Matrix"] >> Cm;
	fs.release();

	tz = 0;

	//Iteration ueber die Extrinsischen Parameter
	//von jedem Bild aus der Kalibration
	for (int i = 0; i < Ex.rows; i++)
	{
		//Extrahieren von r und t (vom i. Bild)
		r = Ex.row(i).colRange(0, 3).t();
		t = Ex.row(i).colRange(3, 6).t();

		//Rotations-Matrix
		cv::Rodrigues(r, R);

		//Zentralpunkt
		ZK = R.t() * (-t);

		//Entfernung zum Optischen Mittelpunkt
		float ZK_lenth = sqrt((ZK.at<double>(0, 0)*ZK.at<double>(0, 0)) +
			(ZK.at<double>(1, 0)*ZK.at<double>(1, 0)) +
			(ZK.at<double>(2, 0)*ZK.at<double>(2, 0)));

		//groesstes tz waehlen
		if ((ZK_lenth + dk) > tz)
		{
			tz = (ZK_lenth + dk);
		}
	}
}

MetricPositionTransformator::~MetricPositionTransformator() {

}
