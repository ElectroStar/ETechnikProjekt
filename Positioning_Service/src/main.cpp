/*
 * main.cpp
 *
 *  Created on: Dec 1, 2014
 *      Author: user
 */

#include <iostream>
#include "Filters/Undistorter.h"
#include "Filters/TailorFieldView.h"

using namespace std;

int main() {

	cout << "Test" << endl;

	Mat src, target;
	src = imread("/home/user/zynq/zed-workspace/Entzerren/image/1.jpg");

	Undistorter test;
	test.readParam("/home/user/zynq/zed-workspace/Entzerren/out_camera_data.xml");

	TailorFieldView test1(Point(0,0), Point(100,100));

	Mat klein;

	test1.filter(src,klein);

	test.filter(src,target);
	imwrite("/home/user/zynq/zed-workspace/Entzerren/image/klein.jpg", klein);
	imwrite("/home/user/zynq/zed-workspace/Entzerren/image/target1.jpg", target);

	cout << "Test" << endl;
}
