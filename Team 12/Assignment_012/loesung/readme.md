# Core Dump erstellen und analysieren

1. dumpme herunterladen, mit 'chmod +x' ausführbar machen und anschließend ausführen

````
dennis@dennis-VirtualBox:~/Dokumente/REE$ chmod +x dumpme
dennis@dennis-VirtualBox:~/Dokumente/REE$ ./dumpme
Please be patient, the answer is near
````

2. Die Ausgabe aus Schritt 1 zeigt, dass die Ausführung der dumpme Datei nicht terminiert. Deshalb schauen wir im nächsten Schritt, ob ein Prozess existiert. Eine Übersicht, über alle laufenden Prozesse bekommt man durch den Befehl 'ps aux'. Durch 'grep "prozessname"' kann man zudem direkt nach einem bestimmten Prozess suchen. Alternativ sucht man manuell nach dem Prozess der dumpme Datei.

````
dennis@dennis-VirtualBox:~/Dokumente/REE$ ps aux
dennis    426388  0.0  0.0   2492   516 pts/0    S+   15:35   0:00 ./dumpme
````

3. Um ein Abbild des Prozessspeichers der dumpme Datei zu erhalten und damit Einblick in den Stack, Heap und weitere Datenstrukturen zu erhalten erstellen wir einen core dump des laufenden dumpme Prozesses über den gcore Befehl gefolgt von der Prozess ID. Dieser Befehl erstellt eine Datei mit dem Dateinamen core.prozessid. 

````
dennis@dennis-VirtualBox:~/Dokumente/REE$ sudo gcore 426388
Saved corefile core.426388
````

4. Die core Datei kann anschließend mit debugging tools oder GDB analysiert werden. In unserem Fall sind wir auf der Suche nach einer Flag, daher durchsuchen wir die core Datei nach dem Keyword 'FLAG'. Dazu lassen wir uns alle strings der core Datei ausgeben und kombinieren diesen Befehl mit dem Such-command 'grep', wodurch wir innerhalb aller Strings nach einem bestimmten String suchen können. Als Ergebnis erhalten wir alle Strings die das Keyword "FLAG" enthalten.

````
dennis@dennis-VirtualBox:~/Dokumente/REE$ strings core.426388 | grep "FLAG"
FLAG{humpy_dumpy}
````