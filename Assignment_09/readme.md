# Reverse Engineering (Wintersemester 2022/2023)

## Willkommen zum Kurs Reverse Engineering (REE)

In diesem Kurs erfahren Sie, wie man einem unbekannten Binärartefakt (Programm, Virus, Payload) seine Geheimnisse entlocken kann. Hierzu werden Sie grundlegende Techniken der Analyse solcher Programme erlernen und diese Techniken verwenden, um deren Funktionsweise zu verstehen und Schwachstellen zu finden. Am Ende des Kurses werden Sie in der Lage sein, einfache CTFs (Capture The Flag) aus dem Bereich des Reverse Engineerings zu lösen und eigene kleinere Aufgaben für Ihre Mitstudierenden zu entwickeln, die diese dann lösen müssen.


## Assignments

Hier finden Sie die wöchentlichen Assignments für die Vorlesung Reverse Engineering (RE). Die Assignments sind unten, zusammen mit dem Fälligkeitsdatum, aufgelistet.

Einige dieser Assignments sind _benotet_, d.h. die Qualität Ihrer Ausarbeitung geht in die Gesamtnote für diesen Kurs ein. Sie erkennen die _benoteten Assignments an dem Abgabedatum_, bis zu dem Ihre Lösung hochgeladen sein muss.

Hinweise zur nötigen Softwareausstattung finden Sie [hier](help/software.md).

| #  | Ausgabe    | Thema                                                                                   | Fällig am 📆   |
|----|------------|-----------------------------------------------------------------------------------------|----------------|
| 1. | 05.10.2022 | [Java-Klasse analysieren und patchen](Assignment_01/readme.md)                          |                |
| 2. | 05.10.2022 | [Dateien mit `file` untersuchen](Assignment_02/readme.md)                               |                |
| 3. | 12.10.2022 | [Speicherlayout eines Prozesses](Assignment_03/readme.md)                               |                |
| 4. | 12.10.2022 | [Importe mit rabin2 untersuchen](Assignment_04/readme.md)                               | **18.10.2022** |
| 5. | 12.10.2022 | [Exports und Imports mit rabin2 untersuchen](Assignment_05/readme.md)                   | **18.10.2022** |
| 6. | 19.10.2022 | [Flag mit strings extrahieren](Assignment_06/readme.md)                                 |                |
| 7. | 19.10.2022 | [Einen Hexeditor verwenden, um Strings zu finden](Assignment_07/readme.md)              |                |
| 8. | 19.10.2022 | [Strings mit rabin2 extrahieren](Assignment_08/readme.md)                               |                |
| 9. | 19.10.2022 | [Core Dump erstellen und mit strings analysieren](Assignment_09/readme.md)              | **25.10.2022** |
| 10. | 26.10.2022 | [Disassemblieren mit Radare 2](Assignment_10/readme.md)                                 |                |
| 11. | 26.10.2022 | [Executable mit Hex-Editor patchen](Assignment_11/readme.md)                            |                |
| 12. | 26.10.2022 | [Executable mit radare2 patchen](Assignment_12/readme.md)                               |                |
| 13. | 26.10.2022 | [gdb](Assignment_13/readme.md)                                                          | **01.11.2022** |
| 14. | 02.11.2022 | [Disassemblieren einer Payload](Assignment_14/readme.md)                                |                |
| 15. | 02.11.2022 | [Disassemblieren einer Payload (obfuscated)](Assignment_15/readme.md)                   |                |
| 16. | 02.11.2022 | [String-Obfuscation](Assignment_16/readme.md)                                           | **08.11.2022** |
| 17. | 09.11.2022 | [Schwachstelle finden und ausnutzen](Assignment_17/readme.md)                           |                |
| 18. | 09.11.2022 | [Schwachstelle finden und ausnutzen](Assignment_18/readme.md)                           |                |
| 19. | 16.11.2022 | [Schwachstelle finden und ausnutzen](Assignment_19/readme.md)                           |                |
| 20. | 16.11.2022 | [Roundtrip mit Ghidra (einfaches C-Programm)](Assignment_20/readme.md)                  |                |
| 21. | 16.11.2022 | [Executable mit Ghidra analysieren (license_check)](Assignment_21/readme.md)            | **22.11.2022** |
| 22. | 23.11.2022 | [Roundtrip mit Ghidra (C-Programm mit struct)](Assignment_22/readme.md)                 |                |
| 23. | 23.11.2022 | [Roundtrip mit Ghidra (C++ Programm)](Assignment_23/readme.md)                          |                |
| 24. | 23.11.2022 | [Executable mit Ghidra analysieren (password_check_11)](Assignment_24/readme.md)        | **29.11.2022** |
| 25. | 30.11.2022 | [Disassemblieren eines unbekannten Programms (verschlüsselt)](Assignment_25/readme.md)  |                |
| 26. | 30.11.2022 | [gdb mit gestripptem Executable](Assignment_26/readme.md)                               |                |
| 27. | 30.10.2022 | [gdb mit gestripptem Executable, statisch gelinkt](Assignment_27/readme.md)             | **06.12.2022** |
| 28. | 07.12.2022 | [Executable mit Ghidra analysieren (pwnable 21)](Assignment_28/readme.md)               |                |
| 29. | 14.12.2022 | [Executable mit Ghidra analysieren (pwnable 22)](Assignment_29/readme.md)               |                |
| 30. | 14.12.2022 | [Executable mit Ghidra analysieren (pwnable 23)](Assignment_30/readme.md)               |                |
| 31. | 14.12.2022 | [Eigenes Crackme schreiben](Assignment_31/readme.md)                                    | **08.01.2023** |
| 32. | 11.01.2023 | [Crackme-Wettbewerb](Assignment_32/readme.md)                                           | **17.01.2023** |

