# Assignment 31: Eigenes Crackme schreiben

In dieser Aufgabe wird ein Executable erstellt, welches eine Formatstring-Schwachstelle hat.
Der Quellcode ist in der Datei [crackme.c](crackme.c) zufinden und kann über das [Makefile](Makefile) kompiliert werden.

## Schwachstelle

Das Crackme nutzt `printf`, um Ausgaben auf die Konsole zu drucken und erfordert ebenfalls eine Nutzereingabe, um diese Eingabe wieder auszugeben.
Dabei wird der Funktion `printf` lediglich die Variable des Puffers mit der Eingabe als einziger Parameter übergeben.
Die Funktion `printf` nimmt als ersten Parameter einen _Format String_ an und eine beliebige Anzahl an weiteren Parametern, die der Reihe nach als Eingabewerte für die im _Format String_ spezifizierten Formatkonversionen benutzt werden.
Werden der Funktion `printf` nicht genügend Parameter übergeben, um alle Konversionen zu bedienen, so werden diese fehlenden Parameter der Reihe nach vom Stack genommen.

Mit dieser Methode lassen sich Daten vom Stack auslesen.
Die Formatkonversion von `printf` kennt verschiedene Konversionsspezifikatoren, von denen `%n` die Möglichkeit bietet, die Anzahl der bis zu diesem Zeitpunkt durch `printf` gedruckten Zeichen in die übergebene Variable zu schreiben.
Dadurch erhält man die Möglichkeit bei Kontrolle über den _Format String_ Zahlenwerte auf den Stack zu schreiben.

## Musterlösung

Zunächst wird festgestellt, ob die Funktion `printf` im Programm verwendet wird.
Hierzu kann man sich mit `rabin2` die Imports des Executables anzeigen lassen:

```text
$ rabin2 -i crackme
[Imports]
nth vaddr      bind   type   lib name
―――――――――――――――――――――――――――――――――――――
1   0x00000000 WEAK   NOTYPE     _ITM_deregisterTMCloneTable
2   0x00001030 GLOBAL FUNC       puts
3   0x00001040 GLOBAL FUNC       strlen
4   0x00001050 GLOBAL FUNC       printf
5   0x00000000 GLOBAL FUNC       __libc_start_main
6   0x00001060 GLOBAL FUNC       fgets
7   0x00000000 WEAK   NOTYPE     __gmon_start__
8   0x00001070 GLOBAL FUNC       exit
9   0x00000000 WEAK   NOTYPE     _ITM_registerTMCloneTable
10  0x00001080 WEAK   FUNC       __cxa_finalize
```

Tatsächlich wird die Funktion importiert.
Mittels Ghidra kann man sich die Disassembly und auch eine Variante des dekompilierten C Codes ansehen:

```c
void main(void)

{
  char local_118 [256];
  long local_18;
  long *local_10;
  
  local_18 = 1;
  local_10 = &local_18;
  printf("Please enter your name: ");
  fgets(local_118,0xfe,stdin);
  printf("Hello ");
  printf(local_118);
  if (local_18 != 1) {
    printflag();
    exit(0);
  }
  exit(1);
}
```

Hier fällt auf, dass `printf` beim zweiten Mal nur mit einer Variable als einzigen Parameter aufgerufen wird.
Dieselbe Varible wird zuvor genutzt, um eine Nutzereingabe zu speichern.
Zusätzlich fällt auf, dass die vermeintliche Funktion zum Ausgeben der Flag erst aufgerufen wird, wenn der Wert einer Variable verändert wird, deren Pointer in einer anderen Variable auf dem Stack gespeichert und sonst nicht verwendet wird.

Bei der Ausführung des Programms kann nun durch Eingabe eines Formatstrings getestet werden, ob die Eingabe tatsächlich verwundbar ist:

```text
$ ./crackme 
Please enter your name: Tom
Hello Tom

$ ./crackme
Please enter your name: %p
Hello 0x6c6c6548
```

In diesem Beispiel wird der Konversionsspezifikator für Pointer verwendet, da dieser mit hoher Wahrscheinlichkeit keinen Programmabsturz herbeiführt.

Aus dem Decompile ist bekannt, dass später auf eine Variable geprüft wird, die den Wert 1 hat und deren Pointer auf dem Stack liegt.
Um deren Position zu finden, wird mit `python3 -c "print('%p '*40)"` zunächst eine Eingabe erzeugt, die an jeder Stelle den Pointer an der Position ausgibt und die Ausgabe auf mögliche Addressen des Stacks überprüft:

```text
$ python3 -c "print('%p '*40)"
%p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p 

$ ./crackme 
Please enter your name: %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p %p
Hello 0x6c6c6548 (nil) (nil) 0x7ffcd9160670 0x6 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0x2070252070252070 0x7025207025207025 0x2520702520702520 0xa70252070252070 (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) (nil) 0x4000000 0x55817a094040 0x55817a095305 (nil) (nil) 0x55817a0952c0 0x55817a095090 0x1 0x7ffcd9160770 0x55817a0952c0
```

Da der Stack im Adressraum von oben nach unten wächst, sind Adressen mit hohem Wert von Interesse.
Diese sind in diesem Beispiel 4 und 39.

Um nun an diesen Positionen den Wert zu verändern, wird der Konversionsspezifikator `%n` verwendet, der die Anzahl der durch `printf` ausgegebenen Zeichen in die Variable schreibt.
Die Position kann im Format dem Konversionsspezifikator durch ein `$` separiert vorangestellt werden: `%4$n`.

Durch Ausprobieren beider Positionen kann nun der Wert an der Position überschrieben werden und die Flag wird beim Überschreiben der korrekten Variable ausgegeben:

```text
$ ./crackme 
Please enter your name: %4$n
Hello 

$ ./crackme 
Please enter your name: %39$n
Hello 
FLAG{LuLGotEm}
```

Die Eingabe von `%39$n` für verschiedene Positionen ist im Python-Skript [autocrack.py](autocrack.py) automatisiert.
