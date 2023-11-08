Durch das selektive Setzen von Breakpoints konnten wir herrausfinden, dass die main ca. bei der Speicherstelle "0x400ba" ist.
Durch den befehl "x /20i $rip" können wir uns die folgenden die Assembler Instruktionen ausgeben lassen. 

Von interesse sind für uns hier besonders die aufgerufenen Funktionen, in der Hoffnung, dass davon eine die "strcmp" Funktion ist, mit die Eignabe und das Passwort verglichen werden.

Durch den befehlt "nexti" können wir instruktionsweise im code vorrücken, bis die Parameter für die Funktionen in die entsprechenden Register geschrieben werden. Die Register können wir uns dann mit  "x $rsi" ausgeben lassen. 

```c
(gdb) x /20i $rip
=> 0x400c04:	mov    rsi,rdx
   0x400c07:	mov    rdi,rax
   0x400c0a:	call   0x400498
   0x400c0f:	test   eax,eax
   0x400c11:	jne    0x400c78
   0x400c13:	mov    edi,0x1d
   0x400c18:	call   0x41fc20
   0x400c1d:	mov    QWORD PTR [rbp-0x118],rax
   0x400c24:	mov    rax,QWORD PTR [rbp-0x118]
   0x400c2b:	mov    r8d,0x10
   0x400c31:	lea    rcx,[rip+0x91aac]        # 0x4926e4
   0x400c38:	mov    edx,0x1c
   0x400c3d:	lea    rsi,[rip+0x2b84ac]        # 0x6b90f0
   0x400c44:	mov    rdi,rax
   0x400c47:	call   0x400ca2
   0x400c4c:	mov    rax,QWORD PTR [rbp-0x118]
   0x400c53:	add    rax,0x1c
   0x400c57:	mov    BYTE PTR [rax],0x0
   0x400c5a:	mov    rax,QWORD PTR [rbp-0x118]
   0x400c61:	mov    rdi,rax
(gdb) nexti
0x0000000000400c07 in ?? ()
(gdb) nexti
0x0000000000400c0a in ?? ()
(gdb) x /s $rsi
0x6bf340:	"radio_moscow"
```

Geht man so weiter vor finden wir bei der Instruktion 0x400c0a den Wert "radio_moscow" im rsi Register.
Vermutlich handelt es sich dabei um das gesuchte Passwort. Wenn wir unsere Vermutung überprüfen und Wert "radio_moskow" in die Passwort-Abfrage eingeben so wir:

```c
./password_check_9 
Enter password: radio_moscow
FLAG{i can hear the statics}
```

Und damit haben wir das dieswöchige Rätsel wieder einmal gelöst :)
