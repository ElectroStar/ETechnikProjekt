
#ifndef UNDISTORTER_H_
#define UNDISTORTER_H_

#include "opencv2/core/core.hpp"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>

#include "ImageFilter.h"

using namespace cv;


class Undistorter : public ImageFilter {

private:
	Mat cameraMatrix;
	Mat distCoeffs;

public:
	Undistorter();
	~Undistorter();

	void filter(Mat &distorted, Mat &undistorted) const;
	int8_t readParam(const string path);

};


#endif /* UNDISTORTER_H_ */
