/*
 * Mutex.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef MUTEX_H_
#define MUTEX_H_

#include <pthread.h>

class Mutex {
friend class Condition;
private:
	pthread_mutex_t _mutex;
public:
	Mutex();
	~Mutex();
	void lock();
	void unlock();
	bool trylock();
};

#endif /* MUTEX_H_ */
