## Eingebettete Files (unknown_3) analysieren
unknown_3 datei 
```console
file unknown_3
unknown_3: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=53758a9504157139e38c64815f6edc474dda6ca2, not stripped

```
unknown_3 mit binwalk untersuchen
```console
binwalk unknown_3

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             ELF, 64-bit LSB shared object, AMD x86-64, version 1 (SYSV)
4128          0x1020          Zlib compressed data, default compression
``` 
unknown_3 datei extrahieren
```console
binwalk --run-as=root -e unknown_3
ls
1020  1020.zlib

```
file oder auch binwalk auf die extrahierte Datei anwenden.
```console
file 1020
1020: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, BuildID[sha1]=dba8dfd0549319f1f7eb206cc921d262d8e74647, not stripped


binwalk 1020

DECIMAL       HEXADECIMAL     DESCRIPTION
--------------------------------------------------------------------------------
0             0x0             ELF, 64-bit LSB shared object, AMD x86-64, version 1 (SYSV)
3480          0xD98           Unix path: /usr/bin/bash

```


1020 datei  Imports untersuchen 
```console
 rabin2 -i 1020
[Imports]
nth vaddr      bind   type   lib name
―――――――――――――――――――――――――――――――――――――
1   ---------- WEAK   NOTYPE     _ITM_deregisterTMCloneTable
2   0x00000850 GLOBAL FUNC       setsockopt
3   0x00000860 GLOBAL FUNC       chdir
4   0x00000870 GLOBAL FUNC       __stack_chk_fail
5   0x00000880 GLOBAL FUNC       htons
6   0x00000890 GLOBAL FUNC       dup
7   0x000008a0 GLOBAL FUNC       memset
8   0x000008b0 GLOBAL FUNC       close
9   ---------- GLOBAL FUNC       __libc_start_main
10  ---------- WEAK   NOTYPE     __gmon_start__
11  0x000008c0 GLOBAL FUNC       listen
12  0x000008d0 GLOBAL FUNC       bind
13  0x000008e0 GLOBAL FUNC       perror
14  0x000008f0 GLOBAL FUNC       accept
15  0x00000900 GLOBAL FUNC       exit
16  ---------- WEAK   NOTYPE     _ITM_registerTMCloneTable
17  0x00000910 GLOBAL FUNC       execl
18  0x00000940 WEAK   FUNC       __cxa_finalize
19  0x00000920 GLOBAL FUNC       fork
20  0x00000930 GLOBAL FUNC       socket

```
Exports ausgeben
```console
rabin2 -E 1020
[Exports]
nth paddr      vaddr      bind   type   size lib name            demangled
――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
43  0x00000d40 0x00000d40 GLOBAL FUNC   2        __libc_csu_fini
47  ---------- 0x00202010 GLOBAL NOTYPE 0        _edata
48  0x00000d44 0x00000d44 GLOBAL FUNC   0        _fini
56  0x00002000 0x00202000 GLOBAL NOTYPE 0        __data_start
58  0x00002008 0x00202008 GLOBAL OBJ    0        __dso_handle
59  0x00000d50 0x00000d50 GLOBAL OBJ    4        _IO_stdin_used
60  0x00000cd0 0x00000cd0 GLOBAL FUNC   101      __libc_csu_init
61  0x00000a5a 0x00000a5a GLOBAL FUNC   586      server
63  ---------- 0x00202018 GLOBAL NOTYPE 0        _end
64  0x00000950 0x00000950 GLOBAL FUNC   43       _start
65  ---------- 0x00202010 GLOBAL NOTYPE 0        __bss_start
66  0x00000ca4 0x00000ca4 GLOBAL FUNC   44       main
71  ---------- 0x00202010 GLOBAL OBJ    0        __TMC_END__
75  0x00000828 0x00000828 GLOBAL FUNC   0        _init
```
Verwendete Libraries ausgeben
```console
rabin2 -l 1020
[Linked libraries]
libc.so.6

1 library

```
Strings in der .data-Section ausgeben
```console
 rabin2 -z 1020
[Strings]
nth paddr      vaddr      len size section type  string
―――――――――――――――――――――――――――――――――――――――――――――――――――――――
0   0x00000d54 0x00000d54 13  14   .rodata ascii socket failed
1   0x00000d62 0x00000d62 17  18   .rodata ascii setsockopt failed
2   0x00000d74 0x00000d74 11  12   .rodata ascii bind failed
3   0x00000d80 0x00000d80 13  14   .rodata ascii listen failed
4   0x00000d93 0x00000d93 4   5    .rodata ascii bash
5   0x00000d98 0x00000d98 13  14   .rodata ascii /usr/bin/bash
6   0x00000da6 0x00000da6 12  13   .rodata ascii execl failed
```
Strings aus allen Sektionen ausgeben
```console
 -zzz 1020
000 0x00000034 0x00000034   4  10 () utf16le @8\t@
001 0x00000238 0x00000238  27  28 (.interp) ascii /lib64/ld-linux-x86-64.so.2
002 0x000004b1 0x000004b1   9  10 (.dynstr) ascii libc.so.6
003 0x000004bb 0x000004bb   6   7 (.dynstr) ascii socket
004 0x000004c2 0x000004c2   4   5 (.dynstr) ascii exit
005 0x000004c7 0x000004c7   5   6 (.dynstr) ascii execl
006 0x000004cd 0x000004cd   5   6 (.dynstr) ascii htons
007 0x000004d3 0x000004d3   6   7 (.dynstr) ascii perror
008 0x000004da 0x000004da   4   5 (.dynstr) ascii fork
009 0x000004df 0x000004df  16  17 (.dynstr) ascii __stack_chk_fail
010 0x000004f0 0x000004f0   6   7 (.dynstr) ascii listen
011 0x000004f7 0x000004f7   6   7 (.dynstr) ascii memset
012 0x000004fe 0x000004fe   4   5 (.dynstr) ascii bind
013 0x00000503 0x00000503   5   6 (.dynstr) ascii chdir
014 0x00000509 0x00000509  10  11 (.dynstr) ascii setsockopt
015 0x00000518 0x00000518   5   6 (.dynstr) ascii close
016 0x0000051e 0x0000051e   6   7 (.dynstr) ascii accept
017 0x00000525 0x00000525  14  15 (.dynstr) ascii __cxa_finalize
018 0x00000534 0x00000534  17  18 (.dynstr) ascii __libc_start_main
019 0x00000546 0x00000546   9  10 (.dynstr) ascii GLIBC_2.4
020 0x00000550 0x00000550  11  12 (.dynstr) ascii GLIBC_2.2.5
021 0x0000055c 0x0000055c  27  28 (.dynstr) ascii _ITM_deregisterTMCloneTable
022 0x00000578 0x00000578  14  15 (.dynstr) ascii __gmon_start__
023 0x00000587 0x00000587  25  26 (.dynstr) ascii _ITM_registerTMCloneTable
024 0x00000cd0 0x00000cd0   5   6 (.text) ascii AWAVI
025 0x00000cd7 0x00000cd7   5   6 (.text) ascii AUATL
026 0x00000d29 0x00000d29  14  16 (.text)  utf8 \b[]A\\A]A^A_Ðf.
027 0x00000d54 0x00000d54  13  14 (.rodata) ascii socket failed
028 0x00000d62 0x00000d62  17  18 (.rodata) ascii setsockopt failed
029 0x00000d74 0x00000d74  11  12 (.rodata) ascii bind failed
030 0x00000d80 0x00000d80  13  14 (.rodata) ascii listen failed
031 0x00000d93 0x00000d93   4   5 (.rodata) ascii bash
032 0x00000d98 0x00000d98  13  14 (.rodata) ascii /usr/bin/bash
033 0x00000da6 0x00000da6  12  13 (.rodata) ascii execl failed
034 0x00000e08 0x00000e08   4   5 (.eh_frame) ascii \e\f\a\b
035 0x00000e38 0x00000e38   4   5 (.eh_frame) ascii \e\f\a\b
036 0x00000e5f 0x00000e5f   5   6 (.eh_frame) ascii ;*3$"
037 0x00002010 0x00000000  40  41 (.comment) ascii GCC: (Ubuntu 7.5.0-3ubuntu1~18.04) 7.5.0
038 0x00002791 0x00000001  10  11 (.strtab) ascii crtstuff.c
039 0x0000279c 0x0000000c  20  21 (.strtab) ascii deregister_tm_clones
040 0x000027b1 0x00000021  21  22 (.strtab) ascii __do_global_dtors_aux
041 0x000027c7 0x00000037  14  15 (.strtab) ascii completed.7698
042 0x000027d6 0x00000046  38  39 (.strtab) ascii __do_global_dtors_aux_fini_array_entry
043 0x000027fd 0x0000006d  11  12 (.strtab) ascii frame_dummy
044 0x00002809 0x00000079  30  31 (.strtab) ascii __frame_dummy_init_array_entry
045 0x00002828 0x00000098  17  18 (.strtab) ascii payload_1_shell.c
046 0x0000283a 0x000000aa  13  14 (.strtab) ascii __FRAME_END__
047 0x00002848 0x000000b8  16  17 (.strtab) ascii __init_array_end
048 0x00002859 0x000000c9   8   9 (.strtab) ascii _DYNAMIC
049 0x00002862 0x000000d2  18  19 (.strtab) ascii __init_array_start
050 0x00002875 0x000000e5  18  19 (.strtab) ascii __GNU_EH_FRAME_HDR
051 0x00002888 0x000000f8  21  22 (.strtab) ascii _GLOBAL_OFFSET_TABLE_
052 0x0000289e 0x0000010e  15  16 (.strtab) ascii __libc_csu_fini
053 0x000028ae 0x0000011e  27  28 (.strtab) ascii _ITM_deregisterTMCloneTable
054 0x000028ca 0x0000013a  23  24 (.strtab) ascii setsockopt@@GLIBC_2.2.5
055 0x000028e2 0x00000152   6   7 (.strtab) ascii _edata
056 0x000028e9 0x00000159  18  19 (.strtab) ascii chdir@@GLIBC_2.2.5
057 0x000028fc 0x0000016c  27  28 (.strtab) ascii __stack_chk_fail@@GLIBC_2.4
058 0x00002918 0x00000188  18  19 (.strtab) ascii htons@@GLIBC_2.2.5
059 0x0000292b 0x0000019b  16  17 (.strtab) ascii dup@@GLIBC_2.2.5
060 0x0000293c 0x000001ac  19  20 (.strtab) ascii memset@@GLIBC_2.2.5
061 0x00002950 0x000001c0  18  19 (.strtab) ascii close@@GLIBC_2.2.5
062 0x00002963 0x000001d3  30  31 (.strtab) ascii __libc_start_main@@GLIBC_2.2.5
063 0x00002982 0x000001f2  12  13 (.strtab) ascii __data_start
064 0x0000298f 0x000001ff  14  15 (.strtab) ascii __gmon_start__
065 0x0000299e 0x0000020e  12  13 (.strtab) ascii __dso_handle
066 0x000029ab 0x0000021b  14  15 (.strtab) ascii _IO_stdin_used
067 0x000029ba 0x0000022a  15  16 (.strtab) ascii __libc_csu_init
068 0x000029ca 0x0000023a   6   7 (.strtab) ascii server
069 0x000029d1 0x00000241  19  20 (.strtab) ascii listen@@GLIBC_2.2.5
070 0x000029e5 0x00000255  11  12 (.strtab) ascii __bss_start
071 0x000029f1 0x00000261   4   5 (.strtab) ascii main
072 0x000029f6 0x00000266  17  18 (.strtab) ascii bind@@GLIBC_2.2.5
073 0x00002a08 0x00000278  19  20 (.strtab) ascii perror@@GLIBC_2.2.5
074 0x00002a1c 0x0000028c  19  20 (.strtab) ascii accept@@GLIBC_2.2.5
075 0x00002a30 0x000002a0  17  18 (.strtab) ascii exit@@GLIBC_2.2.5
076 0x00002a42 0x000002b2  11  12 (.strtab) ascii __TMC_END__
077 0x00002a4e 0x000002be  25  26 (.strtab) ascii _ITM_registerTMCloneTable
078 0x00002a68 0x000002d8  18  19 (.strtab) ascii execl@@GLIBC_2.2.5
079 0x00002a7b 0x000002eb  27  28 (.strtab) ascii __cxa_finalize@@GLIBC_2.2.5
080 0x00002a97 0x00000307  17  18 (.strtab) ascii fork@@GLIBC_2.2.5
081 0x00002aa9 0x00000319  19  20 (.strtab) ascii socket@@GLIBC_2.2.5
082 0x00002abe 0x00000001   7   8 (.shstrtab) ascii .symtab
083 0x00002ac6 0x00000009   7   8 (.shstrtab) ascii .strtab
084 0x00002ace 0x00000011   9  10 (.shstrtab) ascii .shstrtab
085 0x00002ad8 0x0000001b   7   8 (.shstrtab) ascii .interp
086 0x00002ae0 0x00000023  13  14 (.shstrtab) ascii .note.ABI-tag
087 0x00002aee 0x00000031  18  19 (.shstrtab) ascii .note.gnu.build-id
088 0x00002b01 0x00000044   9  10 (.shstrtab) ascii .gnu.hash
089 0x00002b0b 0x0000004e   7   8 (.shstrtab) ascii .dynsym
090 0x00002b13 0x00000056   7   8 (.shstrtab) ascii .dynstr
091 0x00002b1b 0x0000005e  12  13 (.shstrtab) ascii .gnu.version
092 0x00002b28 0x0000006b  14  15 (.shstrtab) ascii .gnu.version_r
093 0x00002b37 0x0000007a   9  10 (.shstrtab) ascii .rela.dyn
094 0x00002b41 0x00000084   9  10 (.shstrtab) ascii .rela.plt
095 0x00002b4b 0x0000008e   5   6 (.shstrtab) ascii .init
096 0x00002b51 0x00000094   8   9 (.shstrtab) ascii .plt.got
097 0x00002b5a 0x0000009d   5   6 (.shstrtab) ascii .text
098 0x00002b60 0x000000a3   5   6 (.shstrtab) ascii .fini
099 0x00002b66 0x000000a9   7   8 (.shstrtab) ascii .rodata
100 0x00002b6e 0x000000b1  13  14 (.shstrtab) ascii .eh_frame_hdr
101 0x00002b7c 0x000000bf   9  10 (.shstrtab) ascii .eh_frame
102 0x00002b86 0x000000c9  11  12 (.shstrtab) ascii .init_array
103 0x00002b92 0x000000d5  11  12 (.shstrtab) ascii .fini_array
104 0x00002b9e 0x000000e1   8   9 (.shstrtab) ascii .dynamic
105 0x00002ba7 0x000000ea   5   6 (.shstrtab) ascii .data
106 0x00002bad 0x000000f0   4   5 (.shstrtab) ascii .bss
107 0x00002bb2 0x000000f5   8   9 (.shstrtab) ascii .comment
.eh_frame_hdr
.eh_frame
.init_array
.fini_array
.dynamic
.data
.bss
.comment
```
# zusammenfassung

