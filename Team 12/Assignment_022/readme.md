# Assignment: Analyse mit Ghidra (buggy_hello_world)

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 22.11.2023** 📆

In diesem Assignment werden Sie eine ausführbare Datei (Executable) mit Ghidra untersuchen und versuchen dem Programm ein Flag zu entlocken.


## Ghidra

Diese Aufgabe verwendet [Ghidra](https://ghidra-sre.org/), ein umfangreiches Reverse-Engineering-Tool, das von der NSA entwickelt und als Open-Source-Lösung frei zur Verfügung gestellt wird.

Laden Sie Ghidra herunter und installieren Sie es auf Ihrem Rechner.

## Aufgabe

Laden Sie die folgende Datei herunter und analysieren Sie sie in Ghidra:

  * [buggy_hello_world](buggy_hello_world)

Analysieren Sie das Programm, um zu verstehen, wie es funktioniert und suchen Sie dabei explizit nach einer Schwachstelle, die es Ihnen erlaubt das Flag auszugeben.


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

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.