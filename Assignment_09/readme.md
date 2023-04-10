# Assignment: Core Dump erstellen und mit strings analysieren

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 25.10.2022** 📆

In diesem Assignment werden Sie versuchen, einer ausführbaren Datei (Executables) ihre Geheimnisse zu entlocken, indem Sie das `strings`-Tool verwenden. Da die gesuchten Informationen nicht im Executable selbst zu finden sind, untersuchen wir den Speicher des laufenden Prozesses.

Gesucht wird wie immer ein **Flag** im Format `FLAG{...}`, das diesmal aber nicht nach der Eingabe eines korrekten Passworts ausgegeben wird, sondern aus dem Speicher extrahiert werden muss.

## Aufgabe

Schauen Sie sich die Funktionsweise des Werkzeuges `gcore` unter Linux an. Je nach Einstellung Ihres Systems müssen Sie das Tool als `root` ausführen, d.h. mit `sudo` verwenden.

Laden Sie folgende Datei herunter:

  * [dumpme](dumpme)

Starten Sie das Programm und beobachten Sie die Ausgabe. Wahrscheinlich reicht Ihre Geduld nicht aus, um auf die Ausgabe des Flags zu warten. Dumpen Sie deshalb den Prozessspeicher und untersuchen Sie das erstellte _Core-File_ mit `strings`. Sie können in der Ausgabe mit `grep` nach dem Flag suchen.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.