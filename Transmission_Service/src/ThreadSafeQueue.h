//============================================================================
// Datei	: ThreadSafeQueue.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef TREADSAFEQUEUE_H_
#define TREADSAFEQUEUE_H_

#include "Mutex.h"
#include "Condition.h"
#include <queue>
#include <unistd.h>
#include <pthread.h>
#include <stdlib.h>

/**
 * Templateklasse zur Repraesentieren einer Thread sicheren Warteschlange
 * @author	Sebastian Hollermann
 * @date	05.11.2014
 */
template <class T>
class ThreadSafeQueue {
private:
	// Standardwarteschlange
	std::queue<T> data;
	// Mutex
	Mutex mtx;
	// Bedingungsvariable nicht voll
	Condition notFull;
	// Bedingungsvariable nicht leer
	Condition notEmpty;
	// Maximalegroesse der Schlange
	size_t max_size;
public:
	/**
	 * Konsturktor zum Initialisieren
	 * @param max_size	Maximale groesse der Warteschlange
	 */
	ThreadSafeQueue(size_t max_size = 10) : max_size(max_size) {}

	/**
	 * Dekonstruktor zum leeren der Warteschlange
	 */
	~ThreadSafeQueue() {

		mtx.lock();
		while (data.size()) data.pop();
		mtx.unlock();
	}

	/**
	 * Methode zum Zurueckgeben der Anzahl der Elemente innerhalb der Warteschlange
	 * @return	Anzahl der Elemente
	 */
	size_t size() {
		mtx.lock();
		size_t result = data.size();
		mtx.unlock();
		return result;
	}

	/**
	 * Methode zum Hinzufuegen von einen Element in die Warteschlange
	 * @param item	Element welches hinzugefuegt werden soll
	 */
	void push(T item) {
		mtx.lock();
		if (data.size() >= max_size) {
			notFull.wait(&mtx);
		}
		data.push(item);
		mtx.unlock();
		notEmpty.signal();
	}

	/**
	 * Methode zum Entnehmen des ersten Elementes aus der Warteschlange
	 * @return Erstes Element der Warteschlange
	 */
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
