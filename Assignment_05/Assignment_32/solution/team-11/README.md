# Capture the Flag (Team 11)

|Name|Matrikel-Nummer|
|-|-|
|Marius Schmalz|1924338|
|Felix Klör|1924300|
|Lukas Hagmaier|1926235|

## Zusammenfassung

Das Crackme besteht aus zwei Teilen. Zuerst muss ein Lizenzschlüssel gefunden werden, welcher daraufhin benötigt wird, um unter Verwendung eines Bufferoverflows einen Funktionspointer auf die `win`-Methode zu setzen.

Die benötigte Lizenz liegt als XOR-verschlüsselter Hex-Wert offen sichtbar in der `main`-Methode. Der Funktionspointer kann durch die unsichere `gets`-Anweisung überschrieben werden, welche den Lizenzschlüssel in einen Buffer statischer Länge einliest. Der Bufferoverflow ist auch ohne korrekten Lizenzschlüssel möglich -- zu der Funktion, auf welche der Pointer zeigt, wird aber nur gesprungen, wenn die Lizenz valide ist. 

Um das Überschreiben des Funktionspointers mithilfe von `gets` zu ermöglichen, wird das Crackme mit deaktiviertem `stack-protector` kompiliert. Da wir das Gefühl hatten, das Crackme wäre potenziell zu schwierig, haben wir hier im Nachhinein versucht gegengesteuern: Wir verwenden die Option `no-pie`, um ASLR zu deaktivieren und somit das Überschreiben des Funktionspointers zu vereinfachen, indem die Adresse der überschreibenden Funktion statisch bleibt. Außerdem haben wir die Adresse manuell an eine Adresse im ASCII-Bereich gerückt, da sie über die Konsole eingegeben werden muss und die Lösung ansonsten potenziell das Verwenden einer Skriptsprache voraussetzt.

## Vorgehensweise zum Lösen

Folgende Ausgabe erwartet einen beim Ausführen des Crackmes:

```shell-session
$ ./crackme
+-----+ Welcome to the 'HyperCam 2' registration wizard! +-----+
Checking license status...
Your current license status: 'Unregistered HyperCam 2'
Please enter a valid license key: 
```

Man kann erkennen, dass eine Lizenz benötigt wird, da man seine RuneScape-Videos sonst nur mit Watermark aufnehmen kann.

Hinweise zu beiden Teilen des Crackmes -- der Lizenz und dem Funktionspointer -- springen einen bereits an, wenn man das nicht gestrippte Crackme in Ghidra öffnet:

```c
undefined8 main(void)

{
  int iVar1;
  undefined8 local_a0;
  char local_98 [128];
  code *local_18;
  uint local_c;
  
  local_18 = check_success; 
  local_a0 = 0x2c3a272c2a202625;

  for (local_c = 0; local_c < 8; local_c = local_c + 1) {
    local_98[(long)(int)local_c + -8] = local_98[(long)(int)local_c + -8] ^ 0x69;
  }
  
  [...]

  printf("%s","Please enter a valid license key: ");
  gets(local_98);
  
  [...]
```

`local18` scheint ein Pointer auf die Funktion `check_success` zu sein, während `local_a0` einen verdächtigen Hex-Wert enthält. Ghidra ist hier zwar etwas verwirrt (wir können es uns leider nicht so ganz erklären), davon unabhängig kann man aber trotzdem erkennen, dass in den nächsten Zeilen in einer `for`-Schleife ein Wert mit `0x69` gexored. Auffällig ist außerdem, dass die Eingabe mit der bekannterweise anfälligen Anweisung `gets` eingelesen wird und der Zielbuffer eine feste Länge von 128 hat.

### Entschlüsseln der Lizenz

Kopiert man sich den Wert `0x2c3a272c2a202625` (und trennt ihn in einzelne Hex-Werte), kann man die vorgenommene Entschlüsselung leicht nachstellen (`reversed` wird verwendet, da der Wert im Little-Endian Format angegeben ist): 
```python
print(bytes(a ^ 0x69 for a in reversed([0x2c, 0x3a, 0x27, 0x2c, 0x2a, 0x20, 0x26, 0x25])))
```
Ergebnis: `b'LOICENSE'`


