# Assignment: Schwachstelle finden und ausnutzen



In dem vorliegenden Binary befindet sich eine Schwachstelle, die Sie finden sollen und dann ausnutzen, um das im Programm gespeicherte Flag zu erhalten. Das Flag per Debugger zu extrahieren ist __keine__ gültige Lösung dieser Aufgabe.
  
Verwenden Sie zur Analyse Ghidra.


## Ghidra

Diese Aufgabe verwendet [Ghidra](https://ghidra-sre.org/), ein umfangreiches Reverse-Engineering-Tool, das von der NSA entwickelt und als Open-Source-Lösung frei zur Verfügung gestellt wird.

Laden Sie Ghidra herunter und installieren Sie es auf Ihrem Rechner.


## Aufgabe

Bitte analysieren Sie das folgende Executable, um eine Schwachstelle zu finden:

  * [password_check_13](password_check_13)

Wenn Sie eine Schwachstelle entdeckt haben, verwenden Sie diese, um das Flag auszugeben.

Gehen Sie, wenn Sie **Ghidra** benutzen, wie folgt vor:

  * Öffnen Sie das Executable in Ghidra
  * Suchen Sie die `main`-Funktion im _Symbol-Tree_
  * Versuchen Sie anhand des C-Codes im Decompiler-Fenster das Programm zu verstehen
  * Richten Sie Ihr Augenmerk auf das Speichermanagement des Programms.
  * Wenn Sie eine Schwachstelle gefunden haben, versuchen Sie diese auszunutzen.