# Assignment: Mit gdb debuggen (password_check_4)

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 08.11.2023** 📆

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