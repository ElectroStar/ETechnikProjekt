/*
 * Mutex.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

/**
 * Klasse zur einfachen Handhabung von Mutex
 * @author	Sebastian Hollermann
 * @date	05.11.2014
 */
class Mutex {
friend class Condition;
private:
	// Interne pthread mutex Struktur
	pthread_mutex_t _mutex;
public:
	/**
	 * Konstruktor zum initialisieren des pthread mutex
	 */
	Mutex();

	/**
	 * Dekonstruktor zum loeschen des mutex
	 */
	~Mutex();

	/**
	 * Methode zum blockieren des Mutex
	 */
	void lock();

	/**
	 * Methode zum aufheben einer Blockierung des Mutex
	 */
	void unlock();

	/**
	 * Methode zum versuchen einen Mutex zu blockieren
	 * @return	true bei Erfolg, false bei Misserfolg
	 */
	bool trylock();
};

#endif /* MUTEX_H_ */
