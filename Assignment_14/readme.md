# Assignment: Disassemblieren einer Payload



Bei einem Security-Assessment wurde eine Payload gefunden, die von einem Angreifer in ein laufendes System injiziert wurde. Diese liegt Ihnen vor und soll nun analysiert werden.

In diesem Assignment geht es darum, durch die statisch Analyse einer Datei Aussagen über deren Funktionalität und die Intentionen des Angreifers zu machen. Hierzu werden wir das `radare2`-Tool aus dem Radare2-Paket verwenden.


## Hinweis

Bei dem Executable handelt es sich um ein Programm unbekannter Funktionalität, wie man sie z.B. bei der Untersuchung von kompromittierten Rechner finden könnte. Es kann gut sein, dass es sich um eine _Malware_ handelt, welche bei der Ausführung Schaden verursacht, bis hin zur Zerstörung aller Daten auf dem Rechner. Deswegen sollten Sie die Datei __auf keinen Fall__ ohne Schutzmaßnahmen (virtuelle Maschine etc.) __ausführen__. Die hier vorgenommene Analyse kommt ohne Ausführung der Datei aus und ist insofern sicher auch ohne Schutzmaßnahmen durchführbar.

Sie müssen in der Realität damit rechnen, dass die Malware Schwachstellen in den von Ihnen verwendeten Werkzeugen nutzt, um bei einem Reverse-Engineering Ihren Rechner anzugreifen. Da wir uns hier in einem Übungskontext befinden, ignorieren wir dieses Problem.

## Aufgabe

Sie finden die Payload in der folgenden Datei:

  * [payload_3.bin](payload_3.bin)

Verwenden Sie `radare2`, um den Inhalt zu analysieren. Öffnen Sie die Datei mit `r2 payload_3.bin` und disassemblieren Sie den Inhalt mit dem Kommando `pd`.

Betrachten Sie den Assembler-Code und versuchen Sie herauszufinden, was die Datei macht.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.