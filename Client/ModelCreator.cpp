//============================================================================
// Datei	: ModelCreator.cpp
// Autor	: Christian Jungblut
// Version	: 1.0
//============================================================================

#include "ModelCreator.h"


ModelCreator::ModelCreator(int _pxWidth) : pixelFieldWidth(_pxWidth), pixelFieldHeight(0), metricFieldWidth(0), metricFieldHeight(0)
{

}


Point ModelCreator::calcPosition(int _x, int _y, int _x2, int _y2){

	if (metricFieldWidth!=_x2 || metricFieldHeight!=_y2){

		metricFieldWidth = _x2;
		metricFieldHeight = _y2;

		float ratio = (float)metricFieldHeight / (float)metricFieldWidth;
		pixelFieldHeight = (int)(ratio * pixelFieldWidth);

		model = Mat(pixelFieldHeight, pixelFieldWidth, CV_8UC3, Scalar(255, 255, 255));
	}


	float ratioX = (float)pixelFieldWidth / (float)metricFieldWidth;
	float ratioY = (float)pixelFieldHeight / (float)metricFieldHeight;

	Point result;
	_x = (int)(ratioX*_x);
	_y = (int)(ratioY*_y);

	if (_x > 0 && _y > 0)
	{
		result.x = _x;
		result.y = model.rows - _y;

	}
	else if (_x > 0 && _y < 0){
	
		result.x = _x;
		result.y = -_y;
	}
	else if (_x < 0 && _y > 0){
	
		result.x = model.cols + _x;
		result.y = model.rows - _y;
	}
	else
	{
		result.x = model.cols + _x;
		result.y = -_y;
	}

	return result;
}


void ModelCreator::drawPosition(Point _p)
{

	circle(model, _p, (int)model.rows / 50, Scalar(0, 0, 255), -1);
}

Mat ModelCreator::getModel()
{
	return model;
}


int ModelCreator::getMetricFieldWidth()
{
	return metricFieldWidth;
}

void ModelCreator::setMetricFieldWidth(int _x)
{
	metricFieldWidth = _x;
}

int ModelCreator::getMetricFieldHeight()
{
	return metricFieldHeight;
}

void ModelCreator::setMetricFieldHeight(int _y)
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


