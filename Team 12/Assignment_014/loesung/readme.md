# Disassemblieren mit Radare 2

## Ausführen der Datei mit gdb
```
$ chmod +x number_check_1   #Datei ausführbar machen
$ gdb number_check_1        #Datei mit gdb ausführen

GNU gdb (Ubuntu 9.2-0ubuntu1~20.04.1) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from number_check_1...
(No debugging symbols found in number_check_1)

(gdb) run                   #Datei runnen
Starting program: /home/oleg/Desktop/REE/auf14/number_check_1 
Enter number:
```

## Vorgehen zur Analyse
```
$ r2 number_check_1     #1.Schritt: Ausführen der Datei durch Radare2

[0x000009f0]> aaa       #2.Schritt: Zusätzliche Analysen hinzufügen
[x] Analyze all flags starting with sym. and entry0 (aa)
[x] Analyze function calls (aac)
[x] Analyze len bytes of instructions for references (aar)
[x] Check for objc references
[x] Check for vtables
[x] Type matching analysis for all functions (aaft)
[x] Propagate noreturn information
[x] Use -AA or aaaa to perform additional experimental analysis.

[0x000009f0]> s main    #3.Schritt: Methode der Datei zur Analyse auswählen
[0x00000b0d]> pd        #3.Schritt: Ausführen der Analyse
            ; DATA XREF from entry0 @ 0xa0d
┌ 150: int main (int argc, char **argv);
│           ; var char **var_130h @ rbp-0x130
│           ; var int64_t var_124h @ rbp-0x124
│           ; var int64_t var_114h @ rbp-0x114
│           ; var char *s @ rbp-0x110
│           ; var int64_t canary @ rbp-0x8
│           ; arg int argc @ rdi
│           ; arg char **argv @ rsi
│           0x00000b0d      55             push rbp
│           0x00000b0e      4889e5         mov rbp, rsp
│           0x00000b11      4881ec300100.  sub rsp, 0x130
│           0x00000b18      89bddcfeffff   mov dword [var_124h], edi   ; argc
│           0x00000b1e      4889b5d0feff.  mov qword [var_130h], rsi   ; argv
│           0x00000b25      64488b042528.  mov rax, qword fs:[0x28]
│           0x00000b2e      488945f8       mov qword [canary], rax
│           0x00000b32      31c0           xor eax, eax
│           0x00000b34      e88b020000     call sym.setup
│           0x00000b39      488d85f0feff.  lea rax, qword [s]
│           0x00000b40      488d15760300.  lea rdx, qword str.Enter_number: ; 0xebd ; "Enter number: " ; int64_t arg3
│           0x00000b47      beff000000     mov esi, 0xff               ; int64_t arg2
│           0x00000b4c      4889c7         mov rdi, rax                ; char *arg1
│           0x00000b4f      e8e4010000     call sym.read_password
│           0x00000b54      488d95ecfeff.  lea rdx, qword [var_114h]   ;   ...
│           0x00000b5b      488d85f0feff.  lea rax, qword [s]
│           0x00000b62      488d35630300.  lea rsi, qword [0x00000ecc] ; "%d" ; const char *format
│           0x00000b69      4889c7         mov rdi, rax                ; const char *s
│           0x00000b6c      b800000000     mov eax, 0
│           0x00000b71      e83afeffff     call sym.imp.__isoc99_sscanf ; int sscanf(const char *s, const char *format,   ...)
│           0x00000b76      8b85ecfeffff   mov eax, dword [var_114h]
│           0x00000b7c      3d39050000     cmp eax, 0x539              ; "trlen"
│       ┌─< 0x00000b81      7505           jne 0xb88
│       │   0x00000b83      e872ffffff     call sym.win
│       │   ; CODE XREF from main @ 0xb81
│       └─> 0x00000b88      b800000000     mov eax, 0
│           0x00000b8d      488b4df8       mov rcx, qword [canary]
│           0x00000b91      6448330c2528.  xor rcx, qword fs:[0x28]
│       ┌─< 0x00000b9a      7405           je 0xba1
│       │   0x00000b9c      e87ffdffff     call sym.imp.__stack_chk_fail ; void __stack_chk_fail(void)
│       │   ; CODE XREF from main @ 0xb9a
│       └─> 0x00000ba1      c9             leave
└           0x00000ba2      c3             ret
            ; CALL XREF from sym.xor_print @ 0xc6c
            ; CALL XREF from sym.xor_compare @ 0xd01
┌ 131: sym.xor_crypt (int64_t arg1, char *arg2, size_t arg3, int64_t arg4, uint32_t arg5);
│           ; var uint32_t var_38h @ rbp-0x38
│           ; var int64_t var_30h @ rbp-0x30
│           ; var size_t var_28h @ rbp-0x28
│           ; var char *var_20h @ rbp-0x20
│           ; var int64_t var_18h @ rbp-0x18
│           ; var int64_t var_8h @ rbp-0x8
│           ; var int64_t var_4h @ rbp-0x4
│           ; arg int64_t arg1 @ rdi
│           ; arg char *arg2 @ rsi
│           ; arg size_t arg3 @ rdx
│           ; arg int64_t arg4 @ rcx
│           ; arg uint32_t arg5 @ r8
│           0x00000ba3      55             push rbp
│           0x00000ba4      4889e5         mov rbp, rsp
│           0x00000ba7      48897de8       mov qword [var_18h], rdi    ; arg1
│           0x00000bab      488975e0       mov qword [var_20h], rsi    ; arg2
│           0x00000baf      488955d8       mov qword [var_28h], rdx    ; arg3
│           0x00000bb3      48894dd0       mov qword [var_30h], rcx    ; arg4
│           0x00000bb7      4c8945c8       mov qword [var_38h], r8     ; arg5
│           0x00000bbb      c745fc000000.  mov dword [var_4h], 0
│           0x00000bc2      c745f8000000.  mov dword [var_8h], 0
│       ┌─< 0x00000bc9      eb4d           jmp 0xc18
│       │   ; CODE XREF from sym.xor_crypt @ 0xc21
│       │   0x00000bcb      8b45f8         mov eax, dword [var_8h]
│       │   0x00000bce      4863d0         movsxd rdx, eax
│       │   0x00000bd1      488b45e0       mov rax, qword [var_20h]
│       │   0x00000bd5      4801d0         add rax, rdx
│       │   0x00000bd8      0fb630         movzx esi, byte [rax]
│       │   0x00000bdb      8b45fc         mov eax, dword [var_4h]
│       │   0x00000bde      4863d0         movsxd rdx, eax
│       │   0x00000be1      488b45d0       mov rax, qword [var_30h]
│       │   0x00000be5      4801d0         add rax, rdx
│       │   0x00000be8      0fb608         movzx ecx, byte [rax]
│       │   0x00000beb      8b45f8         mov eax, dword [var_8h]
│       │   0x00000bee      4863d0         movsxd rdx, eax
│       │   0x00000bf1      488b45e8       mov rax, qword [var_18h]
│       │   0x00000bf5      4801d0         add rax, rdx
│       │   0x00000bf8      31ce           xor esi, ecx
│       │   0x00000bfa      89f2           mov edx, esi
│       │   0x00000bfc      8810           mov byte [rax], dl
│       │   0x00000bfe      8345fc01       add dword [var_4h], 1
│       │   0x00000c02      8b45fc         mov eax, dword [var_4h]
│       │   0x00000c05      4898           cdqe
│       │   0x00000c07      483945c8       cmp qword [var_38h], rax
│      ┌──< 0x00000c0b      7707           ja 0xc14
│      ││   0x00000c0d      c745fc000000.  mov dword [var_4h], 0
```
## Analyse
<p>Es gibt zwei cmp Befehle:<br>
0x00000c07      483945c8       cmp qword [var_38h], rax<br>
0x00000b7c      3d39050000     cmp eax, 0x539              ; "trlen"</p>
Der obere Befehl gehört zu sym.xor_crypt (int64_t arg1, char *arg2, size_t arg3, int64_t arg4, uint32_t arg5) und der untere zu int main (int argc, char **argv). Der cmp Befehl in der main beinhaltet eine Hexadezimalzahl 0x539, als Vergleich mit eax. Wandelt man die Hexadezimalzahl in eine Dezimalzahl um, ergibt sie 1337.

## Eingabe der Dezimalzahl als Passwort
```
[Ausführung der Datei durch gdb]
Starting program: /home/oleg/Desktop/REE/auf14/number_check_1 
Enter number: 1337
[Detaching after vfork from child process 6711]
cat: flag: No such file or directory 
#Flag wird durch netcat ausgegeben. Datei gibt wahrscheinlich nur win() aus.
```

## Netcat Eingabe
```
$ nc tank.informatik.hs-mannheim.de 3001
```