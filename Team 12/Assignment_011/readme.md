# Assignment: Eingebettete Files (unknown_3)

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 22.10.2023** 📆

In diesem Assignment werden Sie ein Programm unbekannter Herkunft analysieren.

In Executables (und anderen Dateiformaten) können sich weitere Dateien verstecken, die zur Laufzeit extrahiert und verwendet werden. Insbesondere Malware macht hiervon häufig Gebrauch, um Werkzeuge zu transportieren, die dann auf dem Zielsystem ausgepackt oder installiert werden.


## Hinweis

Bei dem Executable handelt es sich um ein Programm unbekannter Funktionalität, wie man sie z.B. bei der Untersuchung von kompromittierten Rechner finden könnte. Es kann gut sein, dass es sich um eine _Malware_ handelt, welche bei der Ausführung Schaden verursacht, bis hin zur Zerstörung aller Daten auf dem Rechner. Deswegen sollten Sie die Datei __auf keinen Fall__ ohne Schutzmaßnahmen (virtuelle Maschine etc.) __ausführen__. Die hier vorgenommene Analyse kommt ohne Ausführung der Datei aus und ist insofern sicher auch ohne Schutzmaßnahmen durchführbar.

Sie müssen in der Realität damit rechnen, dass die Malware Schwachstellen in den von Ihnen verwendeten Werkzeugen nutzt, um bei einem Reverse-Engineering Ihren Rechner anzugreifen. Da wir uns hier in einem Übungskontext befinden, ignorieren wir dieses Problem.


## Radare 2

Für diese Übung werden wir das Kommandozeilen-Reverse-Engineering-Werkzeug Radare 2 einsetzen. Sie finden Tipps zur Installation und Verwendung in der [Kurzanleitung](../help/radare2.md).


## Binwalk

Für diese Übung werden wir das Kommandozeilen-Reverse-Engineering-Werkzeug `binwalk` einsetzen. Sie finden Tipps zur Installation und Verwendung in der [Kurzanleitung](../help/binwalk.md).

## Aufgabe

Laden Sie die folgende Datei herunter:

  * [unknown_3](unknown_3)

Das Utility `file` zeigt uns, dass es sich um ein Linux-Exectuable handelt.

```console
$ file unknown_3
unknown_3: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV),
    dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2,
    BuildID[sha1]=8c1f20df34cdcbe2c5e53e3b4105189d9acd87bd,
    for GNU/Linux 4.4.0, not stripped
```

Zur weiteren Analyse werden wir das Werkzeug `binwalk` benutzen, das speziell für die Suche nach eingebetteten Dateien gemacht ist.

Wenden Sie `binwalk`auf die Datei an.

```console
$ binwalk unknown_3
```

Die Ausgabe zeigt uns, dass
```console
DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             ELF, 64-bit LSB shared object, AMD x86-64, version 1 (SYSV)
12416         0x3080          Zlib compressed data, best compression
```

Im Executable ist also eindeutig ein mit der ZLib komprimiertes Segment vorhanden, das für uns interessant sein könnte. Dieses extrahieren Sie mithilfe von `binwalk` und der Option `-e`:

```console
$ binwalk -e unknown_3
```

`binwalk` legt ein Verzeichnis `_unknown_3.extracted` an, in dem sich die extrahierten Dateien befinden. Es packt bekannte Dateien auch direkt aus, sodass Sie sich das Entpacken sparen können. Die Dateien werden nach dem Offset benannt, an dem sie in der ursprünglichen Datei gefunden wurden.

```console
$ cd _unknown_3.extracted
$ ls -axl
-rw-r--r-- 1 thomas thomas 16176  4. Jul 12:15 3080
-rw-r--r-- 1 thomas thomas  6536  4. Jul 12:15 3080.zlib
```

Jetzt können wir das Programm `file` oder auch `binwalk` auf die extrahierte Datei anwenden.

```console
$ file 3080
3080: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV),
    dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2,
    BuildID[sha1]=0e3c77cb8f7d33fee640ee802b509da170bfe143,
    for GNU/Linux 4.4.0, not stripped

$ binwalk 3080
DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             ELF, 64-bit LSB shared object, AMD x86-64, version 1 (SYSV)
8264          0x2048          Unix path: /usr/bin/bash
```

Wir haben also ein Executable im Executable gefunden.

Analysieren Sie die Importe der Datei mit `rabin2`.

Haben Sie einen Verdacht, um was es sich hier handeln könnte?


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.