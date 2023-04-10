# Assignment: gdb mit gestripptem Executable, statisch gelinkt

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 06.12.2022** 📆

In diesem Assignment werden Sie einen Debugger einsetzen, um eine ausführbare Datei (Executable) zu untersuchen. Das Executable wurde vom Programmierer gestrippt, d.h. es enthält keine Symbole mehr, wie Sie leicht mit `nm` überprüfen können. Das Fehlen der Symbole macht das Debuggen deutlich schwerer. Außerdem wurde das Executable auch noch statisch gelinkt, sodass auch für die Funktionen der Bibliotheken keine Namen mehr vorhanden sind.


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

  * [password_check_9](password_check_9)

Starten Sie den Debugger und teilen Sie ihm mit, dass Sie diese Datei analysieren wollen:

```console
$ gdb password_check_9
GNU gdb (Ubuntu 9.2-0ubuntu2) 9.2
...
(No debugging symbols found in password_check_9)
(gdb) _
```

Da das Executable gestripp wurde, können Sie nicht einfach nach der `main`-Funktion suchen, und sich diese ansehen. Deswegen ist der beste Weg, das Programm mit `r` zu starten und dann mit CTRL-C zu unterbrechen, damit Sie mit `bt` den Stack untersuchen können.

Wenn Sie sich den Stack mit `bt` ansehen, werden Sie keine Main-Funktion finden. Außerdem ist das Executable statisch gelinkt, sodass Sie auch die Aufrufe der Library-Funkionen nicht mehr zu erkennen sind. Der Backtrace sieht deswegen ungefähr wie folgt aus:

```console
#0  0x000000000044ae42 in ?? ()
#1  0x0000000000415104 in ?? ()
#2  0x00000000004189c7 in ?? ()
#3  0x00000000004123fc in ?? ()
#4  0x000000000041200a in ?? ()
#5  0x00000000004022ee in ?? ()
#6  0x000000000040207b in ?? ()
#7  0x0000000000402dc4 in ?? ()
#8  0x0000000000401f3e in ?? ()
```

Irgendwo auf dem Stack verbirgt sich die `main`-Funktion und die Stelle, an der das Passwort entschlüsselt wird. Die Adressen im Backtrace sind jeweils die Instruktionen __nach__ der `call`-Instruktion. Wir können also einen Breakpoint an den Adressen setzen und das Programm unterbricht, bei der Rückkehr.

Gehen Sie wie folgt vor:

  * Setzen Sie von der untersten Adresse beginnend jeweils einen Breakpoint mit `break *ADRESSE` und lassen Sie das Programm weiterlaufen. Geben Sie ein beliebiges Passwort ein.
  * Wenn sich das Programm beendet, ohne auf den Breakpoint gelaufen zu sein, starten Sie das Programm neu, setzen den Breakpoint dann einen Stack-Frame weiter oben.
  * Wenn das Programm auf den Breakpoint läuft, sollten Sie sich in den `main`-Funktion befinden.
  * Disassemblieren Sie das Programm ab der aktuellen Adresse. Hierzu können Sie den Programm-Counter (Register `rip`) verwenden, also z.B. `x /10i $rip`.
  * Gehen Sie das Programm schrittweise mit `nexti` und `stepi` durch und schauen Sie sich die Eingabe und Ausgabe-Daten der gerufenen Funktionen an. `stepi` geht in die gerufenen Funktionen hinein, `nexti` überspringt sie. Irgendwo muss sich das verschlüsselte Passwort verstecken.
  * Wenn Sie das Passwort gefunden haben, benutzen Sie dieses, um das Flag auszugeben.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.