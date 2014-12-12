/*
 * Service.h
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#ifndef SERVICE_H_
#define SERVICE_H_
#define QUEUESIZE	10

#include "Networkinterface.h"
#include "PosData.h"

using namespace std;

/**
 * Klasse zur Repraesentierung des Uebertragungsdienst
 * @author	Sebastian Hollermann
 * @date	05.11.2014
 */
class Service {
private:
	// UDP-Senderport
	int _sendport;
	// TCP-Empfangsport
	int _recvport;
	// Netzwerkinterface
	Networkinterface* _interface;
public:
	/**
	 * Konsturktor zum Initialisieren des Uebertragungsdienst
	 * @param sendport	UDP-Port auf dem gesendet werden soll
	 * @param recvport	TCP-Port auf dem empfangen werden soll
	 * @param interface	Netzwerkinterface welches verwendet werden soll
	 */
	Service(int sendport, int recvport, Networkinterface* interface) : _sendport(sendport), _recvport(recvport), _interface(interface) {};

	/**
	 * Methode zum starten des Uebertragungsdienst
	 */
	void start();
};

#endif /* SERVICE_H_ */
