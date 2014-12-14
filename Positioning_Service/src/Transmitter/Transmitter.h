/*
 * Transmitter.h
 *
 *  Created on: 12.12.2014
 *      Author: Sebastian Hollermann
 */

#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

#include <string>
#include <cv.h>

using namespace std;
using namespace cv;

/**
 * Klasse zum Uebertragen von Positionsdaten zum Uebertragungsdienst
 * @author	Sebastian Hollermann
 * @date	12.12.2014
 */
class Transmitter {
private:
	// Empfangsport des Uebertragungsdienst
	int _targetPort;

	// TCP-Socket
	int _socket;

	/**
	 * Methode zum Ermitteln der Adresse eines Hostnames
	 * @param host	Name des Hosts
	 * @param addr	Adresse
	 * @return 0 bei Misserfolg
	 */
	int resolveHostName(const char* host, struct in_addr* addr);
public:

	/**
	 * Konstruktor zum Initialisieren der TCP-Verbindung
	 * @param destinationAddress	Zieladresse des Uebertragungsdienst
	 * @param port	Empfangsport des Uebertragungsdienst
	 */
	Transmitter(string destinationAddress, int port);

	/**
	 * Destruktor zum Schließen der Verbindung
	 */
	~Transmitter();

	/**
	 * Methode zum Uebermitteln der ermittelten Position an den Uebertragungsdienst
	 * @param	Position
	 */
	void transmit(Point2d pos);
};

#endif /* TRANSMITTER_H_ */
