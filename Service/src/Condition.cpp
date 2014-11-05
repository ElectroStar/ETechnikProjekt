/*
 * Condition.cpp
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#include "Condition.h"

Condition::Condition() {
	pthread_cond_init(&_condition, NULL);
}

Condition::~Condition() {
	pthread_cond_destroy(&_condition);
}

void Condition::signal() {
	pthread_cond_signal(&_condition);
}

void Condition::wait(Mutex mutex) {
	pthread_cond_wait(&_condition, &mutex._mutex);
}
