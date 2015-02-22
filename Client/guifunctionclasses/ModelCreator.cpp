//============================================================================
// Datei	: ModelCreator.cpp
// Autor	: Christian Jungblut
// Version	: 1.0
//============================================================================

#include "ModelCreator.h"


ModelCreator::ModelCreator(int _pxWidth) :  oldPosition(0,0), metricFieldWidth(0), metricFieldHeight(0) ,pixelFieldWidth(_pxWidth), pixelFieldHeight(0) {

}


Point ModelCreator::calcPosition(double _x, double _y, double _x2, double _y2){

	if (metricFieldWidth!=_x2 || metricFieldHeight!=_y2){

		metricFieldWidth = _x2;
		metricFieldHeight = _y2;

        double ratio = metricFieldHeight / metricFieldWidth;
		pixelFieldHeight = (int)(ratio * pixelFieldWidth);

		model = Mat(pixelFieldHeight, pixelFieldWidth, CV_8UC3, Scalar(255, 255, 255));
	}

    return calcNewPositionWithoutUpdate(_x,_y);
}

Point ModelCreator::calcNewPositionWithoutUpdate(double _x, double _y) {

    double ratioX = (double)pixelFieldWidth / metricFieldWidth;
    double ratioY = (double)pixelFieldHeight / metricFieldHeight;

    Point result;
    int xPx = (int)(ratioX*_x);
    int yPx = (int)(ratioY*_y);

    if (xPx > 0 && yPx > 0)
    {
        result.x = xPx;
        result.y = model.rows - yPx;

    }
    else if (xPx > 0 && yPx < 0){

        result.x = xPx;
        result.y = -yPx;
    }
    else if (xPx < 0 && yPx > 0){

        result.x = model.cols + xPx;
        result.y = model.rows - yPx;
    }
    else
    {
        result.x = model.cols + xPx;
        result.y = -yPx;
    }

    return result;
}


void ModelCreator::drawPosition(Point _p)
{

    if(oldPosition.x != 0 && oldPosition.y !=0){

        circle(model, oldPosition, (int)model.rows / 50, Scalar(255, 0, 0), -1);
    }

        circle(model, _p, (int)model.rows / 50, Scalar(255, 0, 0), -1);
        circle(model, _p, (int)model.rows / 80, Scalar(0, 0, 0), -1);

        oldPosition = _p;
}

void ModelCreator::drawLine(Point _p1, Point _p2) {

    line(model, _p1, _p2, Scalar( 255, 255, 255 ),1,1);
}

void ModelCreator::redraw(){

    model.setTo(Scalar(255,255,255));
}

Mat& ModelCreator::getModel()
{
	return model;
}


double ModelCreator::getMetricFieldWidth()
{
	return metricFieldWidth;
}

void ModelCreator::setMetricFieldWidth(double _x)
{
	metricFieldWidth = _x;
}

double ModelCreator::getMetricFieldHeight()
{
	return metricFieldHeight;
}

void ModelCreator::setMetricFieldHeight(double _y)
{
	metricFieldHeight = _y;
}

int ModelCreator::getPixelFieldWidth()
{
	return pixelFieldWidth;
}

void ModelCreator::setPixelFieldWidth(int _x)
{
	pixelFieldWidth = _x;
}

int ModelCreator::getPixelFieldHeight()
{
	return pixelFieldHeight;
}

void ModelCreator::setPixelFieldHeight(int _y)
{
	pixelFieldHeight = _y;
}

ModelCreator::~ModelCreator()
{
}


