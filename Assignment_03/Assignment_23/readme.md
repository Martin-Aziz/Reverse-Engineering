# Assignment: Roundtrip mit Ghidra (C++ Programm)



In diesem Assignment werden Sie eine ausführbare Datei (Executable) mit Ghidra untersuchen und versuchen das Programm, aus dem sie erzeugt wurde, wieder zu rekonstruieren. Anders als die anderen Programme wurde dieses in C++ programmiert.


## Ghidra

Diese Aufgabe verwendet [Ghidra](https://ghidra-sre.org/), ein umfangreiches Reverse-Engineering-Tool, das von der NSA entwickelt und als Open-Source-Lösung frei zur Verfügung gestellt wird.

Laden Sie Ghidra herunter und installieren Sie es auf Ihrem Rechner.

## Aufgabe

Laden Sie die folgende Datei herunter und analysieren Sie sie in Ghidra:

  * [roundtrip_3](roundtrip_3)

Versuchen Sie die Datei zu analysieren und dann ein C++-Programm zu extrahieren, das exakt dieselbe Ausgabe wie diese Datei macht. Die Ausgaben ändern sich mit der Zeit, sodass Sie für den Vergleich Ihre Version und die gegebene nahezu gleichzeitig aufrufen müssen. Schreiben Sie ein Makefile, dass Ihr Programm compiliert (Target `all`) und einen Test durchführt, bei dem die Ausgabe von Ihrem und dem gegebenen Programm verglichen werden (Target `test`).