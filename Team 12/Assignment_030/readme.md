# Assignment: Analyse mit Ghidra (pwnable 21)

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 13.12.2023** 📆

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

  * [pwnable_21](pwnable_21)

Versuchen Sie eine Schwachstelle zu entdecken und nutzen Sie diese dann aus, um sich das Flag ausgeben zu lassen. Hierbei geht es darum, __eine Eingabe__ zu finden, die das Programm dazu bewegt, das Flag auszugeben.

**Tipp**: Versuchen Sie die Variable, welche den Aufruf der `win()`-Funktion kontrolliert durch Ausnutzung einer Schwachstelle zu schreiben.


## Das echte Flag erhalten

Das Executable enthält nicht direkt das Flag, sondern nur eine `win()`-Funktion, die das Flag ausgibt. Deswegen finden Sie auf der [CTF-Webseite](http://tank.informatik.hs-mannheim.de) die Information, wo Sie dem  Executable das Flag entlocken können. Hier ist ein Netzwerkdienst angegeben, z.B. `tank.informatik.hs-mannheim.de:3001`, h.h. auf Port `3001` des Servers `tank.informatik.hs-mannheim.de` lauscht das Programm auf Ihre Eingaben. Der Server ist nur aus dem Hochschulnetz erreichbar.

Verwenden Sie netcat (`nc`), um Ihre Eingaben an das Programm zu senden:

```console
$ nc tank.informatik.hs-mannheim.de 3001
Enter your name: Thomas
Hello Thomas
```

`telnet` ist an dieser Stelle keine gute Wahl, weil es die Daten nicht immer roh überträgt.


## Flags sammeln

Wenn Sie das Flag erhalten haben, so tragen Sie das Flag bitte auf der [CTF-Webseite](http://tank.informatik.hs-mannheim.de) ein. Bei der ersten Benutzung legt sich jedes Team einen Benutzer an, der wie das Team heißt.


## Abgabe

  * Beschreiben Sie, um welche Schwachstelle es sich handelt und wie Sie diese ausgenutzt haben, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Versuchen Sie die Ausnutzung der Schwachstelle/Besonderheit in Form eines kleinen Skriptes zu formulieren.
  * Welche Information konnten Sie extrahieren?

Um das Schreiben des Skriptes zu vereinfachen, steht ihnen eine Hilfsklasse in Ruby zur Verfügung:

  * [crackme.rb](crackme.rb)

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.