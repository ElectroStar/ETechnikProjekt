/*
 * Service.cpp
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#include "Service.h"
#include <stdio.h>
#include "ThreadSafeQueue.h"
#include "PosData.h"
#include "TCPReceiver.h"
#include "UDPSender.h"

/**
 * Methode zum starten des Uebertragungsdienst
 */
void Service::start() {
	printf("Um den Dienst wieder zu beenden tippen Sie 'ende' ein\n");

	// Queue erstellen
	ThreadSafeQueue<PosData> queue;

	// TCP-Receiver starten
	TCPReceiver receiver(&queue, "Receiver", _recvport);
	receiver.start();

	// UDP-Sender starten
	UDPSender sender(&queue, "Sender", _sendport, _interface);
	sender.start();

	// Auf TCP-Receiver warten
	receiver.join();

	printf("Dienst wurde beendet\n");
}
