# Installationsanleitung
### Compilieren und Installieren
Fürs compilieren wird das Programm `cmake` benötigt, falls nicht vorhanden lässt es sich mit folgenden Befehl installieren:

 * `sudo apt-get install cmake`

Die Programme Client und Server benötigen zusätzlich die Qt5 Bibilotheken. Diese lassen sich wie folgt installieren:

 * `sudo apt-get install qt5-default`

Um die Programme des Projektes zu compilieren und zu installieren müssen Sie ausgehend von diesen Verzeichnis folgende Befehle ausführen:

 * `mkdir build`
 * `cd build`
 * `cmake ../`
 * `make install`
 
Wenn Sie nur ein bestimmtes Programm compilieren wollen müssen Sie einfach eine oder mehrere der Optionen

 * `CLIENT=1`
 * `SERVER=1`
 * `SERVICE=1`

An den `cmake` Befehl hängen. Beispiel compilieren des Transmission-Service: `cmake ../ -DSERVICE=1` oder Client und Server zusammen: `cmake ../ -DCLIENT=1 -DSERVER=1`.

Wenn Sie zusätzlich die Doxygen Dokumentation erstellen wollen fügen Sie die Option `WITH_DOXYGEN=1` an und führen Sie den Befehl `make doc` aus.

Im Anschluss solle sich die Programm des Projektes im Unterzeichnis `bin` befinden.

