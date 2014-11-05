/*
 * TCPReceiver.cpp
 *
 *  Created on: 05.11.2014
 *      Author: Sebastian Hollermann
 */

#include "TCPReceiver.h"
#include "TCPServer.h"
#include <iostream>
#include <string>
#include <stdlib.h>
#include <algorithm>

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
			char line[256];
			// Waren ueberhaupt Daten im Socket?
			// Wenn nicht wurde der Socket geschlossen
			if((len = stream->receive(line, sizeof(line))) == 0) {
				break;
			} else {
				// Eintrag der Queue hinzufuegen
				string arg(line);
				PosData posData(arg);
				_queue->push(posData);
			}
		}

		// Stream wieder freigeben
		delete stream;
	}
}

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
