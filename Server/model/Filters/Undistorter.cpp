//============================================================================
// Datei	: Undistorter.cpp
// Autor	: Eric Buschermoehle
// Version  : 1.0
//============================================================================

#include "Undistorter.h"

Undistorter::Undistorter() : cameraMatrix(Mat(3,3,CV_32FC1)), distCoeffs(Mat(5,1,CV_32FC1)) {}

Undistorter::~Undistorter() {}

void Undistorter::filter(Mat &distorted, Mat &undistorted) const{

	undistort(distorted, undistorted, cameraMatrix, distCoeffs);

}

int Undistorter::readParam(const string path) {

    FileStorage fs(path, FileStorage::READ);

    if (!fs.isOpened()) {
        return -1;
    }

    fs["Camera_Matrix"] >> cameraMatrix;
    fs["Distortion_Coefficients"] >> distCoeffs;

    fs.release();
    return 1;
}



