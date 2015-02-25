//============================================================================
// Datei	: Transmitter.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include "Transmitter.h"
#include <netdb.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include "ConnectionException.h"
#include "TransmittingException.h"
#include "PosData.h"

/**
 * Konstruktor zum Initialisieren der TCP-Verbindung
 * @param destinationAddress	Zieladresse des Uebertragungsdienst
 * @param port	Empfangsport des Uebertragungsdienst
 */
Transmitter::Transmitter(string destinationAddress, int port) {
	_targetPort = port;

	struct sockaddr_in address;

	memset (&address, 0, sizeof(address));
	address.sin_family = AF_INET;
	address.sin_port = htons(port);
	if (resolveHostName(destinationAddress.c_str(), &(address.sin_addr)) != 0 ) {
		inet_pton(PF_INET, destinationAddress.c_str(), &(address.sin_addr));
	}
	_socket = socket(AF_INET, SOCK_STREAM, 0);
	if (::connect(_socket, (struct sockaddr*)&address, sizeof(address)) != 0) {
		throw ConnectionException();
	}
}

Transmitter::~Transmitter() {
	close(_socket);
}

/**
 * Methode zum Uebermitteln der ermittelten Position an den Uebertragungsdienst
 * @param pos	PositionsData
 */
void Transmitter::transmit(PosData pos) {
	// Datenpaket versenden an den Server
	string packet = pos;

	size_t laenge = packet.length();
	ssize_t sended = write(_socket, packet.c_str(), packet.length());
	if(sended != laenge)
		throw TransmittingException();
}

/**
 * Methode zum Ermitteln der Adresse eines Hostnames
 * @param host	Name des Hosts
 * @param addr	Adresse
 * @return 0 bei Misserfolg
 */
int Transmitter::resolveHostName(const char* hostname, struct in_addr* addr)
{
    struct addrinfo *res;

    int result = getaddrinfo (hostname, NULL, NULL, &res);
    if (result == 0) {
        memcpy(addr, &((struct sockaddr_in *) res->ai_addr)->sin_addr, sizeof(struct in_addr));
        freeaddrinfo(res);
    }
    return result;
}
