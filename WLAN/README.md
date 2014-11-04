# Installationsanleitung
### Installation
Folgendende Pakete müssen installiert werden:

 * dnsmasq
 * hostapd

Dazu folgenden Befehl ausführen:

 * ```sudo apt-get install dnsmasq hostapd```
 
Im Anschluss sollen die Service zur Sicherheit beendet werden und dafür gesorgt werden das diese nicht automatisch beim Systemstart gestartet werden. Dafür folgende vier Befehle ausführen:

 * ```sudo service hostapd stop```
 * ```sudo service dnsmasq stop```
 * ```sudo update-rc.d hostapd disable```
 * ```sudo update-rc.d dnsmasq disable```
 
Die beiden Konfigurationsdateien [hostapd.conf](https://github.com/ElectroStar/ETechnikProjekt/blob/master/WLAN/hostapd.conf) und [dnsmasq.conf](https://github.com/ElectroStar/ETechnikProjekt/blob/master/WLAN/dnsmasq.conf) ins Verzeichnis /etc/ kopieren ggf. ersetzen.

Das Skript [start.sh](https://github.com/ElectroStar/ETechnikProjekt/blob/master/WLAN/start.sh) kann an einen beliebigen Ort kopiert werden. Das Skript benötigt Ausführungsrechte. Diese können mit folgenden Befehl gegeben werden:
 
 * ```chmod +x start.sh```

### Benutzung des Skripts
Das Skript kann wie folgt aufgerufen werden:

 * ```sudo ./start.sh```
 
Das Skript kann per STRG+C abgebrochen werden. In diesen Fall wird wieder der Network-Manager Service gestartet.


### Mögliche Fehler
Es kann sein das ein WLAN-Adapter/Sick nicht von hostapd unterstützt wird, ggf. der Treiber im [hostapd.conf](https://github.com/ElectroStar/ETechnikProjekt/blob/master/WLAN/hostapd.conf) geändert werden muss. Mit dem Befehl ``` iw list | grep ap``` ob der Access-Point Modus unterstützt wird. Wenn nichts gefunden wird, wird der Adapter nicht unterstützt dann muss ggf. ein anderer Treiber als nl80211 gewählt werden.
