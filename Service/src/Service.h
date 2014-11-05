/*
 * Service.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef SERVICE_H_
#define SERVICE_H_
#define QUEUESIZE	10

#include "Networkadapter.h"

using namespace std;

class Service {
private:
	int _sendport;
	int _recvport;
	Networkadapter* _adapter;
	typedef struct {
	    int buf[QUEUESIZE];
	    long head, tail;
	    int full, empty;
	    pthread_mutex_t *mut;
	    pthread_cond_t *notFull, *notEmpty;
	} queue;
public:
	Service(int sendport, int recvport, Networkadapter* adapter) : _sendport(sendport), _recvport(recvport), _adapter(adapter) {};
	virtual ~Service();
	void start();
};

#endif /* SERVICE_H_ */