## Benotung

Die Benotung des Kurses erfolgt im Format Continuous Assessment (CA). Hierzu werden Ihre Leistungen während des gesamten Semesters bewertet und die Endnote ergibt sich aus den Einzelleistungen.

Bewertet werden:

  * die erstellten Writeups und Lösungen zu den Assignments
  * die Erstellung neuer Aufgaben/CTFs durch die Teams (Peer-Aufgaben)
  * die Lösung der Peer-Aufgaben/CTFs durch die Teams

Alle mit einem Abgabedatum gekennzeichneten Assignments sind Teil der Bewertung und müssen von Ihnen bearbeitet und fristgerecht abgegeben werden.


## Hilfreiche Links und Tipps

  * [Typische Sicherheitslücken](help/sicherheitsluecken.md)
  * [Compiler Explorer](https://godbolt.org/)
  * [x86 and amd64 instruction reference](https://www.felixcloutier.com/x86/index.html)
  * [System V AMD64 ABI Calling Convention](https://en.wikipedia.org/wiki/X86_calling_conventions#System_V_AMD64_ABI)
    1. RDI <- 1st param (left to right)
    2. RSI <- 2nd param (left to right)
    3. RDX <- 3rd param (left to right)
    4. RCX <- 4th param (left to right)
    5. R8 <- 5th param (left to right)
    6. R9 <- 6th param (left to right)
    * Stack <- excess params (right to left)
    * RAX -> result
  * [Linux System Call Table for x86 64](http://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/)
  * [Linux System Call Convention](https://en.wikibooks.org/wiki/X86_Assembly/Interfacing_with_Linux)
    * RAX <- System call number
    1. RDI <- 1st param (left to right)
    2. RSI <- 2nd param (left to right)
    3. RDX <- 3rd param (left to right)
    4. R10 <- 4th param (left to right)
    5. R8 <- 5th param (left to right)
    6. R9 <- 6th param (left to right)
    * RAX -> result
  * [printf Formatierungszeichen](http://www2.hs-esslingen.de/~zomotor/home.fhtw-berlin.de/junghans/cref/FUNCTIONS/format.html)
  * [gdb Cheat Sheet](https://users.ece.utexas.edu/~adnan/gdb-refcard.pdf)


## Literatur zur Vorlesung

  * Sikorski, M. and Honig, A. (2012). Practical Malware Analysis: The Hands-On Guide to Dissecting Malicious Software. No Starch Press.
  * Andriesse, D. (2018). Practical Binary Analysis: Build Your Own Linux Tools for Binary Instrumentation, Analysis, and Disassembly. No Starch Press.
  * Eagle C. and Nance K. (2020). The Ghidra Book: The Definitive Guide. No Starch Press.
  * Yurichev, D. (2019). Reverse Engineering for Beginners. [Online](https://beginners.re/main.html)
  * [x86-64 Assembly Language Programming with Ubuntu](http://www.egr.unlv.edu/~ed/assembly64.pdf)
  * [Intel Dokumentation zu x86-64](https://software.intel.com/content/www/us/en/develop/articles/intel-sdm.html)
  * [System V ABI](https://raw.githubusercontent.com/wiki/hjl-tools/x86-psABI/x86-64-psABI-1.0.pdf)
