/*
 * TCPReceiver.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef TCPRECEIVER_H_
#define TCPRECEIVER_H_

#include "ThreadSafeQueue.h"
#include "PosData.h"
#include "Thread.h"
#include "TCPStream.h"
#include "TCPServer.h"

class TCPReceiver : public Thread {
private:
		ThreadSafeQueue<PosData> * _queue;
		string _id;
		int _port;
		bool waitForReceiving(TCPStream* stream);
		bool waitForAccepting(TCPServer* server);
		bool checkForEnde();
	protected:
		virtual void run();
	public:
		TCPReceiver(ThreadSafeQueue<PosData> * queue, string id, int port) : _queue(queue), _id(id), _port(port) {}
};

#endif /* TCPRECEIVER_H_ */
