#include "Calibrator.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>


using namespace std;
using namespace cv;

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif


Calibrator::Calibrator(){

}

bool Calibrator::runCalibrationAndSave(Settings& s, Size imageSize, Mat&  cameraMatrix, Mat& distCoeffs,
	vector<vector<Point2f> > imagePoints){


	vector<Mat> rvecs, tvecs;
	vector<float> reprojErrs;
	double totalAvgErr = 0;

	bool ok = runCalibration(s, imageSize, cameraMatrix, distCoeffs, imagePoints, rvecs, tvecs,
		reprojErrs, totalAvgErr);
	cout << (ok ? "Calibration succeeded" : "Calibration failed")
		<< ". avg re projection error = " << totalAvgErr;

	if (ok)
		saveCameraParams(s, imageSize, cameraMatrix, distCoeffs, rvecs, tvecs, reprojErrs,
		imagePoints, totalAvgErr);

	return ok;

}


double Calibrator::computeReprojectionErrors(
	const vector<vector<Point3f> >& objectPoints,
	const vector<vector<Point2f> >& imagePoints,
	const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	const Mat& cameraMatrix, const Mat& distCoeffs,
	vector<float>& perViewErrors){


	vector<Point2f> imagePoints2;
	int i, totalPoints = 0;
	double totalErr = 0, err;
	perViewErrors.resize(objectPoints.size());

	for (i = 0; i < (int)objectPoints.size(); ++i)
	{
		projectPoints(Mat(objectPoints[i]), rvecs[i], tvecs[i], cameraMatrix,
			distCoeffs, imagePoints2);
		err = norm(Mat(imagePoints[i]), Mat(imagePoints2), CV_L2);

		int n = (int)objectPoints[i].size();
		perViewErrors[i] = (float)std::sqrt(err*err / n);
		totalErr += err*err;
		totalPoints += n;
	}

	return std::sqrt(totalErr / totalPoints);
}

void Calibrator::calcBoardCornerPositions(Size boardSize, float squareSize, vector<Point3f>& corners,
	Settings::Pattern patternType){

	corners.clear();

	switch (patternType)
	{
	case Settings::CHESSBOARD:
		for (int i = 0; i < boardSize.height; ++i)
			for (int j = 0; j < boardSize.width; ++j)
				corners.push_back(Point3f(float(j*squareSize), float(i*squareSize), 0));
		break;

	default:
		break;
	}

}


bool Calibrator::runCalibration(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
	vector<vector<Point2f> > imagePoints, vector<Mat>& rvecs, vector<Mat>& tvecs,
	vector<float>& reprojErrs, double& totalAvgErr){


	cameraMatrix = Mat::eye(3, 3, CV_64F);
	if (s.flag & CV_CALIB_FIX_ASPECT_RATIO)
		cameraMatrix.at<double>(0, 0) = 1.0;

	distCoeffs = Mat::zeros(8, 1, CV_64F);

	vector<vector<Point3f> > objectPoints(1);
	calcBoardCornerPositions(s.boardSize, s.squareSize, objectPoints[0], s.calibrationPattern);

	objectPoints.resize(imagePoints.size(), objectPoints[0]);

	//Find intrinsic and extrinsic camera parameters
	double rms = calibrateCamera(objectPoints, imagePoints, imageSize, cameraMatrix,
		distCoeffs, rvecs, tvecs, s.flag | CV_CALIB_FIX_K4 | CV_CALIB_FIX_K5);

	cout << "Re-projection error reported by calibrateCamera: " << rms << endl;

	bool ok = checkRange(cameraMatrix) && checkRange(distCoeffs);

	totalAvgErr = computeReprojectionErrors(objectPoints, imagePoints,
		rvecs, tvecs, cameraMatrix, distCoeffs, reprojErrs);

	return ok;
}


void Calibrator::saveCameraParams(Settings& s, Size& imageSize, Mat& cameraMatrix, Mat& distCoeffs,
	const vector<Mat>& rvecs, const vector<Mat>& tvecs,
	const vector<float>& reprojErrs, const vector<vector<Point2f> >& imagePoints,
	double totalAvgErr){

	FileStorage fs(s.outputFileName, FileStorage::WRITE);

	time_t tm;
	time(&tm);
	struct tm *t2 = localtime(&tm);
	char buf[1024];
	strftime(buf, sizeof(buf) - 1, "%c", t2);

	fs << "calibration_Time" << buf;

	if (!rvecs.empty() || !reprojErrs.empty())
		fs << "nrOfFrames" << (int)std::max(rvecs.size(), reprojErrs.size());
	fs << "image_Width" << imageSize.width;
	fs << "image_Height" << imageSize.height;
	fs << "board_Width" << s.boardSize.width;
	fs << "board_Height" << s.boardSize.height;
	fs << "square_Size" << s.squareSize;

	if (s.flag & CV_CALIB_FIX_ASPECT_RATIO)
		fs << "FixAspectRatio" << s.aspectRatio;

	if (s.flag)
	{
		sprintf(buf, "flags: %s%s%s%s",
			s.flag & CV_CALIB_USE_INTRINSIC_GUESS ? " +use_intrinsic_guess" : "",
			s.flag & CV_CALIB_FIX_ASPECT_RATIO ? " +fix_aspectRatio" : "",
			s.flag & CV_CALIB_FIX_PRINCIPAL_POINT ? " +fix_principal_point" : "",
			s.flag & CV_CALIB_ZERO_TANGENT_DIST ? " +zero_tangent_dist" : "");
		cvWriteComment(*fs, buf, 0);

	}

	fs << "flagValue" << s.flag;

	fs << "Camera_Matrix" << cameraMatrix;
	fs << "Distortion_Coefficients" << distCoeffs;

	fs << "Avg_Reprojection_Error" << totalAvgErr;
	if (!reprojErrs.empty())
		fs << "Per_View_Reprojection_Errors" << Mat(reprojErrs);

	if (!rvecs.empty() && !tvecs.empty())
	{
		CV_Assert(rvecs[0].type() == tvecs[0].type());
		Mat bigmat((int)rvecs.size(), 6, rvecs[0].type());
		for (int i = 0; i < (int)rvecs.size(); i++)
		{
			Mat r = bigmat(Range(i, i + 1), Range(0, 3));
			Mat t = bigmat(Range(i, i + 1), Range(3, 6));

			CV_Assert(rvecs[i].rows == 3 && rvecs[i].cols == 1);
			CV_Assert(tvecs[i].rows == 3 && tvecs[i].cols == 1);
			//*.t() is MatExpr (not Mat) so we can use assignment operator
			r = rvecs[i].t();
			t = tvecs[i].t();
		}
		cvWriteComment(*fs, "a set of 6-tuples (rotation vector + translation vector) for each view", 0);
		fs << "Extrinsic_Parameters" << bigmat;
	}

	if (!imagePoints.empty())
	{
		Mat imagePtMat((int)imagePoints.size(), (int)imagePoints[0].size(), CV_32FC2);
		for (int i = 0; i < (int)imagePoints.size(); i++)
		{
			Mat r = imagePtMat.row(i).reshape(2, imagePtMat.cols);
			Mat imgpti(imagePoints[i]);
			imgpti.copyTo(r);
		}
		fs << "Image_points" << imagePtMat;
	}

}