Wieder in das Programm eingegeben, erhält man nun bereits einen anderen Output:

```shell-session
$ ./crackme
+-----+ Welcome to the 'HyperCam 2' registration wizard! +-----+
Checking license status...
Your current license status: 'Unregistered HyperCam 2'
Please enter a valid license key: LOICENSE
Executing license check: 0x004011b2...
While the license may be valid, we detected that it was obtained illegally!
```

Mehrmaliges Ausführen zeigt, dass die Zeile `Executing license check: 0x004011b2...` gleichbleibt. Ziel ist es nun, mithilfe einer Eingabe, welche zu einem Bufferoverflow führt, den ausgeführten License-Check zu ändern.

#### Alternativer Lösungsweg

Alternativ kann der Lizenzschlüssel auch als Klartext vom Stack abgelesen werden. Dafür führt man das Programm mit einem Debugger aus und sucht eine beliebige Operation nach der Entschlüsselungsroutine. Hier am Beispiel von Radare2:

```shell-session
$ r2 -d crackme
[0x7f531d151730]> aaa
[0x7f531d151730]> db main
[0x7f531d151730]> dc
[0x004022ed]> pdf
┌ 296: int main (int argc, char **argv, char **envp);
│           ; var int64_t var_4h @ rbp-0x4
│           ; var int64_t var_10h @ rbp-0x10
│           ; var int64_t var_90h @ rbp-0x90
│           ; var int64_t var_98h @ rbp-0x98
│           0x004022ed b    55             push rbp
│           0x004022ee      4889e5         mov rbp, rsp
│           0x004022f1      4881eca00000.  sub rsp, 0xa0
│           0x004022f8      488d05b3eeff.  lea rax, [sym.check_success] ; 0x4011b2
│           0x004022ff      488945f0       mov qword [var_10h], rax
│           0x00402303      48b82526202a.  movabs rax, 0x2c3a272c2a202625 ; '%& *,':,'
│           0x0040230d      48898568ffff.  mov qword [var_98h], rax
│           0x00402314      c745fc000000.  mov dword [var_4h], 0
│       ┌─< 0x0040231b      eb22           jmp 0x40233f
│      ┌──> 0x0040231d      8b45fc         mov eax, dword [var_4h]
│      ╎│   0x00402320      4898           cdqe
│      ╎│   0x00402322      0fb6840568ff.  movzx eax, byte [rbp + rax - 0x98]
│      ╎│   0x0040232a      83f069         xor eax, 0x69               ; 105
│      ╎│   0x0040232d      89c2           mov edx, eax
│      ╎│   0x0040232f      8b45fc         mov eax, dword [var_4h]
│      ╎│   0x00402332      4898           cdqe
│      ╎│   0x00402334      88940568ffff.  mov byte [rbp + rax - 0x98], dl
│      ╎│   0x0040233b      8345fc01       add dword [var_4h], 1
│      ╎│   ; CODE XREF from main @ 0x40231b(x)
│      ╎└─> 0x0040233f      8b45fc         mov eax, dword [var_4h]
│      ╎    0x00402342      83f807         cmp eax, 7                  ; 7
│      └──< 0x00402345      76d6           jbe 0x40231d
│           0x00402347      488d057a0d00.  lea rax, str.______Welcome_to_the_HyperCam_2_registration_wizard_______ ; 0x4030c8 ; "+-----+ Welcome to the 'HyperCam 2' registration wizard! +-----+"
│           0x0040234e      4889c7         mov rdi, rax
[...]
```

Nun nehmen wir beispielsweise die Operation mit der Adresse `0x0040234e` und setzen dort einen Breakpoint. Anschließend lassen wir das Programm bis zu diesem Punkt weiterlaufen und sehen uns den Inhalt des Stacks an:

```shell-session
[0x004022ed]> db 0x0040234e
[0x004022ed]> dc
hit breakpoint at: 0x40234e
[0x0040234e]> pxw @ rsp
0x7ffc2640d060  0x00000004 0x00000000 0x43494f4c 0x45534e45  ........LOICENSE
0x7ffc2640d070  0x00000000 0x00000000 0x00000010 0x00000000  ................
0x7ffc2640d080  0x00000040 0x00000000 0x00008000 0x00000000  @...............
0x7ffc2640d090  0x00000000 0x00000000 0x00000006 0x0000008e  ................
```