**"unknown_3"** ist eine ELF-Datei, die für 64-Bit-Systeme (x86-64) entwickelt wurde
.
**unknown_3** enthält  eine ELF-Datei und eine Zlib-komprimierte Datei.

Nach dem extraktion  "unknown_3"  bekommt man eine datei  "1020" .

**"1020"** ist ebenfalls eine ELF-Datei für 64-Bit-Systeme und nicht entkernt.  es gibt  einen Verweis auf "/usr/bin/bash" .
das könnte bedeuten ,dass die Datei "1020" möglicherweise mit der Bash-Shell interagiert oder auf sie zugreift, Befehle ausführt oder versucht, auf die Funktionen der Bash-Shell zuzugreifen.

### Importanalyse von "1020":
wir haben die Importe der Datei "1020" mit "rabin2 -i" analysiert. Dabei haben wir  eine Liste von Importen gefunden, die Funktionen und Bibliotheken darstellen, die von der Datei verwendet werden. Einige dieser Importe sind verdächtig, wie "socket", "fork", "execl", "listen", usw.

**socket**: Eine Funktion zum Erstellen von Netzwerk-Sockets, die zur Kommunikation über das Netzwerk verwendet werden.

**fork**: Erzeugt einen neuen Prozess (Kindprozess) durch Kopieren des aktuellen Prozesses (Elternprozess).

