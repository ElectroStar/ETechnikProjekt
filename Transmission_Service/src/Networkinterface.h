//============================================================================
// Datei	: Networkinterface.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef NETWORKINTERFACE_H_
#define NETWORKINTERFACE_H_

#include <string>
#include <arpa/inet.h>

using namespace std;

/**
 * Klasser zur Abbildung eines Netzwerkinterfaces
 * @author	Sebastian Hollermann
 * @date	05.11.2014
 */
class Networkinterface {
private:
	// Interfacename
	string _interfaceName;
	// Broadcastadresse des Interfacenetzwerks
	struct sockaddr_in _broadcastAddress;
	// Netzmaske des Interfacenetzwerks
	struct sockaddr_in _netmask;
	// IP-Adresse des Interfacenetzwerks
	struct sockaddr_in _address;

public:
	/**
	 * Konstruktor zum Initialisieren der Datenstrukturen
	 */
	Networkinterface();

	/**
	 * Methode zum Ermitteln eines Netzwerkinterfaces
	 * @param interfaceName	Interfacename dessen Daten ermittelt werden sollen
	 * @return	true = Interface gefunden, false = Interface nicht gefunden
	 */
	bool determineInterface(string interfaceName);

	/**
	 * Methode zum Zurueckgeben des Interfacenamens
	 * @return	Interfacename
	 */
	string getName() { return _interfaceName; }

	/**
	 * Methode zum Zurueckgeben der Broadcastadresse des Interfaces
	 * @return	Zeiger auf die Broadcastadresse des Interfaces
	 */
	struct sockaddr_in* getBroadcastAddress() { return &_broadcastAddress; }

	/**
	 * Methode zum Zurueckgeben der Subnetzmaske des Interfaces
	 * @return	Zeiger auf die Subnetzmaske des Interfaces
	 */
	struct sockaddr_in* getNetmask() { return &_netmask; }

	/**
	 * Methode zum Zurueckgeben der IP-Adresse des Interfaces
	 * @return	Zeiger auf die IP-Adresse des Interfaces
	 */
	struct sockaddr_in* getAddress() { return &_address; }
};

#endif /* NETWORKINTERFACE_H_ */
