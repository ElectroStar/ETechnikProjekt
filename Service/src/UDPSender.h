/*
 * UDPSender.h
 *
 *  Created on: 06.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef UDPSENDER_H_
#define UDPSENDER_H_

#include "Thread.h"
#include "ThreadSafeQueue.h"
#include "PosData.h"
#include "Networkadapter.h"

class UDPSender : public Thread {
private:
		ThreadSafeQueue<PosData> * _queue;
		string _id;
		int _port;
		Networkadapter* _adapter;
	protected:
		virtual void run();
	public:
		UDPSender(ThreadSafeQueue<PosData> * queue, string id, int port, Networkadapter* adapter) : _queue(queue), _id(id), _port(port), _adapter(adapter) {}
};

#endif /* UDPSENDER_H_ */
