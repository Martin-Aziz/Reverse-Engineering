
# Assignment: Speicherlayout eines Prozesses ausgeben

Erkenntnisse zu den Veränderungen bei mehrfachen läufen
---
```console
1. Durchlauf
Global initialisierte Variable: 00404004
Global nicht initialisierte Variable: 00407070
Globale Konstante Variable: 00405064
Dynamisch alloziierter Speicher: 00B91610
Adresse der Hauptfunktion: 00401497
Adresse der printf-Funktion: 00403B20
Lokale Variable in der Funktion: 0061FEEC
Statische lokale Variable in der Funktion: 00404008

2. Durchlauf
Global initialisierte Variable: 00404004
Global nicht initialisierte Variable: 00407070
Globale Konstante Variable: 00405064
Dynamisch alloziierter Speicher: 006F1878
Adresse der Hauptfunktion: 00401497
Adresse der printf-Funktion: 00403B20
Lokale Variable in der Funktion: 0061FEEC
Statische lokale Variable in der Funktion: 00404008
```
Bei mehrfacher Ausführung ändern sich die Adressen, bis auf die des zugewiesenen Malloc Speicher, nicht. Da Malloc Speicher auf dem Heap reserviert und diesen nach free(dynamicMemory) freigibt, so dass bei jeder Ausführung neuer Speicher gegeben wird.

Erkenntnisse zum Speicheraufbau
---
Es gibt einen globalen Datenbereich, welcher nicht initialisierte und initialisierte Varaiblen und Konstanten speichert und feste Adressen, während der Programmausführung besitzt.
Außerdem gibt es einen dynamischen Speicher, wie malloc, welcher einen Speicherbereich reserviert und diesen freigeben kann. Variablen von Funktionen werden auf dem Stack gespeichert, welcher freiegegben wird, wenn die Funktion beendet wurde. Speicherbereiche für Funktionen aus der Standardbibliothek werden im gleichen Adressraum wie der Rest gespeichert, bekommen jedoch einen speziellen Speicherbereich. Die Adressen werden zufällig vergeben.