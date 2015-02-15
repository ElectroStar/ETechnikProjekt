
#include "drawimage.h"

#include <iostream>
using namespace std;

DrawImage::DrawImage(uint16_t _imageHeight, uint16_t _imageWidth) : imageHeight(_imageHeight), imageWidth(_imageWidth) {

    image = Mat::zeros(imageHeight, imageWidth, CV_64F);
}

DrawImage::~DrawImage() {
}

void DrawImage::linkPoints() {

    uint16_t size = points.size();
    if(size >= 0 && size <= 2) return;
    line(image, points[size-2], points[size-1], Scalar( 255, 255, 255 ),1,1);
}

void DrawImage::deleteImage() {
    image = Mat::zeros(imageHeight, imageWidth, CV_64F);
}

Mat DrawImage::getImage() const {
    return image;
}

void DrawImage::pushBackPoints(Point p) {
    points.push_back(p);
}

Point DrawImage::getLastPoint() const {
    return points.back();
}

vector<Point> DrawImage::getPoints() const {
    return points;
}
void DrawImage::setPoints(vector<Point> &_points) {
    points = _points;
}
