//======================================================================================
// Datei	: main.cpp
// Autor	: Eric Buschermoehle, Sebastian Hollermann, Joel Bartelheimer, 
//			  Benjamin Augenstein, Tung Pham, Michael Over, Christian Jungblut
// Projekt	: Kamerabasiertes Indoor-Navigationssystem (Elektrotechnik Projekt WS 14/15)
// Version	: 1.0
//======================================================================================

#include "opencv2/highgui/highgui.hpp"
#include "opencv2/imgproc/imgproc.hpp"
#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "PositionService\LocatableObject.h"
#include "Filters/Undistorter.h"
#include "FieldLocator\FieldLocator.h"
#include "Filters\CropFieldView.h"
#include "PositionService\ObjectLocator.h"
using namespace cv;
using namespace std;



int main(int argc, char** argv)
{
	
	
	VideoCapture cap(1); // open the default camera
	if (!cap.isOpened())  // check if we succeeded
		return -1;
	cap.set(CV_CAP_PROP_FPS, 20);

	Undistorter undis;
	FieldLocator fl(LocatableObject(TRIANGLE, 0, 127, 10), LocatableObject(TRIANGLE, 128, 255, 10));
	
  vector<Point> boundaries;

	Mat src;
	Mat undistorted;
	undis.readParam("out_camera_data.xml");


	while (true){

		cap >> src;

		undis.filter(src, undistorted);


		boundaries = fl.locateField(undistorted);

		
	
		for (int i = 0; i < boundaries.size(); i++){
			circle(undistorted, boundaries[i], 5, Scalar(0, 0, 255));
			circle(undistorted, boundaries[i], 3, Scalar(0, 255, 0),-1);
		}

		if (boundaries.size() == 2){
			break;
		}

		imshow("ergebnis", undistorted);
		waitKey(30);
	}

	CropFieldView tfv(boundaries[0], boundaries[1]);
	Mat cropped;

	ObjectLocator ol;
	vector<LocatedObject> result;

	while (true){

		cap >> src;
		undis.filter(src, undistorted);

		tfv.filter(undistorted, cropped);

		result = ol.getAllObjects(cropped, LocatableObject(RECTANGLE, 128, 255, 10));

		for (int i = 0; i < result.size(); i++){
			circle(cropped, result[i].position, 3, Scalar(255, 0, 0), -1);
			circle(cropped, result[i].position, 5, Scalar(0, 0, 255));
		}

		imshow("cropped", cropped);

		if (waitKey(30)>0)break;

	}


	return(0);
}
