//============================================================================
// Datei	: Mutex.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include "Mutex.h"

/**
 * Konstruktor zum initialisieren des pthread mutex
 */
Mutex::Mutex()
{
	pthread_mutex_init(&_mutex, 0);
}

/**
 * Dekonstruktor zum loeschen des mutex
 */
Mutex::~Mutex()
{
	pthread_mutex_destroy(&_mutex);
}

/**
 * Methode zum blockieren des Mutex
 */
void Mutex::lock()
{
	pthread_mutex_lock(&_mutex);
}

/**
 * Methode zum aufheben einer Blockierung des Mutex
 */
void Mutex::unlock()
{
	pthread_mutex_unlock(&_mutex);
}

/**
 * Methode zum versuchen einen Mutex zu blockieren
 * @return	true bei Erfolg, false bei Misserfolg
 */
bool Mutex::trylock()
{
	return (pthread_mutex_trylock(&_mutex) == 0);
}
