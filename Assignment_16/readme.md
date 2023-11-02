# Assignment: String-Obfuscation

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 08.11.2022** 📆

In diesem Assignment werden Sie eine Datei untersuchen, die *sieben Flags* enthält, die aber alle durch String-Obfuscation vor dem direkten Zugriff geschützt sind.


## gdb

Für diese Übung werden wir den Kommandozeilendebugger `gdb` einsetzen. Sie finden Tipps zur Installation und Verwendung in der [Kurzanleitung](../help/gdb.md).

## Aufgabe

Bei der folgenden Datei versagen sowohl `strings`, als auch `rabin`.

  * [string_obfuscation](string_obfuscation)

Wir werden die Datei disasemblieren aber nicht ausführen. Trotzdem sollte es uns gelingen, die Strings zu finden und damit die Flags zu sammeln.

Starten Sie den Debugger und teilen Sie ihm mit, dass Sie diese Datei analysieren wollen:

```console
$ gdb string_obfuscation
GNU gdb (Ubuntu 12.1-3ubuntu2) 12.1
...
(No debugging symbols found in string_obfuscation)
(gdb) _
```

Starten Sie das Programm **nicht**, sondern nutzen Sie gdb nur, um die sieben Funktionen `flag_x` zu disassemblieren, z.B. für die erste Funktion:

```console
(gdb) disass *flag_1
```

Wenn Sie in den Funktionen einen Zugriff auf die (verschlüsselte) Form des Flags finden, können Sie sich den Inhalt über das entsprechende Symbol ausgeben lassen. So findet sich z.B. in `flag_2()` ein Zugriff auf das Symbol `FLAG_2`. Dieses können Sie sich mit dem Debugger ansehen:

```console
(gdb) x /s (char*) FLAG_2
0x4004:	"6<17kSQUcQbOSXYVVbUm"
```

Wenn das Symbol kein Pointer, sondern direkt das Array ist, fügen Sie einfach den Adress-Operator `&` hinzu:

```console
(gdb) x /s (char*) FLAG_3
0xeeefe4fbc7c1ccc6:	<error: Cannot access memory at address 0xeeefe4fbc7c1ccc6>
(gdb) x /10xb (char*) &FLAG_3
0x6020 <FLAG_3>:	0xc6	0xcc	0xc1	0xc7	0xfb	0xe4	0xef	0xee
0x6028 <FLAG_3+8>:	0xa7	0xf4
```


### Hinweis: Verschüsselung

In dem Programm wird auch eine XOR-Verschlüsselung benutzt. Sie können eine Known-Plaintext-Attacke auf die Verschlüsselung durchführen, wenn Sie folgende zwei Informationen verwenden:

  * Der Klartext beginnt mit `FLAG{`
  * der Schlüssel hat eine Länge von vier Zeichen

Mit diesen Informationen können Sie den Schlüssel ganz einfach gewinnen und den gesamten Text entschlüsseln.


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.