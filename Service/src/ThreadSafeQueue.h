/*
 * TreadSafeQueue.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef TREADSAFEQUEUE_H_
#define TREADSAFEQUEUE_H_

#include "Mutex.h"
#include "Condition.h"
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

template <class T>
class ThreadSafeQueue {
private:
	std::queue<T> data;
	Mutex mtx;
	Condition notFull;
	Condition notEmpty;
	size_t max_size;
public:
	ThreadSafeQueue(size_t max_size = 10) : max_size(max_size) {}
	~ThreadSafeQueue() {

		mtx.lock();
		while (data.size()) data.pop();
		mtx.unlock();
	}

	size_t size() {
		mtx.lock();
		size_t result = data.size();
		mtx.unlock();
		return result;
	}

	void push(T item) {
		mtx.lock();
		if (data.size() >= max_size) {
			notFull.wait(&mtx);
		}
		data.push(item);
		mtx.unlock();
		notEmpty.signal();
	}

	T pop() {
		mtx.lock();
		if (data.size() <= 0) {
			notEmpty.wait(&mtx);
		}
		T item = data.front();
		data.pop();
		mtx.unlock();
		notFull.signal();
		return item;
	}
};

#endif /* TREADSAFEQUEUE_H_ */
