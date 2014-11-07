/*
 * Thread.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef THREAD_H_
#define THREAD_H_

#include <pthread.h>

/**
 * Klasse zur einfachen Handhabung eines Threads
 * @author	Sebastian Hollermann
 * @date	05.11.2014
 */
class Thread {
private:
	// pthread Struktur
	pthread_t thread;
	/**
	 * Startmethode des Threads
	 * @param Klassenzeiger
	 */
	static void * dispatch(void *);
protected:
	/**
	 * Methode zum Abarbeiten der Aufgaben
	 */
	virtual void run() = 0;
public:
	/**
	 * Dekonsturktor
	 */
	virtual ~Thread();

	/**
	 * Methode zum Starten des Threads (erzeugen)
	 */
	void start();

	/**
	 * Methode zum Warten auf den Thread
	 */
	void join();
};


#endif /* THREAD_H_ */
