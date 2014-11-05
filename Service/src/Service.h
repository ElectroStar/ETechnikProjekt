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
#include "PosData.h"

using namespace std;

class Service {
private:
	int _sendport;
	int _recvport;
	Networkadapter* _adapter;
public:
	Service(int sendport, int recvport, Networkadapter* adapter) : _sendport(sendport), _recvport(recvport), _adapter(adapter) {};
	virtual ~Service();
	void start();
};

#endif /* SERVICE_H_ */
