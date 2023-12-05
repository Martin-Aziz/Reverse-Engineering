# Assignment: Executable mit Hex-Editor patchen (password_check_5)



In diesem Assignment werden Sie eine ausführbare Datei (Executable) untersuchen und danach so patchen, dass das Flag ausgegeben wird. Hierzu verwenden wir `gdb` und einen Hex-Editor.


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

Die folgende Datei gibt das Flag nicht aus, auch wenn Sie das richtige Passwort eingeben. Es ergibt also keinen Sinn, das Passwort aus der Datei extrahieren zu wollen.

  * [password_check_5](password_check_5)

Für diese Übung werden wir wieder den Kommandozeilendebugger `gdb` einsetzen und die Datei danach mit dem Werkzeug `hexedit` patchen.

Gehen Sie wie folgt vor:

  * Benutzen Sie den Debugger `gdb`, um im Programm die Stelle zu finden, die den Sprung ausführt, wenn das Passwort nicht richtig eingegeben wurde.
  * Benutzen Sie `gdb`, um sich die Byte-Sequenz der Instruktionen ausgeben zu lassen (Tipp: Verwenden Sie `disassemble /r`, um zusätzlich zu den Instruktionen die Bytes angezeigt zu bekommen). Merken Sie sich sicherheitshalber eine längere Byte-Sequenz (z.B. 4 Byte), um nicht aus Versehen die falsche Stelle zu patchen. Merken Sie sich auch, welche Bytes aus der Sequenz zum Sprung gehören.
  * Öffnen Sie das Executable danach mit `hexedit` und suchen Sie nach der Byte-Sequenz mithilfe der Suchfunktion (CTRL-S).
  * Ersetzen Sie die Bytes der Instruktion durch `nop` Opcodes, indem Sie den Hex-Wert `0x90` an die entsprechende Stelle schreiben.
  * Speichern Sie die Datei mit F2.
  * Führen Sie das gepatchte Programm aus und geben Sie ein beliebiges Passwort ein.


## Flags sammeln

Wenn Sie das Flag erhalten haben, so tragen Sie das Flag bitte auf der [CTF-Webseite](http://tank.informatik.hs-mannheim.de) ein. Bei der ersten Benutzung legt sich jedes Team einen Benutzer an, der wie das Team heißt.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.