void Calibrator::start(VideoCapture inputCapture){

	const string inputSettingsFile = "in_VID5.xml";

	// Read the settings
	FileStorage fs(inputSettingsFile, FileStorage::READ);

	if (!fs.isOpened())
	{
		cout << "Could not open the configuration file: \"" << inputSettingsFile << "\"" << endl;
		return;
	}

	s.readSettings(fs["Settings"]);

	// close Settings file
	fs.release();                                         

	//Check input data
	if (!s.goodInput)
	{
		cout << "Invalid input detected. Application stopping. " << endl;
		return;
	}

	vector<vector<Point2f> > imagePoints;
	Mat cameraMatrix, distCoeffs;
	Size imageSize;
	int mode = s.inputType ==  DETECTION;//Capturing?
	clock_t prevTimestamp = 0;
	const Scalar RED(0, 0, 255), GREEN(0, 255, 0);
	const char ESC_KEY = 27;


	while (true)
	{
		Mat view;	
		bool blinkOutput = false;

		//Open Camera
		if (s.inputType == Settings::CAMERA && !inputCapture.isOpened()){

			inputCapture.open(s.cameraID);
		}


		//Get Frame
		if (inputCapture.isOpened())
		{
			inputCapture >> view;
		}


		//-----  If no more image, or got enough, then stop calibration and show result -------------
		if (mode == CAPTURING && imagePoints.size() >= (unsigned)s.nrFrames)
		{
			if (runCalibrationAndSave(s, imageSize, cameraMatrix, distCoeffs, imagePoints))
				mode = CALIBRATED;
			else
				mode = DETECTION;
		}

		// Format input image.
		imageSize = view.size();  

		vector<Point2f> pointBuf;
		bool found;

		switch (s.calibrationPattern) // Find feature points on the input format
		{
		case Settings::CHESSBOARD:
			found = findChessboardCorners(view, s.boardSize, pointBuf,
				CV_CALIB_CB_ADAPTIVE_THRESH | CV_CALIB_CB_FAST_CHECK | CV_CALIB_CB_NORMALIZE_IMAGE);
			break;

		default:
			found = false;
			break;
		}

		// If done with success,
		if (found)                
		{
			// improve the found corners' coordinate accuracy for chessboard
			if (s.calibrationPattern == Settings::CHESSBOARD)
			{
				Mat viewGray;
				cvtColor(view, viewGray, COLOR_BGR2GRAY);
				cornerSubPix(viewGray, pointBuf, Size(11, 11),
					Size(-1, -1), TermCriteria(CV_TERMCRIT_EPS + CV_TERMCRIT_ITER, 30, 0.1));
			}

			if (mode == CAPTURING && inputCapture.isOpened() )
			{
				char key = (char)waitKey(inputCapture.isOpened() ? 10 : 1000);

				if (key == 'x'){
					imagePoints.push_back(pointBuf);
					prevTimestamp = clock();
					blinkOutput = inputCapture.isOpened();
				}
			}

			// Draw the corners.
			drawChessboardCorners(view, s.boardSize, Mat(pointBuf), found);
		}

		//----------------------------- Output Text ------------------------------------------------
		string msg = (mode == CAPTURING) ? "100/100" : 
			mode == CALIBRATED ? "Calibration completed. Press 's' to restart. Quit with ESC." : "Press 's' to start";
		int baseLine = 0;
		Size textSize = getTextSize(msg, 1, 1, 1, &baseLine);
		Point textOrigin(20, 20);
		//Current number of frames
		if (mode == CAPTURING)
		{
				msg = format("Press 'x' to capture a frame. Progress: %d/%d", (int)imagePoints.size(), s.nrFrames);
		}

		putText(view, msg, textOrigin, 1, 1, mode == CALIBRATED ? GREEN : RED);

		if (blinkOutput)
			bitwise_not(view, view);


		//------------------------------ Show image and check for input commands -------------------
		imshow("Calibration", view);
		char key = (char)waitKey(inputCapture.isOpened() ? 10 : 1000);

		if (key == ESC_KEY)
			break;

		if (inputCapture.isOpened() && key == 's')
		{
			mode = CAPTURING;
			imagePoints.clear();
		}
	}
}

