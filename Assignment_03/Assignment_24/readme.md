# Assignment: Executable mit Ghidra analysieren (password_check_11)

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 29.11.2022** 📆

In diesem Assignment werden Sie eine ausführbare Datei (Executable) mit Ghidra untersuchen und versuchen dem Programm ein Flag zu entlocken.


## Ghidra

Diese Aufgabe verwendet [Ghidra](https://ghidra-sre.org/), ein umfangreiches Reverse-Engineering-Tool, das von der NSA entwickelt und als Open-Source-Lösung frei zur Verfügung gestellt wird.

Laden Sie Ghidra herunter und installieren Sie es auf Ihrem Rechner.

## Aufgabe

Laden Sie die folgende Datei herunter und analysieren Sie sie in Ghidra:

  * [password_check_11](password_check_11)

Versuchen Sie die Funktionsweise zu verstehen und nutzen Sie dieses Wissen dann aus, um sich das Flag ausgeben zu lassen. Hierbei geht es darum, __eine Eingabe__ zu finden, die das Programm dazu bewegt, das Flag auszugeben.

**Tipp**: Versuchen Sie die Variable, welche den Aufruf der `win()`-Funktion kontrolliert durch Ausnutzung einer sehr speziellen und verborgenen Funktion des Programms zu schreiben.


## Abgabe

  * Beschreiben Sie, um welche Schwachstelle es sich handelt und wie Sie diese ausgenutzt haben, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Versuchen Sie die Ausnutzung der Schwachstelle/Besonderheit in Form eines kleinen Skriptes zu formulieren.
  * Welche Information konnten Sie extrahieren?

Um das Schreiben des Skriptes zu vereinfachen, steht ihnen eine Hilfsklasse in Ruby zur Verfügung:

  * [crackme.rb](crackme.rb)

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.