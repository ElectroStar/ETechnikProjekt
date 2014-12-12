/*
 * Transmitter.h
 *
 *  Created on: 12.12.2014
 *      Author: Sebastian Hollermann
 */

#ifndef TRANSMITTER_H_
#define TRANSMITTER_H_

/**
 * Klasse zum Uebertragen von Positionsdaten zum Uebertragungsdienst
 * @author	Sebastian Hollermann
 * @date	12.12.2014
 */
class Transmitter {
private:
	// Empfangsport des Uebertragungsdienst
	int _targetPort;
public:
	/**
	 * Konstruktor zum Initialisieren der TCP-Verbindung
	 * @param port	Empfangsport des Uebertragungsdienst
	 */
	TCPReceiver(int port) : _targetPort(port) {}
};

#endif /* TRANSMITTER_H_ */