**execl**: Eine Funktion, um ein neues Programm auszuführen. Sie ersetzt das aktuelle Programm mit einem neuen und startet es.

**listen**: Wird normalerweise in Serveranwendungen verwendet, um einen Socket in den "Lausch"-Modus zu versetzen und auf eingehende Verbindungen von Clients zu warten.

**bind**:  die einen Socket an eine bestimmte IP-Adresse und Portnummer bindet.

**__gmon_start__**: Dies ist eine Funktion, die im Zusammenhang mit dem GNU-Profiler (gprof) steht, einem Werkzeug zur Codeprofilierung.

**accept**: Eine Funktion , die eine Verbindung von einem Socket akzeptiert.

**chdir**: Dies ist eine Funktion zum Ändern des aktuellen Arbeitsverzeichnisses des Programms.

**dup**: Diese Funktion wird verwendet, um eine Kopie eines Dateideskriptors zu erstellen.

**__stack_chk_fail**: Dies ist eine Funktion, die bei einem  Stack Overflow aufgerufen wird.


### Exportanalyse

**"main":**

die beim Starten des Programms aufgerufen wird. Sie enthält normalerweise den Hauptprogrammcode und koordiniert die Ausführung anderer Funktionen und Operationen. In diesem Kontext könnte "main" die Einstiegspunkt-Funktion für das Programm sein.

