//============================================================================
// Datei	: ImageFilter.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef UNDISTORTER_H_
#define UNDISTORTER_H_

#include "opencv2/core/core.hpp"
#include <opencv2/calib3d/calib3d.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include <string>

#include "ImageFilter.h"

using namespace cv;

/** Klasse um Bilder zu entzerren.
 *  @author		Eric Buschermoehle
 *  @date		  31.07.2014
 */
class Undistorter : public ImageFilter {

private:
	Mat cameraMatrix;
	Mat distCoeffs;

public:

  /** Konstruktor
	*  	@param[in] _lowerLeft 	Position unten links
	*  	@param[in] _upperRight 	Position unten rechts
	*/
	Undistorter();
  
  /** Destruktor
	*/
	~Undistorter();

  /** Methode zum entzerren eines Bildes
	*  	@param[in] _input 	  Eingangsbild
	*  	@param[in] _output  	Ausgangsbild
	*/
	void filter(Mat &_distorted, Mat &_undistorted) const;
  
  /** Methode zum einlesen der Verzerrungparameter
	*  	@param[in] _path  	  Pfad
	*/
	int8_t readParam(const string _path);

};


#endif /* UNDISTORTER_H_ */
