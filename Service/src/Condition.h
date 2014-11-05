/*
 * Condition.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef CONDITION_H_
#define CONDITION_H_

#include "Mutex.h"

class Condition {
private:
	pthread_cond_t _condition;
public:
	Condition();
	~Condition();
	void wait(Mutex mutex);
	void signal();
};

#endif /* CONDITION_H_ */
