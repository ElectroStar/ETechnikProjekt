//============================================================================
// Datei	: IPositionService.h
// Autor	: Eric Buschermoehle
// Version	: 1.0
//============================================================================

#ifndef IPOSITIONSERVICE_H_
#define IPOSITIONSERVICE_H_

#include "opencv2/core/core.hpp"
#include "LocatableObject.h"
#include "LocatedObject.h"

using namespace cv;

/** Interface zum Erkennen von Objekten im Bild
 *  @author		Eric Buschermoehle
 *  @date		07.02.2015
 */
class IPositionService {

private:

public:

	/** Methode zur Lokalisierung Objekten eines bestimmbaren Typs.
	*  	@param[in] _src			Ausgangsbild
	*  	@param[in] _spec		Objektspezifikation
	*  	@return					Alle erkannten Objekte des Typs
	*/
	virtual vector<LocatedObject> getAllObjects(Mat _src, LocatableObject _spec) = 0;

	/**
	* Destruktor
	*/
	virtual ~IPositionService() {};
};

#endif /* IPOSITIONSERVICE_H_ */
