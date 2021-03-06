//============================================================================
// Datei	: main.cpp
// Autor	: Sebastian Hollermann
// Version	: 1.0
//============================================================================

#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include "config.h"
#include <string>
#include <getopt.h>
#include <unistd.h>
#include "Networkinterface.h"
#include "Service.h"

#define no_argument 0
#define required_argument 1
#define optional_argument 2

using namespace std;

/**
 * Methode zum Ausgeben der Benutzungshinweise der Anwendung
 * Beendet die Anwendung danach
 */
void print_usage() {
	printf("transmissionservice - Empfaengt und versendet Positionsdaten\n");
    printf("Anwendung: transmissionservice [options]\n");
    printf("Options:\n");
    printf("-s, --sendport=PORT\t\tUDP-Sendeport Defaultwert: %d\n", SENDPORT);
    printf("-r, --recvport=PORT\t\tTCP-Empfangsport Defaultwert: %d\n", RECVPORT);
    printf("-i, --interface=NAME\t\tNetzwerkinterfacename im System an dem die\n");
    printf("\t\t\t\tPositionsdaten gesendet werden sollen.\n");
    printf("\t\t\t\tDefaultwert: %s\n", NETWORKINTERFACE);
    printf("-h, --help\t\t\tAnwendungsoptionen anzeigen\n");

    exit( EXIT_FAILURE );
}

int main(int argc, char** argv) {
	// Umgebungsparameter der Anwendung mit Default-Werten fuellen
	int sendport = SENDPORT;
	int recvport = RECVPORT;
	string interfaceName(NETWORKINTERFACE);

	// Umgebungsparameter mit Konsoleneingaben ueberschreiben
	const struct option long_opts[] = {
			{"sendport", 	required_argument, 	0, 	's'},
			{"recvport", 	required_argument,	0,	'r'},
			{"interface",	required_argument, 	0, 	'i'},
			{"help",		no_argument, 		0, 	'h'},
			{0,				0,					0,	0}
	};

	int opt = 0;
	while((opt = getopt_long(argc, argv, "hs:r:a:", long_opts, 0)) != -1) {
		switch (opt) {
			case 'h' : print_usage();
				break;
		    case 's' : sendport = atoi(optarg);
		    	break;
		    case 'r' : recvport = atoi(optarg);
		    	break;
		    case 'i' : interfaceName = optarg;
		    	break;
		    default: print_usage();
		    	break;
		}
	}

	// Pruefen ob sende und Empfangsport gleich sind
	if(sendport == recvport) {
		printf("Empfangs- und Sendeport duerfen nicht gleich sein!\n");
		print_usage();
	}

	cout << "Parameter:" << endl << "Sendeport: \t\t" << sendport << endl;
	cout << "Empfangsport: \t\t" << recvport << endl << "Netzwerkinterface: \t" << interfaceName << endl;
	cout << endl << "Ermittle Netzwerkinterfacedaten..." << endl;

	// Pruefen ob es die Netzwerkschnittstelle im System gibt
	Networkinterface* interface = new Networkinterface();
	if(!interface->determineInterface(interfaceName)) {
		printf("Netzwerkinterface %s konnte nicht gefunden werden!\n", interface->getName().c_str());
		print_usage();
	}

	// Daten des Netzwerkinterfaces ausgeben:
	cout << endl << "Netzwerkinterface: " << interface->getName() << endl;
	cout << "\tAdresse: \t" << inet_ntoa(interface->getAddress()->sin_addr) << endl;
	cout << "\tBroadcast: \t" << inet_ntoa(interface->getBroadcastAddress()->sin_addr) << endl;
	cout << "\tMaske: \t\t" << inet_ntoa(interface->getNetmask()->sin_addr) << endl;

	// Service starten
	cout << "Uebertragungsdienst starten..." << endl;

	// Dienst starten lassen
	Service* service = new Service(sendport, recvport, interface);
	service->start();

	exit(EXIT_SUCCESS);
}
