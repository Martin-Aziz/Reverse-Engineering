# Assignment: Flag mit strings extrahieren



In diesem Assignment werden Sie versuchen, einer ausführbaren Datei (Executables) ihre Geheimnisse zu entlocken, indem Sie das `strings`-Tool verwenden.


## Flags

Die Executables enthalten ein Geheimnis (Flag), das in der Form `FLAG{GEHEMNIS}` ausgegeben wird, wenn Sie das richtige Passwort angeben. Leider kennen Sie das Passwort nicht.

_Beispiel:_

```console
$ ./password_check_1
Enter password: my_password
FLAG{a secret string}
```

Ihre Aufgabe ist es, diese Geheimnisse aus den Dateien zu extrahieren. Sie können versuchen, das Passwort oder direkt das Flag zu finden. Ein Brute-Force-Angriff auf das Passwort ist aber nicht Teil dieser Übung -- wir betreiben hier Reverse-Engineering und kein Cracking ;-)

## Aufgabe

Nehmen Sie sich die folgenden Dateien vor und verwenden Sie `strings`, um sich alle Zeichenketten anzeigen zu lassen, die in der Datei vorhanden sind.

  * [password_check_1](password_check_1)
  * [password_check_2](password_check_2)
  * [password_check_3](password_check_3)

**Hinweis**: Die Datei `password_check_3` lässt sich wahrscheinlich nicht mit `strings` alleine bezwingen. Diese werden wir uns im nächsten Assignment vornehmen.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.