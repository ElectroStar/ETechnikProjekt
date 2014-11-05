/*
 * Networkadapter.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef NETWORKADAPTER_H_
#define NETWORKADAPTER_H_

#include <string>
#include <arpa/inet.h>

using namespace std;

class Networkadapter {
private:
	string _adapterName;
	struct sockaddr_in _broadcastAddress;
	struct sockaddr_in _netmask;
	struct sockaddr_in _address;

public:
	Networkadapter();
	virtual ~Networkadapter();
	bool determineAdapter(string adapterName);

	string getName() { return _adapterName; }
	struct sockaddr_in* getBroadcastAddress() { return &_broadcastAddress; }
	struct sockaddr_in* getNetmask() { return &_netmask; }
	struct sockaddr_in* getAddress() { return &_address; }
};

#endif /* NETWORKADAPTER_H_ */
