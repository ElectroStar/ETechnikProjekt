//============================================================================
// Datei	: ImageFilter.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef IMAGEFILTER_H_
#define IMAGEFILTER_H_

#include "opencv2/core/core.hpp"

using namespace cv;

/** Interface fuer Filterklassen
 *  @author		Eric Buschermoehle
 *  @date		31.07.2014
 */
class ImageFilter {

public:

   /** Virtuelle Filtermethode
	*  	@param[in] _input 	Eingangsbild
	*  	@param[in] _output 	Ausgangsbild
	*/
	virtual void filter(Mat &_input, Mat &_output) const = 0;

   /**
	* Destruktor
	*/
	virtual ~ImageFilter() {};
};

#endif /* IMAGEFILTER_H_ */
