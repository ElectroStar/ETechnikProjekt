//============================================================================
// Datei	: ObjectLocator.cpp
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#include "ObjectLocator.h"

ObjectLocator::ObjectLocator(){

}

ObjectLocator::~ObjectLocator(){

}

vector<LocatedObject> ObjectLocator::getAllObjects(Mat src, LocatableObject spec) {

	//Prepare result vector
	vector<LocatedObject> objects;

	//Convert source image into gray
	Mat src_gray;
	cvtColor(src, src_gray, CV_BGR2GRAY);

	//Filter out the noise
	Mat src_gray_blurred;
	GaussianBlur(src_gray, src_gray_blurred, Size(9, 9), 3, 3);

	//Apply the Hough Transform to find the circles
	HoughCircles(src_gray_blurred, circles, CV_HOUGH_GRADIENT, 1, src_gray.rows / 20, 200, 50, 0, 0);

	//Examine the detected circles
	if (circles.size() > 0){															//////////////////////////////////TODO: Float in INT!!!

		/// Go through all detected circles
		for (unsigned int i = 0; i < circles.size(); i++)
		{

			//Crop image, special treatment in the border area
			int referencePx = circles[i][0] - circles[i][2];
			int referencePy = circles[i][1] - circles[i][2];

			int width = 2 * circles[i][2];
			int height = 2 * circles[i][2];

			if (circles[i][0] < circles[i][2]){

				width = 2 * circles[i][2] + referencePx;
				referencePx = 0;
			}

			if (circles[i][1] < circles[i][2]){

				height = 2 * circles[i][2] + referencePy;
				referencePy = 0;
			}

			if ((src.cols - circles[i][0]) < circles[i][2]){

				width = src.cols - referencePx;
			}

			if ((src.rows - circles[i][1]) < circles[i][2]){

				height = src.rows - referencePy;
			}

			Rect area(referencePx, referencePy, width, height);
			Mat cropped = src_gray(area);

			// Harris Corner Detection
			Mat corners, corners_norm, corners_norm_scaled;
			cornerHarris(cropped, corners, blockSize, apertureSize, k, BORDER_DEFAULT);

			// Normalizing
			normalize(corners, corners_norm, 0, 255, NORM_MINMAX, CV_32FC1, Mat());
			convertScaleAbs(corners_norm, corners_norm_scaled);

			// Detect corners in resulting image
			for (int j = 0; j < corners_norm.rows; j++)
			{
				for (int k = 0; k < corners_norm.cols; k++)
				{
					if ((int)corners_norm.at<float>(j, k) > thresh)
					{
						bool foundNew = true;

						for (unsigned int l = 0; l < cornerP.size(); l++){

							if (abs(cornerP[l].x - k) <= 3 && abs(cornerP[l].y - j) <= 3){

								foundNew = false;
								cornerP[l].x = (cornerP[l].x + k) / 2;
								cornerP[l].y = (cornerP[l].y + j) / 2;
								break;
							}
						}

						if (foundNew){

							cornerP.push_back(Point(k, j));
						}
					}
				}
			}

			//Check inner figure
			if (cornerP.size() == spec.form){

				//Calculate real positions and center
				Point center(0, 0);
				for (unsigned int m = 0; m < cornerP.size(); m++){

					cornerP[m].x += referencePx;
					center.x += cornerP[m].x;
					cornerP[m].y += referencePy;
					center.y += cornerP[m].y;
				}

				center.x = center.x / cornerP.size();
				center.y = center.y / cornerP.size();


				//Color of the central point
				if (src_gray_blurred.at<uchar>(Point(center.x, center.y)) <= spec.colorMax &&
					src_gray_blurred.at<uchar>(Point(center.x, center.y)) >= spec.colorMin){

					//Calculate the distance (Euklid)
					//Works for triangles and squares
					int distance = (int)sqrt(pow(cornerP[0].x - cornerP[1].x, 2) + pow(cornerP[0].y - cornerP[1].y, 2));


					//Store the found object
					objects.push_back(LocatedObject(Point(center.x, center.y), distance, spec));
				}

			}

			cornerP.clear();

		}

		circles.clear();
	}


	return objects;
}