//============================================================================
// Datei	: TransmittingException.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef TRANSMITTINGEXCEPTION_H_
#define TRANSMITTINGEXCEPTION_H_

#include <exception>

using namespace std;

/**
 * Struktur zum Werfen einer Fehlermeldung fuer ein Fehlerhaftes Uebermitteln der Positionsdaten
 */
struct TransmittingException : public exception
{
	/**
	 * Methode zum Zurueckgeben der Fehlermeldung
	 * @return	Fehlermeldung
	 */
	const char * what () const throw () {
		return "Es wurden nicht alle Daten uebertragen!";
	}
};


#endif /* TRANSMITTINGEXCEPTION_H_ */
