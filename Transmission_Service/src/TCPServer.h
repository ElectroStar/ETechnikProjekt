/*
   TCPServer.h

   TCPServer class interface. TCPServer provides methods to passively
   establish TCP/IP connections with clients.

   ------------------------------------------

   Copyright � 2013 [Vic Hargrave - http://vichargrave.com]

   Licensed under the Apache License, Version 2.0 (the "License");
   you may not use this file except in compliance with the License.
   You may obtain a copy of the License at

       http://www.apache.org/licenses/LICENSE-2.0

   Unless required by applicable law or agreed to in writing, software
   distributed under the License is distributed on an "AS IS" BASIS,
   WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
   See the License for the specific language governing permissions and
   limitations under the License.
*/

#ifndef __tcpserver_h__
#define __tcpserver_h__

#include <string>
#include <netinet/in.h>
#include "TCPStream.h"

using namespace std;

/**
 * Klasse zur Repraesentierung eines TCP-Servers
 * @author	Vic Hargrave
 * @date	05.11.2014
 */
class TCPServer
{
    int    m_lsd;
    int    m_port;
    string m_address;
    bool   m_listening;

  public:
    /**
     * Konstruktor
     * @param port Port auf dem gehorcht werden soll
     * @param address Adresse welche Akzeptiert werden soll, wenn nicht gefüllt wird jeder Adresse akzeptiert
     */
    TCPServer(int port, const char* address="");

    /**
     * Dekonsturktor
     */
    ~TCPServer();

    /**
     * Startet den Server und bindet somit den Port und fängt das horchen an
     * @return Bei Erfolg 0 sonst Fehlercode vom bind oder listen Befehl
     */
    int        start();

    /**
     * Wartet bis ein gültiger Client sich verbunden hat
     * @return TCPStream des Clients, bei Fehler NULL
     */
    TCPStream* accept();

    /**
     * Gibt die Nummer des Sockets zurück
     */
    operator int();
};

#endif
