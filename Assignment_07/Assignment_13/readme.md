# Assignment: gdb

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 01.11.2022** 📆

In diesem Assignment werden Sie einen Debugger einsetzen, um eine ausführbare Datei (Executable) zu untersuchen.


## Flags

Die Executables enthalten ein Geheimnis (Flag), das in der Form `FLAG{GEHEMNIS}` ausgegeben wird, wenn Sie das richtige Passwort angeben. Leider kennen Sie das Passwort nicht.

_Beispiel:_

```console
$ ./password_check_1
Enter password: my_password
FLAG{a secret string}
```

Ihre Aufgabe ist es, diese Geheimnisse aus den Dateien zu extrahieren. Sie können versuchen, das Passwort oder direkt das Flag zu finden. Ein Brute-Force-Angriff auf das Passwort ist aber nicht Teil dieser Übung -- wir betreiben hier Reverse-Engineering und kein Cracking ;-)


## gdb

Für diese Übung werden wir den Kommandozeilendebugger `gdb` einsetzen. Sie finden Tipps zur Installation und Verwendung in der [Kurzanleitung](../help/gdb.md).

## Aufgabe

Bei der folgenden Datei versagen sowohl `strings`, als auch ein Hex-Editor. Deswegen wollen wir uns die Datei im Debugger ansehen.

  * [password_check_4](password_check_4)

Starten Sie den Debugger und teilen Sie ihm mit, dass Sie diese Datei analysieren wollen:

```console
$ gdb password_check_4
GNU gdb (Ubuntu 9.2-0ubuntu2) 9.2
...
(No debugging symbols found in password_check_4)
(gdb) _
```

Versuchen Sie nun, die Stelle im Programm zu finden, an der das Passwort entschlüsselt wird und setzen Sie direkt danach einen Breakpoint. Untersuchen Sie die Eingabeparameter der Funktion und eventuell Rückgaben. Dort sollten Sie das im Programm verschlüsselte Passwort jetzt entschlüsselt vorfinden. Mit diesem können Sie sich dann das Flag ausgeben lassen.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.