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
#include "Networkinterface.h"

/**
 * Klasse zur Weiterleitung der Positionsdaten
 * @author	Sebastian Hollermann
 * @date	06.11.2014
 */
class UDPSender : public Thread {
private:
	// Warteschlange
	ThreadSafeQueue<PosData> * _queue;
	// Name des Threads
	string _id;
	// Sendeport
	int _port;
	// Netzwerkinterface
	Networkinterface* _interface;
protected:
	/**
	 * Methode zum Abarbeiten der Aufgaben dieses Threads
	 */
	virtual void run();
public:
	/**
	 * Konstruktor zum Initialisieren
	 * @param queue		Warteschlange in die Positionsdaten sind
	 * @param id		Name des Threads
	 * @param port		Ziel-UDP-Port der Datenpakete
	 * @param interface	Netzwerkinterface welches zum Senden benutz werden soll
	 */
	UDPSender(ThreadSafeQueue<PosData> * queue, string id, int port, Networkinterface* interface) : _queue(queue), _id(id), _port(port), _interface(interface) {}
};

#endif /* UDPSENDER_H_ */