**"server":**

"server" könnte eine benutzerdefinierte Funktion oder ein Symbol innerhalb der Datei "1020" sein, die spezifische serverbezogene Aufgaben ausführt. Dies könnte bedeuten, dass diese Funktion für die Verwaltung eines Servers oder für Netzwerkkommunikation verantwortlich ist, da die Datei "1020" möglicherweise auf "socket" und "listen" verweist, die für Netzwerkkommunikation relevant sind.

### Verwendete Bibliotheken
**"libc.so.6"**  ist die C-Standardbibliothek, die Funktionen und Ressourcen für C-Programme bereitstellt. 

### Stringsanalyse
 **"socket failed"** und **"setsockopt failed"** könnten Fehlermeldungen oder Statusnachrichten sein

 ## Schlussfolgerung

Es handelt sich wahrscheinlich um eine Reverse Shell-Anwendung, da das Programm in die Bash-Shell integriert ist und Befehle ausführt. Dies deutet darauf hin, dass es möglicherweise für ferngesteuerte Verbindungen zu einem entfernten Server oder System entwickelt wurde.

Das Programm kommuniziert auch über das Netzwerk, da es die "socket" Funktion verwendet, um Netzwerkverbindungen herzustellen. Es erzeugt Prozesse mit "fork" und führt neue Programme mit "execl" aus. Dies weist auf eine umfassende Funktionalität für Netzwerkkommunikation und die Möglichkeit der Programmsteuerung hin.

Die Verwendung von "listen" deutet darauf hin, dass das Programm auf eingehende Verbindungen von Clients wartet, was typisch für Serveranwendungen ist.

Die Exporte "main" und "server" könnten spezifische Funktionen oder Symbole innerhalb des Programms darstellen. "main" ist in der Regel die Hauptfunktion des Programms, während "server" wahrscheinlich für serverbezogene Aufgaben verantwortlich ist.

Die Fehlermeldungen "socket failed" und "setsockopt failed" deuten auf mögliche Probleme oder Fehler hin, die während der Netzwerkkommunikation auftreten können.





