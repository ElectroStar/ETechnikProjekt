/*
 * DrawRoute.h
 *
 *  Created on: Feb 4, 2015
 *      Author: user
 */

#ifndef DRAWIMAGE_H_
#define DRAWIMAGE_H_

#include "opencv2/core/core.hpp"
#include <opencv2/highgui/highgui.hpp>
#include <vector>

using namespace cv;

class DrawImage {

private:

    Mat image;
    uint16_t imageHeight;
    uint16_t imageWidth;
    vector<Point> points;

public:

    DrawImage(uint16_t _imageHeight, uint16_t _imageWidth);
    ~DrawImage();

    void linkPoints();
    void deleteImage();

    Mat getImage() const;
    Point getLastPoint() const;

    bool getRepaintLine() const;
    void setRepaintLine(bool _value);

    vector<Point> getPoints() const;
    void setPoints(vector<Point> &_points);

    void pushBackPoints(Point _p);
};

#endif /* DRAWIMAGE_H_ */
