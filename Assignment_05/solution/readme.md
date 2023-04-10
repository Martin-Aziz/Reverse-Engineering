# Lösung: Exports und Imports mit rabin2 untersuchen

Es handelt sich um eine Shared-Library, die von anderen Programmen genutzt werden kann. Die exportierten Symbole der Datei kann man sich mit dem folgenden Kommando ansehen:

```console
$ rabin2 -s payload_2.so
```

Das Kommando gibt etwas über 70 exportierte Symbole aus. Interessant sind hier insbesondere folgende:

```console
[Symbols]

nth paddr      vaddr      bind   type   size lib name
―――――――――――――――――――――――――――――――――――――――――――――――――――――
23  0x000019ab 0x000019ab GLOBAL FUNC   75       AES_init_ctx_iv
...
27  0x000013f0 0x000013f0 GLOBAL FUNC   251      encrypt_files
28  0x0000290d 0x0000290d GLOBAL FUNC   146      AES_CBC_encrypt_buffer
...
29  0x000014eb 0x000014eb GLOBAL FUNC   160      hostname_to_ip
...
31  0x000013b5 0x000013b5 GLOBAL FUNC   59       generate_system_id
...
34  0x00001359 0x00001359 GLOBAL FUNC   92       generate_key
35  0x0000158b 0x0000158b GLOBAL FUNC   311      send_home
```

Die Importe können mit `rabin2 -i payload_2.so` angezeigt werden.

```console
[Imports]
nth vaddr      bind   type   lib name
―――――――――――――――――――――――――――――――――――――
2   0x00001170 GLOBAL FUNC       strcpy
3   0x00001180 GLOBAL FUNC       inet_ntoa
4   0x00001190 GLOBAL FUNC       opendir
6   0x000011b0 GLOBAL FUNC       htons
7   0x000011c0 GLOBAL FUNC       send
8   0x000011d0 GLOBAL FUNC       memset
9   0x000011e0 GLOBAL FUNC       close
10  0x000011f0 GLOBAL FUNC       closedir
11  0x00001200 GLOBAL FUNC       read
12  0x00001210 GLOBAL FUNC       gethostbyname
14  0x00001220 GLOBAL FUNC       inet_pton
15  0x00001230 GLOBAL FUNC       readdir
16  0x00001250 GLOBAL FUNC       open
17  0x00001260 GLOBAL FUNC       strcat
18  0x00001270 GLOBAL FUNC       exit
19  0x00001280 GLOBAL FUNC       connect
22  0x00001290 GLOBAL FUNC       socket
```

Die Bibliothek exportiert Verschlüsselungsroutinen (`AES_*`) und enthält Funktionen, die darauf hindeuten, dass Dateien mit einem frisch generierten Schlüssel verschlüsselt werden. Außerdem scheint eine Kommunikation mit dem Internet zu erfolgen, da entsprechende Socket-Funktionen vorhanden sind.

Es handelt sich höchstwahrscheinlich um eine Bibliothek aus einem **Verschlüsselungstrojaner**.

Schaut man sich zusätzlich noch die Strings in der Datei mit `rabin2 -z payload_2.so` an, so findet man folgende Einträge:

```console
[Strings]
nth paddr      vaddr      len size section type  string
―――――――――――――――――――――――――――――――――――――――――――――――――――――――
0   0x00003000 0x00003000 12  13   .rodata ascii /dev/urandom
1   0x0000300d 0x0000300d 16  17   .rodata ascii ransom.evil.corp
...
```

Der erste String zeigt, dass die Zufallszahlen für den Schlüssel mithilfe von `/dev/urandom` erzeugt werden. Der zweite deutet auf den Control Server (CC) der Ransomware hin.


Der Source-Code zeigt, dass der Verdacht gerechtfertigt war:

  * [payload_2.c](payload_2.c)
