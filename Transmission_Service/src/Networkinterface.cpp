/*
 * Networkinterface.cpp
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#include "Networkinterface.h"
#include <sys/types.h>
#include <ifaddrs.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

/**
 * Konstruktor zum Initialisieren der Datenstrukturen
 */
Networkinterface::Networkinterface() {
	// Variablen initialisieren
	_interfaceName = "";
	memset(&_broadcastAddress, 	0, sizeof(_broadcastAddress));
	memset(&_netmask, 			0, sizeof(_netmask));
	memset(&_address, 			0, sizeof(_address));
}

/**
 * Methode zum Ermitteln eines Netzwerkinterfaces
 * @param interfaceName	Interfacename dessen Daten ermittelt werden sollen
 * @return	true = Interface gefunden, false = Interface nicht gefunden
 */
bool Networkinterface::determineInterface(string adapterName) {
	// Merkvariable ob der Eintrag gefunden wurde
	bool found = false;

	// Verkettete Liste der Netzwerkadapter/Interfaces holen
	struct ifaddrs *ifaddr, *ifa;

	if(getifaddrs(&ifaddr) == -1) {
		printf("Konnte nicht auf die Interfaces zugreifen!\n");
		exit(EXIT_FAILURE);
	}

	// Verkette Liste druchgehen bis das richtige Interface gefunden ist
	for (ifa = ifaddr; ifa != NULL; ifa = ifa->ifa_next) {
		// Nur gueltige Adressen verarbeiten
		if (ifa->ifa_addr == NULL) {
			continue;
		}

		// Nur Family AF_INET (IPv4) verarbeiten
		if(ifa->ifa_addr->sa_family != AF_INET) {
			continue;
		}

		// Nur Eintraege verarbeiten welche mit den uebergebneden Namen uebereinstimmen
		string ifname(ifa->ifa_name);
		if(ifname == adapterName) {
			this->_interfaceName = ifname;

			// Struktur sockaddr in sockaddr_in casten und im Anschluss
			// den Speicherinhalt in die Struktur kopieren
			struct sockaddr_in* addrin = ((struct sockaddr_in *)(ifa->ifa_addr));
			memcpy(&_address, addrin, sizeof(*addrin));
			addrin = ((struct sockaddr_in *)(ifa->ifa_netmask));
			memcpy(&_netmask, addrin, sizeof(*addrin));
			addrin = ((struct sockaddr_in *)(ifa->ifa_ifu.ifu_broadaddr));
			memcpy(&_broadcastAddress, addrin, sizeof(*addrin));

			// Entsprechenden Adapter gefunden daher true zurueckgeben
			found = true;
			// Restliche verarbeitung abbrechen
			break;
		}
	}

	// Liste wieder freigeben
	freeifaddrs(ifaddr);

	return found;
}
