# Assignment 31

| Matrikelnummer | Name |
| -------- | -------- |
| 1921637 | Tim Philipp |
| 1920769 | Christian Höfig |
| 1925165 | Tobias Nöth |

Die gesuchte Flag lautet **FLAG{int3gr_0v3rfl0w}**.

## Beschreibung der Schwachstelle

In diesem Programm muss der Benutzer eine bestimmte Zahl eingeben, um die Flag zu erhalten. Diese sogenannte *Magic Number* kann zwar aus dem Programm extrahiert werden, aber die direkte Eingabe ist nicht die Lösung des Rätsels. Stattdessen manipuliert das Programm die Eingabe des Benutzers, indem es nicht die übliche `read`-Funktion aus der `stdio.h`-Bibliothek verwendet, sondern eine eigene, selbst implementierte `read`-Funktion.
Um die richtige Magic Number an das Programm zu übergeben, muss eine fehlerhafte Typenkonversion ausgenutzt werden, die zu einem *Integer Overflow* führt.
Die tatsächliche Funktionsweise des Programms wurde verschleiert, indem ein irrelevantes Klartext-Passwort in den Quellcode eingefügt und eine Attrappe der `win`-Funktion implementiert wurde. Die eigentliche Funktion, die durch ihren Aufruf die Flag ausgibt, heißt `__magic` und ist innerhalb der benutzerdefinierten `read`-Funktion versteckt.

## Quellcode

```c
#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Verschlüsselte Flag
#define FLAG "\x19\x13\x32\x33\x1a\x0a\x05\x2b\x50\x0f\x19\x00\x56\x17\x5a\x1e\x39\x33\x43\x03\x1c"

// Globale Variable für die Magic Number
int magic_number;

// Fake win-Funktion, um Verwirrung zu stiften
void win() {
    printf("It's not THAT easy dummy!\n");
}

// Funktion zur XOR-Entschlüsselung der Flag
void xor_crypt(char* buffer, char* flag, size_t flag_len, char* key, size_t key_len) {
    for (int i = 0; i < flag_len; i++) {
        buffer[i] = flag[i] ^ key[i % key_len];
    }
}

// "Geheime" Funktion, welche die Flag ausgibt
void __magic() {
    char *buf = (char*)malloc(22);
    xor_crypt(buf, FLAG, 21, "__stack_chk_fail", 16);
    buf[21] = '\x00';
    puts(buf);
    free(buf);
}

// Eigene read-Funktion zum Verschleiern
ssize_t read(int fd, char *buf, size_t count) {
    char *buf2 = NULL;

    // Zeile von der Standardeingabe einlesen
    ssize_t size = getline(&buf2, &count, stdin);

    // Zeile in den usrprünglichen Puffer kopieren, damit sie in main verfügbar ist
    strcpy(buf, buf2);

    // Zeile in long konvertieren
    char *ptr;
    long number = strtol(buf, &ptr, 10);

    // User auf Overflow hinweisen
    if (number == (long)magic_number) {
        puts("Think bigger ＼（〇_ｏ）／");
        return size;
    }

    // Überprüfen, ob nach Overflow die Zahl der magic number entspricht
    if ((unsigned int)number == magic_number) {
        // 4294967295 + magic_number + 1
        __magic();
    }

    return size;
}

int main() {

    // Magic Number zwischen 10000 und 60000 generieren
    srand(time(NULL));
    magic_number = (rand() % 50000) + 10000;

    printf("Your magic number is %d\n", magic_number);
    puts("Please enter the passphrase: ");

    char buf[255];
    ssize_t len = read(1, buf, 255);

    // Vergleichen der eingelesene Zeile mit der Passphrase
    int cmp = strcmp(buf, "15islucky\n");
    if (cmp == 0) {
        // Wenn die Zeile der Passphrase entspricht, wird die (fake) win-Funktion aufgerufen
        win();
    }

    return 0;
}
```

## Angriff

1. Beim Dekompilieren der Anwendung sollten dem Angreifer beim Überfliegen der Imports keine Besonderheiten auffallen. Beim anschließenden Blick auf die `main` könnten dem Angreifer das Klartextpasswort `15islucky` und die anschließende `win`-Funktion auffallen. Die Eingabe des Klartextpasswortes wird hier jedoch nicht zur Flag führen. 
2. Danach sollte der Angreifer die Funktionen, bzw. Imports genauer untersuchen. Unter den internen Funktionen/Bibliotheken sollte nun die `__magic`-Funktion auffallen, da sich diese durch ihren untypischen Namen abhebt. Eine genauere Analyse der `__magic`-Funktion, gibt Aufschluss darüber, dass diese durch einen Aufruf wohl zur gesuchten Flag führt.
3. Da die `main` über wenige Funktionsaufrufe verfügt könnte auch die `read`-Funktion genauer unter die Lupe genommen werden. Aus der Analyse der `read`-Funktion sollte klar werden, dass diese selbst geschrieben wurde und nicht aus `stdio.h` importiert wurde. 
4. Bei der Eingabe der Magic Number gibt die `read`-Funktion einen Tipp aus, da die Magic Number als Input noch nicht korrekt ist. Die Magic Number muss also über einen anderen Weg übergeben werden, damit der Check, welcher das Aufrufen von `__magic` verhindert umgangen werden kann und somit die Flag ausgegeben wird.
5. An dieser Stelle sollte die Typenkonversion der Eingabe von `long` zu `unsigned int` ins Auge fallen, welche auf einen *Integer Overflow* hindeutet. Wenn der Angreifer nun den maximalen Unsigned-Integer-Wert (4294967295) um 1 erhöht und dann die Magic Number dazuzählt und das als Eingabe verwendet, wird die Flag ausgegeben. Die Flag liegt zu diesem Zeitpunkt noch verschlüsselt vor und wird dann automatisch mit der selbst geschriebenen `xor_crypt`-Funktion entschlüsselt. Der Schlüssel für diese Entschlüsselung ist `__stack_chk_fail`, welcher nicht auffallen wird, wenn der Angreifer die verfügbaren Funktionen und Imports untersucht. Sobald die Flag entschlüsselt wurde, wird sie ausgegeben.
