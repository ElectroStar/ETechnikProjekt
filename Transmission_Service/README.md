# Anwendungsanleitung
### Compilieren und Installieren
Fürs compilieren wird das Programm `cmake` benötigt, falls nicht vorhanden lässt es sich mit folgenden Befehl installieren:

 * `sudo apt-get install cmake`

Um den Übertragungsdienst zu compilieren und zu installieren müssen Sie ausgehend vom Verzeichnis `ETechnikProjekt/Transmission_Service/` folgende Befehle ausführen:

 * `mkdir build`
 * `cd build`
 * `cmake ../`
 * `make`
 * `make install`
 
Im Anschluss solle sich das Programm des Übertragungsdienst im Unterzeichnis `bin` des Verzeichnis `Transmission_Service` befinden.

### Ausführen
Der Übertragungsdienst besitzt folgende Standardoptionen:

 * TCP-Empfangsport 50728 
 * UDP-Zielport 50729
 * Verwendetes Netzwerkinterface zum Versenden wlan0
 
Diese Aufrufsoptionen können per Kommandozeilenaufruf geändert werden. Mit dem Aufrufsparameter `-h` können die ganzen Optionen eingesehen werden.
