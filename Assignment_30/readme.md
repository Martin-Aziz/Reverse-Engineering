# Assignment: Executable mit Ghidra analysieren (pwnable 23)



In diesem Assignment werden Sie eine ausführbare Datei (Executable) mit Ghidra untersuchen und versuchen dem Programm ein Flag zu entlocken.


## pwnable.xyz

Diese Aufgabe basiert auf einem crackme der Webseite [pwnable.xyz](https://pwnable.xyz/). Auf dieser Seite können Sie kleinere (und größere) Reverse-Engineering Aufgaben herunterladen und lösen. Durch Eingabe der gefundenen Flags auf der Webseite können Sie Punkte sammeln und im Leader-Board aufsteigen.

Da [pwnable.xyz](https://pwnable.xyz/) explizit darum bittet, keine Flags oder Lösungen zu veröffentlichen, gibt diese Aufgabe ein anderes Flag aus, als dort. Sie können Ihre Lösung dieser Aufgabe aber sehr leicht auf die von [pwnable.xyz](https://pwnable.xyz/) übertragen und dort dann entsprechende Punkte sammeln.

Für die Lösung dieser Aufgabe sind __nicht zulässig__

  * das Flag aus dem Executable zu extrahieren
  * einen Debugger zu verwenden, um das Flag auszulesen
  * das Executable zu patchen, um das Flag ausgeben zu lassen

Sie können einen Debugger verwenden, um das Programm besser zu verstehen, nicht aber, um das Flag auszulesen.

Ihre Lösung muss das Programm durch geeignete Eingaben dazu bewegen, das Flag auszugeben. Diese Eingaben und die Begründung, warum sie das gewünschte Ergebnis bringen, sind Teil Ihrer Abgabe zu der Aufgabe.


## Ghidra

Diese Aufgabe verwendet [Ghidra](https://ghidra-sre.org/), ein umfangreiches Reverse-Engineering-Tool, das von der NSA entwickelt und als Open-Source-Lösung frei zur Verfügung gestellt wird.

Laden Sie Ghidra herunter und installieren Sie es auf Ihrem Rechner.

## Aufgabe

Laden Sie die folgende Datei herunter und analysieren Sie sie in Ghidra:

  * [pwnable_23](pwnable_23)

Versuchen Sie eine Schwachstelle zu entdecken und nutzen Sie diese dann aus, um sich das Flag ausgeben zu lassen. Hierbei geht es darum, __eine Eingabe__ zu finden, die das Programm dazu bewegt, das Flag auszugeben.


## Abgabe

  * Beschreiben Sie, um welche Schwachstelle es sich handelt und wie Sie diese ausgenutzt haben, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Versuchen Sie die Ausnutzung der Schwachstelle/Besonderheit in Form eines kleinen Skriptes zu formulieren.
  * Welche Information konnten Sie extrahieren?

Um das Schreiben des Skriptes zu vereinfachen, steht ihnen eine Hilfsklasse in Ruby zur Verfügung:

  * [crackme.rb](crackme.rb)

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.