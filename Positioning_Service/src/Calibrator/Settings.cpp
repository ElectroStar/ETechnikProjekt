#include "Settings.h"
#include <iostream>
#include <sstream>
#include <time.h>
#include <stdio.h>


using namespace std;
using namespace cv;

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif


void Settings::readSettings(const FileNode& node){

	node["BoardSize_Width"] >> boardSize.width;
	node["BoardSize_Height"] >> boardSize.height;
	node["Calibrate_Pattern"] >> patternToUse;
	node["Square_Size"] >> squareSize;
	node["Calibrate_NrOfFrameToUse"] >> nrFrames;
	node["Calibrate_FixAspectRatio"] >> aspectRatio;
	node["Write_DetectedFeaturePoints"] >> bwritePoints;
	node["Write_extrinsicParameters"] >> bwriteExtrinsics;
	node["Write_outputFileName"] >> outputFileName;
	node["Calibrate_AssumeZeroTangentialDistortion"] >> calibZeroTangentDist;
	node["Calibrate_FixPrincipalPointAtTheCenter"] >> calibFixPrincipalPoint;
	node["Input"] >> input;
	interprate();
}
    
void Settings::interprate(){

	goodInput = true;
	if (boardSize.width <= 0 || boardSize.height <= 0)
	{
		cerr << "Invalid Board size: " << boardSize.width << " " << boardSize.height << endl;
		goodInput = false;
	}

	if (squareSize <= 10e-6)
	{
		cerr << "Invalid square size " << squareSize << endl;
		goodInput = false;
	}

	if (nrFrames <= 0)
	{
		cerr << "Invalid number of frames " << nrFrames << endl;
		goodInput = false;
	}

	if (input.empty()) // Check for valid input
		inputType = INVALID;
	else
	{
		if (input[0] >= '0' && input[0] <= '9')
		{
			stringstream ss(input);
			ss >> cameraID;
			inputType = CAMERA;
		}
	}

	if (inputType == INVALID)
	{
		cerr << " Inexistent input: " << input;
		goodInput = false;
	}

	flag = 0;
	if (calibFixPrincipalPoint) flag |= CALIB_FIX_PRINCIPAL_POINT;
	if (calibZeroTangentDist) flag |= CALIB_ZERO_TANGENT_DIST;
	if (aspectRatio) flag |= CALIB_FIX_ASPECT_RATIO;
	calibrationPattern = NOT_EXISTING;
	if (!patternToUse.compare("CHESSBOARD")) calibrationPattern = CHESSBOARD;
	if (calibrationPattern == NOT_EXISTING)
	{
		cerr << " Inexistent camera calibration mode: " << patternToUse << endl;
		goodInput = false;
	}

}
