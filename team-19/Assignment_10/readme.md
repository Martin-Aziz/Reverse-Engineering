# Assignment: Disassemblieren mit Radare 2



In diesem Assignment werden Sie versuchen, einer ausführbaren Datei (Executables) ihre Geheimnisse zu entlocken, indem Sie sie mit dem `radare2`-Tool disassemblieren.


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

Nehmen Sie sich die folgenden Dateien vor und verwenden Sie `radare2`, um das Programm zu disassemblieren.

  * [number_check_1](number_check_1)

In diesem konkreten Fall ist das Passwort eine Zahl. Diese wird sich als Konstante direkt im Assembler verstecken und lässt sich deshalb nicht mit `strings` oder ähnlichen Werkzeugen extrahieren.

Wir werden deshalb `radare2` dazu verwenden, um die Information zu der Konstante aus der Binärdatei zu extrahieren, indem wir das Programm disassemblieren.

Gehen Sie dabei wie folgt vor:

  * Laden Sie die Datei mit `radare2 number_check_1`
  * Analysieren Sie sie mit dem Kommando `aaa`
  * Suchen Sie mit `s main` die Main-Funktion
  * Geben Sie mit `pd` (Print Disassembly) den Maschinencode aus
  * Suchen Sie nach einer `cmp`-Instruktion, die ein Register mit einer festen Konstanten vergleicht
  * Die Konstante ist wahrscheinlich die gesuchte Zahl, die Sie nur noch in das Dezimalsystem umrechnen müssen


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.