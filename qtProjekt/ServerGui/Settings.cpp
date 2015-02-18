//============================================================================
// Datei	: Settings.cpp
// Autor	: Christian Jungblut + Codebeispiel aus OpenCV
// Version	: 1.0
//============================================================================

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


bool Settings::readSettings(){

    // Read the settings
    FileStorage fs(calibConfigFile, FileStorage::READ);

    if (!fs.isOpened())
    {
        fs.release();
        return false;
    }

    FileNode node = fs["Settings"];

    node["landMarkShapeOrigin"] >> landMarkShapeOrigin;
    node["landMarkShapeReference"] >> landMarkShapeReference;

    node["landMarkColorOriginMin"] >> landMarkColorOriginMin;
    node["landMarkColorOriginMax"] >> landMarkColorOriginMax;
    node["landMarkColorReferenceMin"] >> landMarkColorReferenceMin;
    node["landMarkColorReferenceMax"] >> landMarkColorReferenceMax;

    node["landMarkSizeOrigin"] >> landMarkSizeOrigin;
    node["landMarkSizeReference"] >> landMarkSizeReference;

    node["objectShape"] >> objectShape;
    node["objectColorMin"] >> objectColorMin;
    node["objectColorMax"] >> objectColorMax;
    node["objectSizeCM"] >> objectSizeCM;

    node["harrisCornerBlockSize"] >> harrisCornerBlockSize;
    node["harrisCornerApertureSize"] >> harrisCornerApertureSize;
    node["harrisCornerVariance"] >> harrisCornerVariance;
    node["harrisCornerThresh"] >> harrisCornerThresh;
    node["harrisCornerMergeArea"] >> harrisCornerMergeArea;

    node["houghCircleThreshold"] >> houghCircleThreshold;

    node["gaussianStandardDeviation"] >> gaussianStandardDeviation;
    node["gaussianSize"] >> gaussianSize;


	node["BoardSize_Width"] >> boardSize.width;
	node["BoardSize_Height"] >> boardSize.height;
	node["Calibrate_Pattern"] >> patternToUse;
	node["Square_Size"] >> squareSize;
	node["Calibrate_NrOfFrameToUse"] >> nrFrames;
	node["Calibrate_FixAspectRatio"] >> aspectRatio;
	node["Write_DetectedFeaturePoints"] >> bwritePoints;
    node["Write_extrinsicParameters"] >> bwriteExtrinsics;
    node["calibPanelHeightMM"] >> calibPanelHeightMM;
	node["Write_outputFileName"] >> outputFileName;
	node["Calibrate_AssumeZeroTangentialDistortion"] >> calibZeroTangentDist;
	node["Calibrate_FixPrincipalPointAtTheCenter"] >> calibFixPrincipalPoint;
	node["Input"] >> input;
	interprate();

    // close Settings file
    fs.release();

    return true;

}
    

bool Settings::writeSettings(){

    FileStorage fs(calibConfigFile, FileStorage::WRITE);

    if (!fs.isOpened())
    {
        fs.release();
        return false;
    }

    fs << "Settings" << "{";

    fs << "landMarkShapeOrigin" << landMarkShapeOrigin;
    fs << "landMarkShapeReference" << landMarkShapeReference;

    fs << "landMarkColorOriginMin" << landMarkColorOriginMin;
    fs << "landMarkColorOriginMax" << landMarkColorOriginMax;
    fs << "landMarkColorReferenceMin" << landMarkColorReferenceMin;
    fs << "landMarkColorReferenceMax" << landMarkColorReferenceMax;

    fs << "landMarkSizeOrigin" << landMarkSizeOrigin;
    fs << "landMarkSizeReference" << landMarkSizeReference;

    fs << "objectShape" << objectShape;
    fs << "objectColorMin" << objectColorMin;
    fs << "objectColorMax" << objectColorMax;
    fs << "objectSizeCM" << objectSizeCM;

    fs << "harrisCornerBlockSize" << harrisCornerBlockSize;
    fs << "harrisCornerApertureSize" << harrisCornerApertureSize;
    fs << "harrisCornerVariance" << harrisCornerVariance;
    fs << "harrisCornerThresh" << harrisCornerThresh;
    fs << "harrisCornerMergeArea" << harrisCornerMergeArea;

    fs << "houghCircleThreshold" << houghCircleThreshold;

    fs << "gaussianStandardDeviation" << gaussianStandardDeviation;
    fs << "gaussianSize" << gaussianSize;

    fs << "BoardSize_Width" << boardSize.width;
    fs << "BoardSize_Height" << boardSize.height;
    fs << "Calibrate_Pattern" << patternToUse;
    fs << "Square_Size" << squareSize;
    fs << "Calibrate_NrOfFrameToUse" << nrFrames;
    fs << "Calibrate_FixAspectRatio" << aspectRatio;
    fs << "Write_DetectedFeaturePoints" << bwritePoints;
    fs << "Write_extrinsicParameters" << bwriteExtrinsics;
    fs << "calibPanelHeightMM" << calibPanelHeightMM;
    fs << "Write_outputFileName" << outputFileName;
    fs << "Calibrate_AssumeZeroTangentialDistortion" << calibZeroTangentDist;
    fs << "Calibrate_FixPrincipalPointAtTheCenter" << calibFixPrincipalPoint;
    fs << "Input" << input;
    fs << "}";

    fs.release();
    return true;
}

Settings& Settings::instance(){

    static Settings settings;
    return settings;
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
