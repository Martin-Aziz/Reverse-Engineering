# Assignment: Eigenes Crackme schreiben

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 08.01.2024** 📆

Nachdem Sie jetzt viele Erfahrungen im Reverse Engineering gewonnen haben, sollen Sie in diesem Assignment ein eigenes _Crackme_ erstellen. Dieses wird dann im nächsten Schritt von anderen Teams geknackt werden.

## Aufgabe

Schreiben Sie ein Crackme, das von anderen Teams durch Reverse Engineering gelöst werden kann. Das Crackme sollte ein Flag enthalten und dieses nur ausgeben, wenn man eine Schwachstelle in Ihrem Programm erfolgreich ausnutzt. Das Format des Flags ist `FLAG{geheimer_text}`. Bitte achten Sie darauf, dass das Format **genau so ist** und nicht anders; beachten Sie insbesondere Groß- und Kleinschreibung.

Das andere Team darf Ihr Programm debuggen und mit beliebigen Tools reverse engineeren. Die Ausgabe des Flag muss aber letztendlich durch entsprechende Eingaben provoziert werden, welche eine Sicherheitslücke oder einen Logikfehler ausnutzen. Orientieren Sie sich an den Crackmes, die Sie bereits im Rahmen der Vorlesung gelöst haben oder an anderen Crackmes, die Sie im Internet finden können.

Die Wahl der Sicherheitslücke ist Ihnen überlassen. Sie sollten das Crackme allerdings so gestalten, dass es von einem anderen Team auch gelöst werden kann aber auch nicht trivial ist.

Wenn man Ihr Crackme mit der Compileroption `-Wall` compiliert, dürfen **keine Warnungen ausgegeben werden**. Falls die von Ihnen verwendete Sicherheitslücke ebenfalls vom Compiler angemeckert wird und deshalb nicht aus dem Programm entfernt werden kann, unterdrücken Sie die Warnung mit einem passenden `#pragma`-Eintrag im Quelltext. So würde z.B. der Eintrag `#pragma GCC diagnostic ignored "-Wunused-variable"` eine Warnung zu einer ungenutzten Variable unterdrücken.

Ein paar Tipps zu Sicherheitslücken finden Sie [hier](../help/sicherheitsluecken.md)

Beachten Sie, dass die **Crackmes noch einmal neu** unter einer älteren Linux-Version **compiliert werden**, bevor sie an die anderen Gruppen herausgegeben werden. Deswegen sollten Sie in den Aufgaben keine Annahmen über die erzeugten Adressen im Executable machen.

### Optional: Crackme für Remote-Zugriff

Wenn Sie Ihr Crackme auf dem Server laufen lassen möchten, sodass das Flag nicht direkt aus dem Executable extrahiert werden kann, gehen Sie wie folgt vor:

  * Die Programme auf dem Server verwenden die Standard-Eingabe und -Ausgabe. Deswegen können Sie die normalen C-Funktionen (`printf`, `read`, `puts`, `write` etc.) benutzen.
  * Geben Sie in der `win()`-Funktion das Flag aus der Datei `flag` mit `system("cat flag");` aus.
  * Verwenden Sie die folgende `setup()`-Funktion, um den Prozess nach 60 Sekunden zu beenden und die Eingabepufferung auszuschalten:

```c
#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

static void alarmHandler(int signal) {
    exit(1);
}

void setup(void) {
    setvbuf(stdout, (char*)0, _IONBF, 0);
    setvbuf(stdin,  (char*)0, _IONBF, 0);
    signal(0xe, alarmHandler);
    alarm(0x3c);
}
```

Wenn Sie Ihr Programm als Netzwerkdienst z.B. auf Port `3090` lokal testen wollen, können Sie (unter Bash) folgendes tun:

```console
$ mkfifo /tmp/2way
$ nc -l 3090 0</tmp/2way| ./crackme 1>/tmp/2way &
$ rm -f /tmp/2way
```

Jetzt läuft das Programm als Netzwerkdienst auf Port `3090` und Sie können sich mit `nc localhost 3090` damit verbinden.

Wenn Sie fertig sind, können Sie aufräumen:

```console
$ killall -9 crackme
$ killall -9 nc
$ rm -f /tmp/2way
```

## Abgabe

Ihre Abgabe besteht aus:

  * Dem kommentierten Quelltext des Crackmes in C. Alle Warnings, die Sie nicht entfernen konnten, sind unterdrückt.
  * Einem Makefile mit dem Namen `Makefile`, um das Crackme bauen zu können mit den passenden Compileroptionen, einschließlich `-Wall`. Das Executable, das erzeugt wird heißt `crackme`.
  * Eine Datei `flag`, welche nur das Flag enthält.
  * Ein fertig compiliertes Executable des Crackmes.
  * Einer Musterlösung für das Crackme
    - Textuelle Beschreibung der Schwachstelle und des Angriffs
    - Skript, das die Schwachstelle ausnutzt und das Flag ausgibt

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.