//============================================================================
// Datei	: ConnectionException.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef CONNECTIONEXCEPTION_H_
#define CONNECTIONEXCEPTION_H_

#include <exception>

using namespace std;

/**
 * Struktur zum Werfen einer Fehlermeldung wenn keine Verbindung aufgebaut werden konnte
 */
struct ConnectionException : public exception
{
	/**
	 * Methode zum Zurueckgeben der Fehlermeldung
	 * @return	Fehlermeldung
	 */
	const char * what () const throw () {
		return "Konnte keine Verbindung zum Server aufbauen!";
	}
};

#endif /* CONNECTIONEXCEPTION_H_ */
