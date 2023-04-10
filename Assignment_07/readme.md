# Assignment: Einen Hexeditor verwenden, um Strings zu finden



In diesem Assignment werden Sie einen Hex-Editor einsetzen, um eine ausführbare Datei (Executable) zu untersuchen.


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

Leider kennen Sie das Passwort nicht. Sie können die Datei mit dem `strings`-Tools untersuchen, werden aber wahrscheinlich keine Informationen zu dem Passwort oder dem Flag finden.

Installieren Sie einen Hex-Editor und verwenden Sie ihn, um die folgende Datei zu analysieren:

  * [password_check_3](password_check_3)

**Hinweis**: Welchen Hex-Editor Sie verwenden, ist Ihnen überlassen. Für Linux reicht `hexedit` als Konsolenanwendung, die Sie unter Ubuntu mit `sudo apt install hexedit` installieren.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.