//============================================================================
// Datei	: Condition.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef CONDITION_H_
#define CONDITION_H_

#include "Mutex.h"

/**
 * Klasse zur einfachen Handhabung von Bedingungsvariablen
 * @author	Sebastian Hollermann
 * @date	05.11.2014
 */
class Condition {
private:
	// Interne pthread Bedingungsvariablen Struktur
	pthread_cond_t _condition;
public:
	/**
	 * Konstruktor zum initialisieren der Bedingungsvariable
	 */
	Condition();
	/**
	 * Dekonstruktor zum loeschen der Bedingungsvariable
	 */
	~Condition();
	/**
	 * Methode um auf diese Bedingungsvariable zu warten
	 * @param mutex	Mutex, welche zum Warten benutzt werden soll
	 */
	void wait(Mutex *mutex);
	/**
	 * Methode um das Signal der Bedingungsvariable zu senden
	 */
	void signal();
};

#endif /* CONDITION_H_ */
