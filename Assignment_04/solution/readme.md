# Lösung: Importe mit rabin2 untersuchen

```console
$ rabin2 -i payload_1
[Imports]
nth vaddr      bind   type   lib name
―――――――――――――――――――――――――――――――――――――
1   0x00000000 WEAK   NOTYPE     _ITM_deregisterTMCloneTable
2   0x00001120 GLOBAL FUNC       setsockopt
3   0x00001130 GLOBAL FUNC       __stack_chk_fail
4   0x00001140 GLOBAL FUNC       system
5   0x00001150 GLOBAL FUNC       htons
6   0x00001160 GLOBAL FUNC       printf
7   0x00001170 GLOBAL FUNC       memset
8   0x00001180 GLOBAL FUNC       read
9   0x00000000 GLOBAL FUNC       __libc_start_main
10  0x00000000 WEAK   NOTYPE     __gmon_start__
11  0x00001190 GLOBAL FUNC       listen
12  0x000011a0 GLOBAL FUNC       bind
13  0x000011b0 GLOBAL FUNC       perror
14  0x000011c0 GLOBAL FUNC       accept
15  0x000011d0 GLOBAL FUNC       exit
16  0x00000000 WEAK   NOTYPE     _ITM_registerTMCloneTable
17  0x000011e0 GLOBAL FUNC       fork
18  0x000011f0 GLOBAL FUNC       socket
19  0x00000000 WEAK   FUNC       __cxa_finalize
```

Die Liste zeigt eine Reihe von Imports, das Programm wurde also nicht statisch gelinkt, sodass wir die Funktionen aus der C-Library sehen können, die aufgerufen werden. Besonders relevant sind die folgenden:

  * `socket` - erzeugt einen Endpunkt für eine Netzwerkkommunikation
  * `setsockopt` - setzt Optionen für das Socket
  * `bind` - bindet das Socket an einen bestimmten Port
  * `listen` - wartet auf _eingehende_ Netzwerkverbindungen
  * `accept` - nimmt eingehende Netzwerkverbindung an
  * `read` - liest Daten ein, auch von einem Socket
  * `system` - führt ein Kommando auf dem Betriebssystem aus
  * `htons` - wandelt Daten in die sogenannte Network-Byte-Order
  * `fork` - erzeugt einen neuen Kindprozess

Es handelt sich also höchstwahrscheinlich um einen Netzwerk-Server, der auf einem bestimmten Port lauscht (`bind`, `listen`), Daten entgegennimmt (`read`) und die Daten irgendwie dazu benutzt Kommandos direkt auf dem Betriebssystem mit `system` auszuführen. Das `fork` deutet darauf hin, dass das Programm einen zweiten Prozess abspaltet, z.B. um im Hintergrund weiterzulaufen und nicht entdeckt zu werden.

Die importierten Funktionen machen das Programm hochgradig verdächtig. Es kann sich um eine Malware handeln.

Der Source-Code zeigt, dass der Verdacht gerechtfertigt war:

  * [payload_1.c](payload_1.c)
