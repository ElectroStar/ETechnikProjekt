/*
 * Thread.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

class Thread {
private:
	pthread_t thread;
	static void * dispatch(void *);
protected:
	virtual void run() = 0;
public:
	virtual ~Thread();
	void start();
	void join();
};


#endif /* THREAD_H_ */
