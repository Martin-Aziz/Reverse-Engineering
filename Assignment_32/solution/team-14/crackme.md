
# Assignment 31 Eigenes CrackMe 
<br>


## Table of contents

- [Schwachstelle](#schwachstelle)
- [Vorgehen](#vorgehen)
- [Flag](#flag)
- [license.key Änderungen zum extrahieren der Flag](#licensekey--nderungen-zum-extrahieren-der-flag)
- [Beschreibung der Dateien der Abgabe](#beschreibung-der-dateien-der-abgabe)
- [Creators](#creators)



## Schwachstelle

Aus _technischen_ Gründen werden für den Programmablauf relevante Werte innerhalb einer externen Datei gespeichert.
Um die Verwundbarkeit zu verringern, wurde die Datei `license.key` genannt, obwohl sie nichts mit einem Lizenzschlüssel zu tun hat. Hierbei handelt es sich um eine einwandfreie Sicherheitsmaßnahme.
Die Datei enthält zwei für den Programmablauf relevante Hex-Zeichefolgen. 
Zum einen den statischen Teil einer Funktionsadresse, welche aufgerufen werden soll.
Zum anderen sechs 1Byte Zahlen, welche in einem Sicherheitsalgorithmus verrechnet werden, um eine zusätzliche Sicherheitsschicht zu bieten. 
Es muss keine Änderung innerhalb des eigentlichen Programms getätigt werden, lediglich die Abläufe analysiert und entsprechend die `license.key` Datei modifiziert werden, um die Flag zu erhalten.


## Vorgehen

Der grundlegende Aufbau besteht aus dem eigentlichen Programm und der dazugehörigen `license.key` Datei.
Die besagte `license.key` Datei beinhaltet jedoch keine Lizenz die geprüft wird, sondern die letzten 12 Bit einer Funktionsadresse. Diese 12 Bit werden im Programm mit dem statischen Adressteil des Adressspaces kombiniert, um die, für die aktuelle Programmausführung gültige, ganze Funktionsadresse zu erhalten. Standardmäßig handelt es sich bei den ersten 12 Bit der `license.key` Datei um die letzten 12 Bit der Adresse der `lose` Funktion (Adressende: '0x21A'), welche aufgerufen wird. 

Die Herausforderung besteht also darin zunächst die richtige Funktionsadresse der `win` Funktion  (Adressende: '0x316') zu ermitteln. Dies ist z.B über `gdb` mittels dem Befehl `info functions win` möglich. 
Wurde die besagte Funktionsadresse gefunden, können deren letzte 12 Bit in die `license.key` Datei geschrieben werden. Bei erneutem Ausführen springt das Programm in die `win` Methode, welche die zweite Herausforderung bereithält. 

In der `license.key` Datei befinden sich neben der Funktionsadresse und einem Füllbyte `00` noch weitere Hexwerte.
Diese werden innerhalb der `win` Methode über das alternierende Addieren und Subtrahieren voneinander auf eine Zahl reduziert.
Wenn die Nutzer den Code weiter analysieren, sollten sie eine Abfrage finden, welche das Ergebnis dieser Berechnung mit dem Wert `0x2A` (`42`) vergleicht.
Werden nun innerhalb der `license.key` Datei die Hexwerte so gesetzt, dass nach der Verrechnung der Zahlen, das Ergebnis korrekt (also `0x2A`) ist, wird die `gg` Funktion aufgerufen. 

Die `gg` Funktion gibt daraufhin die Flag aus, nachdem diese via `xor` entschlüsselt wurde.
Hierbei kommt der vorher aus den Zahlenwerte errechnete Wert (`0x2A`), auf den eine Konstante (`0x5`) addiert wird,  als Schlüssel zum Einsatz.
Die innerhalb der `gg` Funktion getätigten mathematischen Operationen, sowie die mehrfachen Aufrufe der `gg` Funktion innerhalb der `win` Funktion, dienen dazu, dem Nutzer das errechnen bzw. extrahieren des Schlüssels der `xor`-Entschlüsselung deutlich zu erschweren. Sonst haben sie keinen praktischen Nutzen.


## Flag

__FLAG{license_to_reverse}__


## license.key Änderungen zum extrahieren der Flag

- die korrekten 12 Bit um die `win` Funktion aufzurufen:\
`32 6 ...`

- eine korrekte Zahlenfolge um die Zielsumme 42 zu erreichen:\
`... 14 00 0E 13 2B 10`

- vollständig korrekte `license.key` Datei um die Flag zu erhalten:\
`32 60 00 14 00 0E 13 2B 10`

## Beschreibung der Dateien der Abgabe
* crackme.md
    * Dieses Dokument
* Makefile
    * Makefile zum kompilieren des Programms
* crackme14.c
    * Quellcode des Programms
* crackme14
    * Kompiliertes Programm 
* license.key
    * Datei, deren Werte verändert werden müssen um die Schwachstelle auszunutzen
* crack_script.sh
    * Script zum Ausnutzen der Schwachstelle und Ausführen des gecrackten Programms
* reset_license_file_script.sh
    * Setzt die Lizenzdatei in den ungelösten Zustand zurück


## Creators

- **Nadine Bahadori**
- **Gregor Haase**
- **Simon Höfer**


