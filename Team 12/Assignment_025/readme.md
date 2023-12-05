# Assignment: Analyse mit Ghidra (license_check)

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 29.11.2023** 📆

In diesem Assignment werden Sie eine ausführbare Datei (Executable) mit Ghidra untersuchen und versuchen dem Programm ein Flag zu entlocken.


## Ghidra

Diese Aufgabe verwendet [Ghidra](https://ghidra-sre.org/), ein umfangreiches Reverse-Engineering-Tool, das von der NSA entwickelt und als Open-Source-Lösung frei zur Verfügung gestellt wird.

Laden Sie Ghidra herunter und installieren Sie es auf Ihrem Rechner.

## Aufgabe

Laden Sie die folgende Datei herunter und analysieren Sie sie in Ghidra:

  * [license_check](license_check)

Das Programm verwendet eine Lizenzdatei, die im selben Verzeichnis liegen muss.

  * [license_file.key](license_file.key)

Das Programm prüft eine [Lizenzdatei](license_file.key) darauf, ob Sie eine gültige Lizenz zur Ausgabe des Flags besitzen. Diese Datei ist über eine Checksumme gegen Veränderungen geschützt. Aktuell fehlt Ihnen die Lizenz, d.h. Sie müssen die Lizenzdatei anpassen.

Analysieren Sie das Programm, um zu verstehen, wie es die Lizenz ermittelt und welche Schutzmaßnahmen gegen eine Änderung der Lizenzdatei getroffen wurden.

*Tipp*: Versuchen Sie **nicht**, die Checksumme über einen Brute-Force-Angriff zu manipulieren -- dieses Vorgehen dauert bei 4 Milliarden Möglichkeiten viel zu lange. Nutzen Sie stattdessen die Schwachstellen des verwendeten Algorithmus aus. Ein paar interessante Ansätze hierzu finden Sie [hier](https://stackoverflow.com/questions/48247647/how-do-i-modify-a-file-while-maintaining-its-crc-32-checksum).


## Flags sammeln

Wenn Sie das Flag erhalten haben, so tragen Sie das Flag bitte auf der [CTF-Webseite](http://tank.informatik.hs-mannheim.de) ein. Bei der ersten Benutzung legt sich jedes Team einen Benutzer an, der wie das Team heißt.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.