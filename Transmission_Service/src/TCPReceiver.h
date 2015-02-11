//============================================================================
// Datei	: TCPReceiver.h
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#ifndef TCPRECEIVER_H_
#define TCPRECEIVER_H_

#include "ThreadSafeQueue.h"
#include "PosData.h"
#include "Thread.h"
#include "TCPStream.h"
#include "TCPServer.h"

/**
 * Klasse zum Empfangen von Positionsdatenpaketen
 * @author	Sebastian Hollermann
 * @date	05.11.2014
 */
class TCPReceiver : public Thread {
private:
	// Schlange in der die Daten gespeichert werden
	ThreadSafeQueue<PosData> * _queue;
	// Name des Threads
	string _id;
	// Port zum Empfangen der Daten
	int _port;

	/**
	 * Methode zum Warten bis der Benutzer ein ENDE eingegeben hat oder Datenpakete vorhanden sind
	 * @param stream	Stream welcher ueberwacht werden soll
	 * @return	true = Datenpakete liegen vor, false = Benutzer hat ein ENDE eingegeben
	 */
	bool waitForReceiving(TCPStream* stream);

	/**
	 * Methode zum Warten bis der Benutzer ein ENDE eingegeben hat oder ein Klient eine Verbindung aufbaut
	 * @param server	Server welcher ueberwacht werden soll
	 * @return	true = Verbindunganfrage liegt vor, false = Benutzer hat ein ENDE eingegeben
	 */
	bool waitForAccepting(TCPServer* server);

	/**
	 * Methode zum Ueberpruefen ob ein ENDE eingegeben worden ist
	 * @return	true = ENDE wurde eingegeben, false = kein ENDE
	 */
	bool checkForEnde();
protected:
	/**
	 * Methode zum Abarbeiten der Aufgaben dieses Threads
	 */
	virtual void run();
public:
	/**
	 * Konstruktor zum Initialisieren des Threads
	 * @param queue	Schlange in der die Datenpakete abgelegt werden sollen
	 * @param id	Name des Threads
	 * @param port	Port welcher zum Empfangen benutzt werden soll
	 */
	TCPReceiver(ThreadSafeQueue<PosData> * queue, string id, int port) : _queue(queue), _id(id), _port(port) {}
};

#endif /* TCPRECEIVER_H_ */
