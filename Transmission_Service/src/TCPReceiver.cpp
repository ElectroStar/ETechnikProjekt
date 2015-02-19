//============================================================================
// Datei	: TCPReceiver.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include "TCPReceiver.h"
#include "TCPServer.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>
#include "PositioningDataException.h"

/**
 * Methode zum Abarbeiten der Aufgaben dieses Threads
 */
void TCPReceiver::run()
{
	// TCP-Port binden
	TCPServer* server = new TCPServer(50728);
	if(server->start() != 0) {
		cout << "Konnte TCP-Server nicht starten" << endl;
		exit(EXIT_FAILURE);
	}

	bool ende = false;

	// Solange bis ein ende eingetippt wurde
	while(!ende) {
		// Wurde ein Ende eingegeben waehrend des wartens auf Clients?
		if(!waitForAccepting(server)) {
			ende = true;
			continue;
		}
		// Clients akzeptieren
		TCPStream* stream = server->accept();
		// Solange bis ende oder die Verbindung abgebrochen wird
		while(!ende) {
			// Wurde ein Ende waehrend des wartens auf den Stream eingegeben?
			if(!waitForReceiving(stream)) {
				ende = true;
				continue;
			}

			size_t len;
			char line[512];
			// Waren ueberhaupt Daten im Socket?
			// Wenn nicht wurde der Socket geschlossen
			if((len = stream->receive(line, sizeof(line))) == 0) {
				break;
			} else {
				// Eintrag der Queue hinzufuegen
				string arg(line);
				try {
					PosData posData(arg);
					_queue->push(posData);
				} catch (PositioningDataException& e) {
					continue;
				}
				//cout << "Datensatz gefunden" << endl;
			}
		}

		// Stream wieder freigeben
		delete stream;
	}
}

/**
 * Methode zum Warten bis der Benutzer ein ENDE eingegeben hat oder ein Klient eine Verbindung aufbaut
 * @param server	Server welcher ueberwacht werden soll
 * @return	true = Verbindunganfrage liegt vor, false = Benutzer hat ein ENDE eingegeben
 */
bool TCPReceiver::waitForAccepting(TCPServer* server) {
	fd_set fdset;
	// Stdin in FD-Set hinzufügen
	FD_ZERO(&fdset);
	FD_SET(STDIN_FILENO, &fdset);
	FD_SET(*server, &fdset);

	// Solange warten bis Daten im TCP-Stream vorliegen oder
	// ein Ende in der Eingabe eingegeben wurde
	while(1) {
		// Warten bis im Stream oder in der Eingabe etwas vorliegt
		select((*server)+1, &fdset, NULL, NULL, NULL);

		// Ist STDIN aktiv?
		if(FD_ISSET(STDIN_FILENO, &fdset)) {
			if(checkForEnde())
				return false;
		}

		// Ist was aufm TCP-Socket?
		if(FD_ISSET((*server), &fdset)) {
			return true;
    	}
	}

	return true;
}

/**
 * Methode zum Ueberpruefen ob ein ENDE eingegeben worden ist
 * @return	true = ENDE wurde eingegeben, false = kein ENDE
 */
bool TCPReceiver::checkForEnde() {
	string line, out;
	getline(cin, line);
	transform(line.begin(), line.end(), std::back_inserter(out), (int (*)(int))std::toupper);
	// Wurde ein ENDE eingeben?
	if(out == "ENDE") {
		return true;
	}

	return false;
}

/**
 * Methode zum Warten bis der Benutzer ein ENDE eingegeben hat oder Datenpakete vorhanden sind
 * @param stream	Stream welcher ueberwacht werden soll
 * @return	true = Datenpakete liegen vor, false = Benutzer hat ein ENDE eingegeben
 */
bool TCPReceiver::waitForReceiving(TCPStream* stream) {
	fd_set fdset;
	// Stdin in FD-Set hinzufügen
	FD_ZERO(&fdset);
	FD_SET(STDIN_FILENO, &fdset);
	FD_SET(*stream, &fdset);

	// Solange warten bis Daten im TCP-Stream vorliegen oder
	// ein Ende in der Eingabe eingegeben wurde
	while(1) {
		// Warten bis im Stream oder in der Eingabe etwas vorliegt
		select((*stream)+1, &fdset, NULL, NULL, NULL);

		// Ist STDIN aktiv?
		if(FD_ISSET(STDIN_FILENO, &fdset)) {
			if(checkForEnde())
				return false;
		}

		// Ist was aufm TCP-Socket?
		if(FD_ISSET((*stream), &fdset)) {
			return true;
    	}
	}

	return true;
}
