# Mit gdb debuggen

1. password_check_4 als ausführbare Datei in gdb Debugger laden

````
dennis@dennis-VirtualBox:~/Dokumente/REE$ gdb ./password_check_4
````

2. Executable ausführen. Da wir das Passwort noch nicht kennen, unterbrechen wir die Ausführung an der Stelle um zu analysieren, was das Programm bis dahin macht

````
(gdb) r
Starting program: /home/dennis/Dokumente/REE/password_check_4 
Enter password: ^C 
Program received signal SIGINT, Interrupt.
````

3. Anschließend können wir den Stack analysieren, da das Programm zwar unterbrochen, jedoch nicht beendet wurde

````
(gdb) bt
#0  0x00007ffff7ecffd2 in __GI___libc_read (fd=0, buf=0x7ffff7faea03 <_IO_2_1_stdin_+131>, nbytes=1)
    at ../sysdeps/unix/sysv/linux/read.c:26
#1  0x00007ffff7e52b9f in _IO_new_file_underflow (fp=0x7ffff7fae980 <_IO_2_1_stdin_>) at libioP.h:948
#2  0x00007ffff7e53f86 in __GI__IO_default_uflow (fp=0x7ffff7fae980 <_IO_2_1_stdin_>) at libioP.h:948
#3  0x00007ffff7e4586c in __GI__IO_getline_info (fp=fp@entry=0x7ffff7fae980 <_IO_2_1_stdin_>, buf=buf@entry=0x7fffffffdf00 "", 
    n=n@entry=253, delim=delim@entry=10, extract_delim=extract_delim@entry=1, eof=eof@entry=0x0) at iogetline.c:60
#4  0x00007ffff7e4596c in __GI__IO_getline (fp=fp@entry=0x7ffff7fae980 <_IO_2_1_stdin_>, buf=buf@entry=0x7fffffffdf00 "", 
    n=n@entry=253, delim=delim@entry=10, extract_delim=extract_delim@entry=1) at iogetline.c:34
#5  0x00007ffff7e446ca in _IO_fgets (buf=0x7fffffffdf00 "", n=254, fp=0x7ffff7fae980 <_IO_2_1_stdin_>) at iofgets.c:53
#6  0x0000555555400da2 in read_password ()
#7  0x0000555555400b34 in main ()
````

4. Wir sehen aus dem Backtrace, dass es eine fgets Funktion gibt, mit der vermutlich user input empfangen wird, sowie eine read_password und eine main Funktion. Um uns einen Überblick über das Programm zu verschaffen, disassemblieren wir nun die main Funktion

````
(gdb) disas main
Dump of assembler code for function main:
   0x0000555555400aed <+0>:	push   %rbp
   0x0000555555400aee <+1>:	mov    %rsp,%rbp
   0x0000555555400af1 <+4>:	sub    $0x130,%rsp
   0x0000555555400af8 <+11>:	mov    %edi,-0x124(%rbp)
   0x0000555555400afe <+17>:	mov    %rsi,-0x130(%rbp)
   0x0000555555400b05 <+24>:	mov    %fs:0x28,%rax
   0x0000555555400b0e <+33>:	mov    %rax,-0x8(%rbp)
   0x0000555555400b12 <+37>:	xor    %eax,%eax
   0x0000555555400b14 <+39>:	callq  0x555555400de8 <setup>
   0x0000555555400b19 <+44>:	lea    -0x110(%rbp),%rax
   0x0000555555400b20 <+51>:	lea    0x3b6(%rip),%rdx        # 0x555555400edd
   0x0000555555400b27 <+58>:	mov    $0xff,%esi
   0x0000555555400b2c <+63>:	mov    %rax,%rdi
   0x0000555555400b2f <+66>:	callq  0x555555400d5c <read_password>
   0x0000555555400b34 <+71>:	mov    $0x9,%edi
   0x0000555555400b39 <+76>:	callq  0x555555400990 <malloc@plt>
   0x0000555555400b3e <+81>:	mov    %rax,-0x118(%rbp)
   0x0000555555400b45 <+88>:	mov    -0x118(%rbp),%rax
   0x0000555555400b4c <+95>:	mov    $0x10,%r8d
   0x0000555555400b52 <+101>:	lea    0x384(%rip),%rcx        # 0x555555400edd
   0x0000555555400b59 <+108>:	mov    $0x8,%edx
   0x0000555555400b5e <+113>:	lea    0x2014ab(%rip),%rsi        # 0x555555602010 <PASSWORD>
   0x0000555555400b65 <+120>:	mov    %rax,%rdi
   0x0000555555400b68 <+123>:	callq  0x555555400bc7 <xor_crypt>
   0x0000555555400b6d <+128>:	mov    -0x118(%rbp),%rax
   0x0000555555400b74 <+135>:	add    $0x8,%rax
   0x0000555555400b78 <+139>:	movb   $0x0,(%rax)
   0x0000555555400b7b <+142>:	mov    -0x118(%rbp),%rdx
   0x0000555555400b82 <+149>:	lea    -0x110(%rbp),%rax
   0x0000555555400b89 <+156>:	mov    %rdx,%rsi
   0x0000555555400b8c <+159>:	mov    %rax,%rdi
   0x0000555555400b8f <+162>:	callq  0x555555400970 <strcmp@plt>
   0x0000555555400b94 <+167>:	test   %eax,%eax
   0x0000555555400b96 <+169>:	jne    0x555555400b9d <main+176>
   0x0000555555400b98 <+171>:	callq  0x555555400ada <win>
   0x0000555555400b9d <+176>:	mov    -0x118(%rbp),%rax
   0x0000555555400ba4 <+183>:	mov    %rax,%rdi
   0x0000555555400ba7 <+186>:	callq  0x5555554008d0 <free@plt>
   0x0000555555400bac <+191>:	mov    $0x0,%eax
   0x0000555555400bb1 <+196>:	mov    -0x8(%rbp),%rcx
