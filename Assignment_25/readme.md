# Assignment: Disassemblieren eines unbekannten Programms (verschlüsselt)



Ihn liegt ein Programm unbekannter Funktionalität vor, das Sie analysieren sollen. Dieses Programm ist verschlüsselt und wird erst zur Laufzeit entschlüsselt, weswegen wir einen Umweg gehen müssen.


## Hinweis

Bei dem Executable handelt es sich um ein Programm unbekannter Funktionalität, wie man sie z.B. bei der Untersuchung von kompromittierten Rechner finden könnte. Es kann gut sein, dass es sich um eine _Malware_ handelt, welche bei der Ausführung Schaden verursacht, bis hin zur Zerstörung aller Daten auf dem Rechner. Deswegen sollten Sie die Datei __auf keinen Fall__ ohne Schutzmaßnahmen (virtuelle Maschine etc.) __ausführen__. Die hier vorgenommene Analyse kommt ohne Ausführung der Datei aus und ist insofern sicher auch ohne Schutzmaßnahmen durchführbar.

Sie müssen in der Realität damit rechnen, dass die Malware Schwachstellen in den von Ihnen verwendeten Werkzeugen nutzt, um bei einem Reverse-Engineering Ihren Rechner anzugreifen. Da wir uns hier in einem Übungskontext befinden, ignorieren wir dieses Problem.


## Ghidra

