//============================================================================
// Datei	: UDPSender.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include "UDPSender.h"
#include <stdio.h>
#include <stdlib.h>
#include "PosData.h"
#include <iostream>
#include <string.h>

/**
 * Methode zum Abarbeiten der Aufgaben dieses Threads
 */
void UDPSender::run() {
	// Socket erstellen
	int sock;
	if((sock = socket(AF_INET, SOCK_DGRAM, 0)) < 0) {
		cout << "Konnte UDP-Socket nicht erstellen" << endl;
		exit(EXIT_FAILURE);
	}

	// Socket fuer Broadcast erlauben
	int yes = 1;
	if(setsockopt(sock, SOL_SOCKET, SO_BROADCAST, &yes, sizeof(int)) < 0) {
		cout << "Konnte UDP-Socket nicht fuer Broadcast einstellen" << endl;
		exit(EXIT_FAILURE);
	}

	// Socket auf TTL = 1 setzen
	int ttl = 1;
	if(setsockopt(sock, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) < 0) {
		cout << "Konnte TTL nicht setzen" << endl;
		exit(EXIT_FAILURE);
	}

	// Broadcast-Netzwerkadresse holen
	struct sockaddr_in network;
	memcpy(&network, _interface->getBroadcastAddress(), sizeof(*(_interface->getBroadcastAddress())));
	// Ziel-Port setzen
	network.sin_port = htons(_port);

	// TODO: Statt eine Endlosschleife das Beenden aus dem Main Thread ermoeglichen
	while(1) {
		// Warten bis Positionsdaten vorliegen, welche weitergeleitet werden sollen
		PosData data = _queue->pop();

		// PosData in String umwandenln und dann in Char-Array
		string posDataString = data;
		char *buffer=new char[posDataString.size()+1];
		buffer[posDataString.size()]=0;
		memcpy(buffer,posDataString.c_str(),posDataString.size());

		// Daten ins Netzwerk senden
		if (sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&network, sizeof(network)) < 0) {
			cout << "Senden ins Netzwerk fehlgeschlagen" << endl;
			exit(EXIT_FAILURE);
		}
	}

	// Socket wieder schließen
	close(sock);
}
