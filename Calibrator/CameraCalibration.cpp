#include <stdio.h>
#include "Settings.h"
#include "Calibrator.h"

#include <opencv2/core/core.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/highgui/highgui.hpp>

using namespace std;
using namespace cv;

#ifndef _CRT_SECURE_NO_WARNINGS
# define _CRT_SECURE_NO_WARNINGS
#endif


int main(int argc, const char* argv[])
{

	Calibrator calib;
	VideoCapture cap;

	calib.start(cap);

}

