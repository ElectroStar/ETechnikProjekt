/*
   TCPStream.h

   TCPStream class interface. TCPStream provides methods to trasnfer
   data between peers over a TCP/IP connection.

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

#ifndef __tcpstream_h__
#define __tcpstream_h__

#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>
#include <string>

using namespace std;

/**
 * Klasse zur Repraesentierung eines TCP-Streams
 * @author	Vic Hargrave
 * @date	05.11.2014
 */
class TCPStream
{
    int     m_sd;
    string  m_peerIP;
    int     m_peerPort;

  public:
    friend class TCPServer;
    friend class TCPConnector;

    /**
     * Dekonstruktor
     */
    ~TCPStream();

    /**
     * Schreibt Daten aus dem Buffer in den Stream
     * @param buffer Datenbuffer
     * @param len Länge der Daten
     * @return Anzahl der geschriebenen Bytes
     */
    ssize_t send(const char* buffer, size_t len);

    /**
     * Liest Daten aus dem Stream
     * @param buffer Buffer in dem die Daten gespeichert werden sollen
     * @param len Maximale Länge des Buffers
     * @param timeout Wartezeit bis Daten im Stream vorliegen in Sekunden
     * @return Anzahl der gelesenden Bytes
     */
    ssize_t receive(char* buffer, size_t len, int timeout=0);

    /**
     * Ermittelt die Partner IP-Adresse
     * @return IP-Adresse des Partners
     */
    string getPeerIP();

    /**
     * Ermittelt den Port des Partners
     * @return Port des Partners
     */
    int    getPeerPort();

    /**
     * Gibt die Socketnummer zurueck
     */
    operator int();

    /**
     * Enum zum Status des Streams
     */
    enum {
        connectionClosed = 0,  //!< Verbindung geschlossen
        connectionReset = -1,  //!< Verbindungsreset
        connectionTimedOut = -2//!< Verbindungstimeout
    };

  private:
    /**
     * Wartet eine Zeit bis ein Event im Stream auftritt
     * @param timeout Wartezeit in Sekunden
     * @return true wenn ein Event aufgetreten ist, False bei Ablauf der Wartezeit
     */
    bool waitForReadEvent(int timeout);

    /**
     * Konstruktor
     * @param sd Socketnummer
     * @param address Adresse
     */
    TCPStream(int sd, struct sockaddr_in* address);

    /**
     * Konstruktor
     */
    TCPStream();

    /**
     * Kopierkonstruktor
     * @param stream TCPStream
     */
    TCPStream(const TCPStream& stream);
};

#endif