### Überschreiben des Funktionspointers

Da der Buffer 128 Zeichen lang ist und unsere Lizenz (`LOICENSE`) 8 Zeichen Lang ist, benötigen wir weitere 120 Zeichen zum Padden, um einen Overflow auszulösen und somit andere Daten im Stack zu überschreiben. Dafür verwenden wir der Lesbarkeit halber Python und pipen den Output in das Crackme.

```shell-session
$ python -c "print('LOICENSE' + 'A'*120)" | ./crackme
+-----+ Welcome to the 'HyperCam 2' registration wizard! +-----+
Checking license status...
Your current license status: 'Unregistered HyperCam 2'
Please enter a valid license key: 
Executing license check: 0x00401100...


Thank you for using HyperCam 2. Exiting... 
```

Wir sehen, dass sich der auszuführende Lizenzcheck bereits geändert hat und der Text fehlt, der uns vorher sagte, unsere Lizenz wäre auf illegalem Weg beschafft worden. Die Funktion `check_success` wird also bereits nicht mehr ausgeführt. Hängt man probeweise ein weiteres `A` an den Input an, erhält man als license check den Wert `0x00400041`. Was man eingibt, wird also via ASCII (`A` = `41` in Hex) übersetzt.

Es muss nun also nur noch stattdessen die Funktion ausgeführt werden, welche die Flag enthält. Dafür müssen wir erst die Adresse der `win`-Funktion finden. Dass diese existiert, sieht man entweder in Ghidra, oder mit `info functions` in GDB:

```shell-session
$ gdb crackme 

(gdb) info functions
All defined functions:

Non-debugging symbols:
0x0000000000401000  _init
0x0000000000401030  strncmp@plt
0x0000000000401040  puts@plt
0x0000000000401050  strlen@plt
0x0000000000401060  printf@plt
0x0000000000401070  gets@plt
0x0000000000401080  exit@plt
0x0000000000401090  sleep@plt
0x00000000004010a0  _start
0x00000000004010d0  _dl_relocate_static_pie
0x00000000004010e0  deregister_tm_clones
0x0000000000401110  register_tm_clones
0x0000000000401150  __do_global_dtors_aux
0x0000000000401180  frame_dummy
0x0000000000401186  close
0x00000000004011b2  check_success
0x0000000000402137  win
0x0000000000401383  main
0x00000000004014b0  _fini
```

Hier sieht man auch die Adressse der Funktion, nämlich `402137`. Um die `win`-Funktion auszuführen, muss nun einfach diese Adresse richtig kodiert als Eingabe übergeben werden. Dafür gibt es unterschiedliche Optionen. Die intuitivste ist wohl, `402137`, also `40`, `21`, und `37`, in ASCII-Zeichen zu übersetzen. Man erhält `@`, `!` und `7`. Diese kann man einfach (in umgedrehter Reihenfolge) dem vorherigen String anhängen:
```python
python -c 'print("LOICENSE" + ("A"*120) + "7!@")' | ./crackme
```

So wird die `win`-Funktion ausgeführt und man erhält man die Flag [`Dreamscape_009_Sound_System`](https://youtu.be/TKfS5zVfGBc):
```shell-session
+-----+ Welcome to the 'HyperCam 2' registration wizard! +-----+
Checking license status...
Your current license status: 'Unregistered HyperCam 2'
Please enter a valid license key: 
Executing license check: 0x00402137...
FLAG{Dreamscape_009_Sound_System}


Thank you for using HyperCam 2. Exiting...
```

#### Alternativer Lösungsweg

Alternativ kann der letzte Schritt auch gelöst werden, indem unter Verwendung von bspw. Python die Zeichen aufgelöst und direkt an das Programm übergeben werden. Dies wäre die angedachte Lösung, würde sich die Adresse nicht "zufällig" im ASCII-Bereich befinden. Es gibt noch weitere Optionen.  

```python
python -c "print('LOICENSE' + ('A'*120) + chr(0x37) + chr(0x21) + chr(0x40))" | ./crackme
```