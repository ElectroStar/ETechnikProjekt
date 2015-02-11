//============================================================================
// Datei	: PositioningDataException.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef POSITIONINGDATAEXCEPTION_H_
#define POSITIONINGDATAEXCEPTION_H_

#include <exception>

using namespace std;

/**
 * Struktur zum Werfen einer Fehlermeldung fuer ein Falsches Format bei den Positionsdaten
 */
struct PositioningDataException : public exception
{
	/**
	 * Methode zum Zurueckgeben der Fehlermeldung
	 * @return	Fehlermeldung
	 */
	const char * what () const throw () {
		return "Flasches PositioningData-Format";
	}
};

#endif /* POSITIONINGDATAEXCEPTION_H_ */