--Type <RET> for more, q to quit, c to continue without paging--q
Quit
````

5. Aus der disassemblierten main sehen wir, dass nach der read_password Funktion über malloc Speicher auf dem Heap reserviert wird, um das eingegebene Passwort des Users zu speichern. Das Passwort des Users wird verschlüsselt und mit einem Offset zum Basepointer gespeichert. Anschließend wird es mit einer xor_crypt Funktion entschlüsselt und auf dem Heap gespeichert. Nach der Entschlüsselung wird das eingegebene Passwort mit dem erwarteten Passwort in der string-compare (strcmp) Funktion verglichen und das Ergebnis in das eax-Register geschrieben. Wenn die beiden Strings gleich sind müsste dort der Wert 0 stehen. Ist dies der Fall und das Passwort richtig, wird die win-Funktion aufgerufen und der allocierte Speicher mit free freigegeben. Um das Passwort rauszufinden sehen wir uns die strcmp Funktion genauer an und welche Strings verglichen werden:

```
   0x0000555555400b82 <+149>:	lea    -0x110(%rbp),%rax
   0x0000555555400b89 <+156>:	mov    %rdx,%rsi
   0x0000555555400b8c <+159>:	mov    %rax,%rdi
   0x0000555555400b8f <+162>:	callq  0x555555400970 <strcmp@plt>
```

Wir sehen, dass die Adresse -0x110(%rbp), also das Offset des Basepointer, an der das eingegebene Passwort gespeichert wird zunächst mit lea ins rax-Register geschrieben und der Inhalt anschließend mit move in das rdi-Register geschrieben wird. Das zweite Argument, das der strcmp-Funktion übergeben wird, wird aus dem rdx-Register in das rsi-Register geschrieben wird. Das bedeutet, dass wir das richtige Passwort aus dem rsi-Register auslesen können

6. Breakpoint an strcmp setzen und Executable ausführen

```
(gdb) r
The program being debugged has been started already.
Start it from the beginning? (y or n) y
Starting program: /home/dennis/Dokumente/REE/password_check_4 
Enter password: 123

Breakpoint 1, 0x0000555555400b8f in main ()
```

7. Passwort auslesen indem wir das rsi-Register analysieren und den String daraus auslesen

```
(gdb) x/s $rdi
0x7fffffffdf00:	"123"
(gdb) x/s $rsi
0x5555556032a0:	"mutti123"
```

8. Flag erhalten

```
dennis@dennis-VirtualBox:~/Dokumente/REE$ nc tank.informatik.hs-mannheim.de 3006
Enter password: mutti123
FLAG{xor_or_not_to_xor}
```


