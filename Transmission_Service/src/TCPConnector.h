/*
   TCPConnector.h

   TCPConnector class interface. TCPConnector provides methods to actively
   establish TCP/IP connections with a server.

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
   limitations under the License
*/

#ifndef __tcpconnector_h__
#define __tcpconnector_h__

#include <netinet/in.h>
#include "TCPStream.h"

/**
 * Klasse zur Repraesentierung eines TCP-Clients
 * @author	Vic Hargrave
 * @date	05.11.2014
 */
class TCPConnector
{
  public:
	/**
	 * Verbindet sich zu einen TCP-Server
	 * @param server Adresse des Servers
	 * @param port Port des TCP-Servers
	 * @return TCPStream zwischen Client und Server, NULL bei Fehler
	 */
    TCPStream* connect(const char* server, int port);

    /**
     * Verbindet sich zu einen TCP-Server
     * @param server Adresse des Servers
     * @param port Port des TCP-Servers
     * @param timeout Timeoutwert in Sekunden
     * @return TCPStream zwischen Client und Server, NULL bei Fehler
     */
    TCPStream* connect(const char* server, int port, int timeout);

  private:
    /**
     * Loest einen DNS-Name in eine IP-Adresse auf
     * @param host Name des Hosts
     * @param addr IP-Adresse des Hosts
     * @return 0 bei Erfolg, bei Fehler den Fehlercode der Funktion getaddrinfo
     */
    int resolveHostName(const char* host, struct in_addr* addr);
};

#endif
