# Assignment: Strings mit rabin2 extrahieren



In diesem Assignment werden Sie versuchen, einer ausführbaren Datei (Executables) ihre Geheimnisse zu entlocken, indem Sie das `rabin2`-Tool aus dem Radare 2 Paket verwenden.


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

Das Werkzeug `rabin2` kann dazu verwendet werden, eine Reihe von Informationen aus einer Binärdatei zu extrahieren. Anders als `strings` versteht es das Format von ausführbaren Dateien (z.B. ELF unter Linux) und kann daher Informationen aus den verschiedenen Bereichen der Binärdatei sehr gezielt extrahieren.

Zeichenketten aus der `.data`-Sektion des ELF-Binaries lassen sich mit `rabin2 -z DATEINAME` ausgeben.

Nehmen Sie sich die folgenden Dateien vor und verwenden Sie `rabin2`, um sich alle Zeichenketten anzeigen zu lassen, die in der `.data`-Sektion vorhanden sind.

  * [password_check_1](password_check_1)
  * [password_check_2](password_check_2)
  * [password_check_3](password_check_3)

Versuchen Sie mit dieser Information das Flag zu extrahieren bzw. zu erhalten.



## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.