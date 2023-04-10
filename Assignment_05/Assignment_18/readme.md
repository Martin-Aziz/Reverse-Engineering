# Assignment: Schwachstelle finden und ausnutzen



In dem vorliegenden Binary befindet sich eine Schwachstelle, die Sie finden sollen und dann ausnutzen, um das im Programm gespeicherte Flag zu erhalten. Das Flag per Debugger zu extrahieren ist __keine__ gültige Lösung dieser Aufgabe.

Sie können zur Analyse Radare 2 benutzen.


## Radare 2

Für diese Übung werden wir das Kommandozeilen-Reverse-Engineering-Werkzeug Radare 2 einsetzen. Sie finden Tipps zur Installation und Verwendung in der [Kurzanleitung](../help/radare2.md).

## Aufgabe

Bitte analysieren Sie das folgende Executable, um eine Schwachstelle zu finden:

  * [greeter_2](greeter_2)

Wenn Sie eine Schwachstelle entdeckt haben, verwenden Sie diese, um das Flag auszugeben.

Gehen Sie, wenn Sie **Radare 2** benutzen, wie folgt vor:

  * Öffnen Sie das Executable mit Radare 2.
  * Suchen Sie nach der `main`-Funktion mithilfe der Suchfunktion (`s`).
  * Wechseln Sie in den _visuellen Modus_ des Disassemblers von `r2`, indem Sie `v` drücken. (Sie können die Anzeige nach rechts verbreitern, indem Sie RETURN drücken.)
  * Scrollen Sie durch das Assembler-Listing und versuchen Sie das Programm zu verstehen.
  * Richten Sie Ihr Augenmerk auf den Aufruf von Bibliotheksfunktionen und die Anzahl der übergebenen Parameter.
  * Wenn Sie eine Schwachstelle gefunden haben, versuchen Sie diese auszunutzen.

<!--
Sie können auch **Ghidra** benutzen, um das Programm zu analysieren:

  * Öffnen Sie das Executable in Ghidra
  * Suchen Sie die `main`-Funktion im _Symbol-Tree_
  * Versuchen Sie anhand des C-Codes im Decompiler-Fenster das Programm zu verstehen
  * Richten Sie Ihr Augenmerk auf den Aufruf von Bibliotheksfunktionen und die Anzahl der übergebenen Parameter.
  * Wenn Sie eine Schwachstelle gefunden haben, versuchen Sie diese auszunutzen.
-->