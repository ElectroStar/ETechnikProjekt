/*
 * Condition.cpp
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#include "Condition.h"

/**
 * Konstruktor zum initialisieren der Bedingungsvariable
 */
Condition::Condition() {
	pthread_cond_init(&_condition, NULL);
}

/**
 * Dekonstruktor zum loeschen der Bedingungsvariable
 */
Condition::~Condition() {
	pthread_cond_destroy(&_condition);
}

/**
 * Methode um das Signal der Bedingungsvariable zu senden
 */
void Condition::signal() {
	pthread_cond_signal(&_condition);
}

/**
 * Methode um auf diese Bedingungsvariable zu warten
 * @param mutex	Mutex, welche zum Warten benutzt werden soll
 */
void Condition::wait(Mutex* mutex) {
	pthread_cond_wait(&_condition, &(mutex->_mutex));
}
