//============================================================================
// Datei	: Thread.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include "Thread.h"

/**
 * Dekonsturktor
 */
Thread::~Thread()
{}

/**
 * Startmethode des Threads
 * @param Klassenzeiger
 */
void * Thread::dispatch(void * ptr)
{
	if (!ptr) return 0;
	static_cast<Thread *>(ptr)->run();
	pthread_exit(ptr);
	return 0;
}

/**
 * Methode zum Starten des Threads (erzeugen)
 */
void Thread::start()
{
	pthread_create(&thread, 0, Thread::dispatch, this);
}

/**
 * Methode zum Warten auf den Thread
 */
void Thread::join()
{
	pthread_join(thread, 0);
}
