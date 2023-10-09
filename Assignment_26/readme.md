# Assignment: gdb mit gestripptem Executable



In diesem Assignment werden Sie einen Debugger einsetzen, um eine ausführbare Datei (Executable) zu untersuchen. Das Executable wurde vom Programmierer gestrippt, d.h. es enthält keine Symbole mehr, wie Sie leicht mit `nm` überprüfen können. Das Fehlen der Symbole macht das Debuggen deutlich schwerer.


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

  * [password_check_7](password_check_7)

Starten Sie den Debugger und teilen Sie ihm mit, dass Sie diese Datei analysieren wollen:

```console
$ gdb password_check_7
GNU gdb (Ubuntu 9.2-0ubuntu2) 9.2
...
(No debugging symbols found in password_check_7)
(gdb) _
```

Da das Executable gestrippt wurde, können Sie nicht einfach nach der `main`-Funktion suchen, und sich diese ansehen. Deswegen ist der beste Weg, das Programm mit `r` zu starten und dann mit CTRL-C zu unterbrechen, damit Sie mit `bt` den Stack untersuchen können.

Wenn Sie sich den Stack ansehen, werden Sie keine Main-Funktion finden. Allerdings ist das Executable zum Glück nicht statisch gelinkt, sodass Sie wenigstens die Aufrufe der Library-Funktionen, z.B. `_IO_fgets` sehen. Die Funktionen des Executables haben keine Namen und werden nur als `??` angezeigt.

Gehen Sie zu den jeweiligen `??`-Funktionen, indem Sie sie mit `frame NO` ansteuern. Der Versuch, die Funktion mit `disassemble` zu disassembliere scheitert an den fehlenden Symbolen. Sie können sich aber das Listing trotzdem ansehen, indem Sie die Adresse aus dem Backtrace nehmen und diese an `x /i` verfüttern. Mit `x /30i ADRESSE` können Sie sich z.B. die nächsten 30 Instruktionen disassemblieren lassen.

Versuchen Sie die Funktion zu finden, die letztendlich den String-Vergleich von Passwort und Eingabe macht und setzen Sie dort vor dem `strcmp` einen Breakpoint. Lassen Sie das Programm weiterlaufen, geben Sie ein beliebiges Passwort ein. Nach der Eingabe sollte das Programm auf den Breakpoint laufen und einer der Parameter von `stcmp` sollte das richtige Passwort enthalten.

Verwenden Sie die Informationen, um das Flag auszugeben.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.