//============================================================================
// Datei	: IPositionService.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef IPOSITIONSERVICE_H_
#define IPOSITIONSERVICE_H_

#include "opencv2/core/core.hpp"

using namespace cv;

/** Interface zum erkennen von Objekten im Bild
 *  @author		Eric Buschermoehle
 *  @date		31.07.2014
 */
class IPositionService {

private:

public:

	virtual void getAllObjects(Mat &_input, Mat &_output) const = 0;

	/** Destruktor
	*/
	virtual ~IPositionService() {};
};

#endif /* IPOSITIONSERVICE_H_ */
