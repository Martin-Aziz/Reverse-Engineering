# Assignment: Executable mit radare2 patchen



In diesem Assignment werden Sie eine ausführbare Datei (Executable) untersuchen und danach so patchen, dass das Flag ausgegeben wird. Hierzu verwenden wir ein spezielles Reverse-Engineering Tool namens Radare 2, sodass wir nicht mit verschiedenen Werkzeugen arbeiten müssen.


## Flags

Die Executables enthalten ein Geheimnis (Flag), das in der Form `FLAG{GEHEMNIS}` ausgegeben wird, wenn Sie das richtige Passwort angeben. Leider kennen Sie das Passwort nicht.

_Beispiel:_

```console
$ ./password_check_1
Enter password: my_password
FLAG{a secret string}
```

Ihre Aufgabe ist es, diese Geheimnisse aus den Dateien zu extrahieren. Sie können versuchen, das Passwort oder direkt das Flag zu finden. Ein Brute-Force-Angriff auf das Passwort ist aber nicht Teil dieser Übung -- wir betreiben hier Reverse-Engineering und kein Cracking ;-)


## Radare 2

Für diese Übung werden wir das Kommandozeilen-Reverse-Engineering-Werkzeug Radare 2 einsetzen. Sie finden Tipps zur Installation und Verwendung in der [Kurzanleitung](../help/radare2.md).

## Aufgabe

Die folgende Datei gibt das Flag nicht aus, auch wenn Sie das richtige Passwort eingeben. Es ergibt also keinen Sinn, das Passwort aus der Datei extrahieren zu wollen.

  * [password_check_6](password_check_6)

Für diese Übung verwenden wir das Tool `r2` bzw. `radare2`, um die Datei zu analysieren *und* zu patchen.

Gehen Sie wie folgt vor:

  * Öffnen Sie das Executable mit Radare 2. Damit Sie direkt den Patch durchführen können, sollten Sie die Datei im Schreibmodus öffnen (Option `-w`): `r2 -w password_check_6`.
  * Suchen Sie nach der `main`-Funktion mithilfe der Suchfunktion (`s`).
  * Wechseln Sie in den _visuellen Modus_ des Disassemblers von `r2`, indem Sie `v` drücken. (Sie können die Anzeige nach rechts verbreitern, indem Sie RETURN drücken.)
  * Scrollen Sie durch das Assembler-Listing, bis Sie die entsprechende Stelle gefunden haben. Sie können mit den Pfeiltasten navigieren.
  * Schieben Sie die Stelle, die Sie patchen wollen ganz nach oben, d.h. in die erste Zeilen.
  * Rufen Sie mit `A` den interaktiven Assembler auf.
  * Geben Sie so viel `nop`-Instruktionen durch `;` getrennt an, wie nötig sind, um den Sprungbefehl zu ersetzen.
  * Drücken Sie ENTER und speichern Sie die Änderungen.
  * Verlassen Sie mit `q` den visuellen Modus (bzw. `qq`, wenn Sie die Anzeige verbreitert haben) und dann mit CTRL-D Radare.
  * Führen Sie das gepatchte Programm aus und geben Sie ein beliebiges Passwort ein.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.