Diese Aufgabe verwendet [Ghidra](https://ghidra-sre.org/), ein umfangreiches Reverse-Engineering-Tool, das von der NSA entwickelt und als Open-Source-Lösung frei zur Verfügung gestellt wird.

Laden Sie Ghidra herunter und installieren Sie es auf Ihrem Rechner.


## gdb

Für diese Übung werden wir den Kommandozeilendebugger `gdb` einsetzen. Sie finden Tipps zur Installation und Verwendung in der [Kurzanleitung](../help/gdb.md).

## Aufgabe

Sie finden das Programm unter:

  * [unknown_2](unknown_2)

### Erste Analyse in Ghidra

Analysieren Sie das Programm in Ghidra und versuchen Sie die Funktionalität zu verstehen.

Sie werden feststellen, dass die eigentliche Funktionalität verschlüsselt ist und erst bei Ausführung des Programms in den Hauptspeicher geladen, entschlüsselt und ausgeführt wird. Um an die entschlüsselte Payload zu gelangen, werden wir `gdb` verwenden.

### Entschlüsselung mit gdb

Sie müssen das Programm so weit ausführen, dass es entschlüsselt im Speicher liegt. Hierzu verwenden wir den GNU Debugger (`gdb`).

Gehen Sie wie folgt vor:

Starten Sie den Debugger und teilen Sie ihm mit, dass Sie diese Datei analysieren wollen:

```console
$ gdb unknown_2
GNU gdb (Ubuntu 9.2-0ubuntu2) 9.2
...
(No debugging symbols found in unknown_2)
(gdb) _
```

Führen Sie das Programm __nicht__ aus, sondern setzen Sie einen Breakpoint in der `main`-Funktion direkt vor der `call`-Instruktion, die die Payload ausführt.

```console
(gdb) disass main
Dump of assembler code for function main:
   0x0000000000001264 <+0>:	endbr64
   0x0000000000001268 <+4>:	push   rbp
   0x0000000000001269 <+5>:	mov    rbp,rsp
   0x000000000000126c <+8>:	sub    rsp,0x20
   0x0000000000001270 <+12>:	mov    DWORD PTR [rbp-0x14],edi
   0x0000000000001273 <+15>:	mov    QWORD PTR [rbp-0x20],rsi
   0x0000000000001277 <+19>:	mov    edi,0xbc
   0x000000000000127c <+24>:	call   0x1209 <alloc_executable_memory>
   0x0000000000001281 <+29>:	mov    QWORD PTR [rbp-0x8],rax
   0x0000000000001285 <+33>:	mov    eax,DWORD PTR [rip+0x2e51]        # 0x40dc <bin_payload_5_encrypted_bin_len>
   0x000000000000128b <+39>:	mov    edx,eax
   0x000000000000128d <+41>:	mov    rax,QWORD PTR [rbp-0x8]
   0x0000000000001291 <+45>:	mov    r8d,0xa
   0x0000000000001297 <+51>:	lea    rcx,[rip+0xd6b]        # 0x2009
   0x000000000000129e <+58>:	lea    rsi,[rip+0x2d7b]       # 0x4020 <bin_payload_5_encrypted_bin>
   0x00000000000012a5 <+65>:	mov    rdi,rax
   0x00000000000012a8 <+68>:	call   0x12bf <xor_crypt>
   0x00000000000012ad <+73>:	mov    rdx,QWORD PTR [rbp-0x8]
   0x00000000000012b1 <+77>:	mov    eax,0x0
   0x00000000000012b6 <+82>:	call   rdx
   0x00000000000012b8 <+84>:	mov    eax,0x0
   0x00000000000012bd <+89>:	leave
   0x00000000000012be <+90>:	ret
(gdb) break *main+82
Breakpoint 1 at 0x12b6
```

Jetzt können Sie das Programm mit `r` starten und auf den Breakpoint laufen lassen.

```console
(gdb) r
Starting program: unknown_1

Breakpoint 1, 0x00005555555552b6 in main ()
```

Im Register `rdx` findet sich die Start-Adresse der entschlüsselten Payload:

```console
(gdb) p /x $rdx
$1 = 0x7ffff7fc2000
```

Disassemblieren Sie die Instruktionen an dieser Adresse mit `x /i`, bis Sie auf eine Reihe von `add BYTE PTR [rax],al` treffen. Diese Instruktion entspricht dem Opcode `0x00` und deutet auf das Ende der Payload.

```console
(gdb) x /70i 0x7ffff7fc2000
   0x7ffff7ffa000:	xor    rax,rax
   0x7ffff7ffa003:	push   rax
   0x7ffff7ffa004:	movabs rax,0x6477737361702f2f
   0x7ffff7ffa00e:	push   rax
   0x7ffff7ffa00f:	movabs rax,0x2f2f2f2f6374652f
...
   0x7ffff7ffa055:	mov    eax,0x3
   0x7ffff7ffa05a:	mov    rdi,r10
   0x7ffff7ffa05d:	syscall
   0x7ffff7ffa05f:	mov    eax,0x3c
   0x7ffff7ffa064:	mov    edi,0x0
   0x7ffff7ffa069:	syscall
   0x7ffff7ffa06b:	add    BYTE PTR [rax],al
   0x7ffff7ffa06d:	add    BYTE PTR [rax],al
```

Sie können die Länge der Payload mit aus den Adressen berechnen:

```console
(gdb) p 0x7ffff7ffa06b-$rdx
$3 = 107
```

Sie ist also 107 Bytes lang.

Die Payload schreiben Sie jetzt mithilfe von `gdb` in eine Datei mit beliebigem Namen, z.B. `payload.bin`, wobei Sie natürlich die Start- (`0x7ffff7ffa000`) und Endadresse (`0x7ffff7ffa06b`) aus Ihren Ausgaben übernehmen müssen:

```console
(gdb) dump binary memory payload.bin 0x7ffff7ffa000 0x7ffff7ffa06b
```

Verlassen Sie `gdb` und laden Sie die extrahierten Daten in Ghidra.

### Erneute Analyse in Ghidra

Ghidra weiß nicht, um was es sich handelt, weil keinerlei Header-Informationen vorhanden sind. Es handelt sich um die nackte Payload. Wählen Sie daher

  * Format: Raw Binary
  * Language: x86:LE:64:default:gcc
    * Processor: x86
    * Variant: default
    * Size: 64
    * Endian: little
    * Compiler: gcc

Lassen Sie Ghidra die Datei analysieren. Leider wird Ghidra aber keine Strukturen erkennen, sodass Sie links nur die reinen Bytes angezeigt bekommen.

Klicken Sie links auf die das erste Byte (`48`)
 und drücken Sie `D`, um die Daten zu disassemblieren.

Wahrscheinlich wird Ghidra ungefähr in der Mitte ein Problem haben und die Disassemblierung mit `??` abbrechen. Gehen Sie auf die das erste Byte, nach den `??` drücken Sie `C`, um die Interpretation zu löschen. Gehen Sie jetzt auf das erste Byte mit `??` und drücken Sie erneut `D`. Das Programm sollte jetzt vollständig disassembliert sein.

Sie sehen eine Reihe von Betriebssystemaufrufen (`syscall`-Instruktion). Um herauszufinden, was diese tun, benötigen Sie eine [Tabelle der System-Calls](https://blog.rchapman.org/posts/Linux_System_Call_Table_for_x86_64/).

Es handelt sich um handgeschriebenen Assembler-Code. Deswegen versagt die Dekompilation als C-Programm und bringt wenig Informationen.

Interessant sind die Zeichenketten, die sich in den langen Zahlenkonstanten verbergen, die auf den Stack gepusht werden. Gehen Sie in Ghdidra auf diese Zahlenkonstanten und klicken Sie mit der rechten Maustaste und wählen Sie `convert` -> `char sequence`. Denken Sie daran, dass Intel eine Litte-Endian-Architektur ist, wenn Sie die Texte interpretieren.

Was macht das Programm?


## Abgabe

  * Schreiben Sie auf, wie Sie vorgegangen sind, und zwar so, dass ein fachkundiger Dritter Ihre Schritte nachvollziehen kann.
  * Gab es Probleme?
  * Welche Information konnten Sie extrahieren?
  * Falls es ein Flag gab, wie lautete das Flag?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.

Bitte legen Sie im Wurzelverzeichnis Ihres Repos eine Datei `readme.md` an, die einen Überblick über die Assignments und Write-Ups liefert. Die WritUps sollten von dieser Datei aus verlinkt sein. Gestalten Sie das Repo so, dass man sich leicht und schnell zurechtfinden kann.