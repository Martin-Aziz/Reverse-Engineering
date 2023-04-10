# Crackme Team 13
[`Sprung zum Flag`](https://gitty.informatik.hs-mannheim.de/ree-lecture/team-13/src/branch/main/Assignment_31#user-content-flag)

## Hinweis

Es existieren zwei Flags in diesem Crackme, jedoch ist eins davon nicht echt. Außerdem stimmt das Format der Flag auch nicht. FLAG{xxx} ist nur bei dem echten Flag.

Das Crackme:
-   [crackme13](https://gitty.informatik.hs-mannheim.de/ree-lecture/team-13/src/branch/main/Assignment_31/crackme13)

## Fake Flag
Wenn wir uns den Code in Ghidra anschauen, sehen wir auf den ersten Blick die passwordCheck und win Funktion.

```c
void passwordCheck(void)
{
  char local_a8 [80];
  char local_58 [76];
  uint local_c;
 
  local_c = 0x13371337;
  puts("Log dich ein mit deinem Password: ");
  gets(local_58);
  if (local_c == 0xbadface) {
    win();
  }
  else {
    printf("Kannst du dein Passwort nicht schreiben? Es ist: %04x\n",(ulong)local_c);
    puts("Wie viele Versuche hast du gebraucht?");
    gets(local_a8);
    printf("Stundenzahl verschwendet: %s\n",local_a8);
  }
  return;
}
```
Es ist zu erkennen, dass zweimal `gets` aufgerufen wird. Da wir jedoch beim ersten `gets` an unser `"win()"` Funktion dran kommen, fangen wir hier an. Wir sehen dank Ghidra, dass der Buffer 76 Chars groß. Deswegen schreiben wir eine mini Payload in Python.
```console
python2 -c 'print 76 * "A"' > payload1st
```
Diese Payload starten wir einfach in gdb.
```console
(gdb) r < payload1st
Log dich ein mit deinem Password: 
Kannst du dein Passwort nicht schreiben? Es ist: 13371300
```
Wir sehen, dass sich der Stack schon verschoben hat. Also müssen wir jetzt nur noch das richtige Passwort zusätzlich noch einfügen, damit 0xbadface == 0xbadface stimmt. Wir wissen außerdem, dass es ein LSB executable ist. Deswegen müssen wir 0x rückwärts schreiben. Zusätzlich verwandeln wir es in ASCII Escape Code und wir erhalten dann: `\xce\xfa\xad\x0b`
Als Nächstes fügen wir es zu unserer Payload hinzu.
```console
python2 -c 'print 76 * "A" + "\xce\xfa\xad\x0b"' > payload1st
```
```console
./crackme13 < payload1st
Log dich ein mit deinem Password: 
FL4G[NiCeTIMewAStE!]
```
Die Vermutung war angeblich falsch, dass sich hier die richtige Flag befindet.
## Real Flag
Die nächste Schwachstelle wäre bei dem zweiten `gets`. Wenn wir uns die Funktionen in Ghidra genauer anschauen, sehen wir, dass sich eine Methode versteckt. Der Name wurde in `_dl_relocate_static` geändert, damit es sich besser unter den anderen C Funktionen verstecken kann. Die Funktion sieht genauso aus wie die Funktion `win()`.
```c
void _dl_relocate_static(void)
{
  undefined8 local_78;
  undefined8 local_70;
  undefined4 local_68;
  undefined local_64;
  int local_10;
  int local_c;
  
  local_78 = 0x67317835657b4146;
  local_70 = 0x466b6e47307d6f6f;
  local_68 = 0x4c474c54;
  local_64 = 0;
  local_10 = 0x14;
  for (local_c = 0; local_c < local_10 / 2; local_c = local_c + 1) {
    printf("%c%c",(ulong)(uint)(int)*(char *)((long)&local_78 + (long)local_c),
           (ulong)(uint)(int)*(char *)((long)&local_78 + (long)((local_10 - local_c) + -1)));
  }
  return;
}
```
Nun können wir von dem zweiten `gets` ein Buffer Overflow erzeugen und dadurch in diese Funktion gelangen. 
Wir versuchen es im gdb 81 * "A" und schauen, ob es wieder übereinstimmt mit der Größe des Buffers.
```console
(gdb) r
Log dich ein mit deinem Password: 
a
Kannst du dein Passwort nicht schreiben? Es ist: 13371337
Wie viele Versuche hast du gebraucht?
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Stundenzahl verschwendet: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
[Inferior 1 (process 17173) exited normally]
(gdb) 
```
Wir sehen, dass es mit 81 keine Probleme gab. Deswegen erhöhen wir es einfach und schreiben 170 * "A" rein.
```console
(gdb) r
Log dich ein mit deinem Password: 
a
Kannst du dein Passwort nicht schreiben? Es ist: 13371337
Wie viele Versuche hast du gebraucht?
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Stundenzahl verschwendet: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA
Program received signal SIGSEGV, Segmentation fault.
0x0000000000004141 in ?? ()
(gdb) bt
#0  0x0000000000004141 in ?? ()
#1  0x0000000000000001 in ?? ()
```
Wir sehen an dem backtrace, dass wir zwei As zu viel eingefügt haben. Wenn wir es wiederholen und nur 168 * "A" einfügen, erhalten wir:
```console
Program received signal SIGILL, Illegal instruction.
0x0000000000401200 in passwordCheck ()
```
Also sind wir genau an der Grenze angekommen. Nun brauchen wir nur noch die Adresse von der Stelle in der Funktion `_dl_relocate_static`. Die Adresse ist die, wo RSP in RBP gemovt wird, auf der Adresse `4012ce`. Hier muss die Adresse wieder umgedreht werden und in ASCII Escape Code umgewandelt werden, damit erhalten wir: `\xce\x12\x40`. Außerdem kann man ein kleinen Script schreiben, welches das doppelte, manuelle Tippen, erleichtert.

```python
from pwn import *
io = process('./crackme13')
io.recvline()
io.sendline(b'A'*76) #erste Eingabe
io.sendline(b'B'*148 + b'A'*20 +b'\xce\x12\x40') #168 | zweite Eingabe
io.interactive()
```
Wenn wir das nun ausführen, erhalten wir: 
```console
./crackme13Script.py
[+] Starting local process './crackme13': pid 17319
[*] Switching to interactive mode
[*] Process './crackme13' stopped with exit code 10 (pid 17319)
Kannst du dein Passwort nicht schreiben? Es ist: 13371300
Wie viele Versuche hast du gebraucht?
Stundenzahl verschwendet: BBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBBAAAAAAAAAAAAAAAAAAAA\xce@
FLAG{LeT5Fxk1ngGo0o}
```
## Flag
`FLAG{LeT5Fxk1ngGo0o}`