//============================================================================
// Datei	: Calibrator.h
// Autor	: Christian Jungblut + Codebeispiel aus OpenCV
// Version	: 1.0
//============================================================================

#include <cstdlib>
#include <string>
#include "Settings.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#ifndef CALIBRATOR_H
#define	CALIBRATOR_H

/** Klasse zur Kalibrierung einer Kamera.
 *  @author		Christian
 *  @date		21.12.2014
 */
class Calibrator{

public:
	
	/** Konstruktor.
	*/
	Calibrator();
	
	/** Methode zur Durchfuehrung der Kalibrierung.
	*  	@param[in] inputCapture 	Kameraobjekt
	*/
	void start(VideoCapture inputCapture);


private:

	enum { DETECTION = 0, CAPTURING = 1, CALIBRATED = 2 };
	Settings s;

	/** Interne Methode zur Erkennung des Kalibriermusters.
	*/
	bool runCalibrationAndSave(Settings& s, Size imageSize, Mat&  cameraMatrix, Mat& distCoeffs,
		vector<vector<Point2f> > imagePoints);

	/** Methode zur Berechnung des Kalibirerfehlers.
	*/
	double computeReprojectionErrors(
		const vector<vector<Point3f> >& objectPoints,
		const vector<vector<Point2f> >& imagePoints,
		const vector<Mat>& rvecs, const vector<Mat>& tvecs,
		const Mat& cameraMatrix, const Mat& distCoeffs,
		vector<float>& perViewErrors);

	/** Methode zur Berechnung der Kantenpunkte.
	*/
	void calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners,
		Settings::Pattern patternType);

		
	/** Interne Methode zum Starten des Kalibriervorgangs.
	*/
	bool runCalibration(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
		vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs,
		vector<float>& reprojErrs, double& totalAvgErr);

		
	/** Methode zur Speicherung der ermittelten Parameter.
	*/
	void saveCameraParams(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
		const vector<Mat>& rvecs, const vector<Mat>& tvecs,
		const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints,
		double totalAvgErr);

};

#endif                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                                          