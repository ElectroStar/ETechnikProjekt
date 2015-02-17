//============================================================================
// Name        : TestUdpProducer.cpp
// Author      : Sebastian Hollermann
// Version     :
// Copyright   : HS Osnabrück
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <iostream>
#include <iostream>
#include <string.h>
#include <arpa/inet.h>
#include <stdlib.h>
#include <sys/types.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <stdio.h>
using namespace std;

int main() {
	cout << "!!!Hello World!!!" << endl; // prints !!!Hello World!!!

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

	// Ziel-Port setzen
	memset(&network, 0, sizeof(network));
	network.sin_port = htons(50729);
	network.sin_addr.s_addr = inet_addr("192.168.178.255");
	network.sin_family = AF_INET;
	char echo_string[50];
	int echo_len;
	// TODO: Statt eine Endlosschleife das Beenden aus dem Main Thread ermoeglichen
	while(1) {
		// Warten bis Positionsdaten vorliegen, welche weitergeleitet werden sollen
		//PosData data = _queue->pop();

		// PosData in String umwandenln und dann in Char-Array
		//string posDataString = "Blablabla\r\n";
		echo_len = sprintf(echo_string, "$%d.%d,%d.%d,%d.%d,%d.%d,MR,%d.%d,%d.%d,%d,%d\r\n",
						rand()%1000, rand()%1000, rand()%1000, rand()%1000, rand()%1000,
						rand()%1000, rand()%1000, rand()%1000, rand()%1000, rand()%1000,
						rand()%1000, rand()%1000, rand()%8000, rand()%100000000);
		//char *buffer=new char[posDataString.size()+1];
		//buffer[posDataString.size()]=0;
		//memcpy(buffer,posDataString.c_str(),posDataString.size());
			// Daten ins Netzwerk senden
		//if (sendto(sock, buffer, strlen(buffer), 0, (struct sockaddr *)&network, sizeof(network)) < 0) {
		if (sendto(sock, echo_string, echo_len, 0, (struct sockaddr *)&network, sizeof(network)) < 0) {
			cout << "Senden ins Netzwerk fehlgeschlagen" << endl;
			exit(EXIT_FAILURE);
		}

		struct timeval tv;
		fd_set fds;
		// Timeout auf 3 Sekunde setzen
		tv.tv_sec = 3;
		tv.tv_usec = 0;
		// Stdin in FD-Set hinzufügen
		FD_SET(STDIN_FILENO, &fds);
		select(STDIN_FILENO+1, &fds, NULL, NULL, &tv);
	}

	// Socket wieder schließen
	close(sock);

	return 0;
}
