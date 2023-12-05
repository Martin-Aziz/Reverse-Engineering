# Mit gdb debuggen

### FLAG 1
```
(gdb) disass *flag_1
Dump of assembler code for function flag_1:
   0x0000555555400acc <+0>:	push   %rbp
   0x0000555555400acd <+1>:	mov    %rsp,%rbp
   0x0000555555400ad0 <+4>:	sub    $0x20,%rsp
   0x0000555555400ad4 <+8>:	mov    %fs:0x28,%rax
   0x0000555555400add <+17>:	mov    %rax,-0x8(%rbp)
   0x0000555555400ae1 <+21>:	xor    %eax,%eax
   0x0000555555400ae3 <+23>:	movb   $0x46,-0x20(%rbp) #"F"
   0x0000555555400ae7 <+27>:	movb   $0x4c,-0x1f(%rbp) #"L"
   0x0000555555400aeb <+31>:	movb   $0x41,-0x1e(%rbp) #"A"
   0x0000555555400aef <+35>:	movb   $0x47,-0x1d(%rbp) #"G"
   0x0000555555400af3 <+39>:	movb   $0x7b,-0x1c(%rbp) #"{"
   0x0000555555400af7 <+43>:	movb   $0x64,-0x1b(%rbp) #"d"
   0x0000555555400afb <+47>:	movb   $0x6f,-0x1a(%rbp) #"o"
   0x0000555555400aff <+51>:	movb   $0x20,-0x19(%rbp) #" "
   0x0000555555400b03 <+55>:	movb   $0x6e,-0x18(%rbp) #"n"
   0x0000555555400b07 <+59>:	movb   $0x6f,-0x17(%rbp) #"o"
   0x0000555555400b0b <+63>:	movb   $0x74,-0x16(%rbp) #"t"
   0x0000555555400b0f <+67>:	movb   $0x20,-0x15(%rbp) #" "
   0x0000555555400b13 <+71>:	movb   $0x73,-0x14(%rbp) #"s"
   0x0000555555400b17 <+75>:	movb   $0x74,-0x13(%rbp) #"t"
   0x0000555555400b1b <+79>:	movb   $0x61,-0x12(%rbp) #"a"
   0x0000555555400b1f <+83>:	movb   $0x63,-0x11(%rbp) #"c"
   0x0000555555400b23 <+87>:	movb   $0x6b,-0x10(%rbp) #"k"
   0x0000555555400b27 <+91>:	movb   $0x7d,-0xf(%rbp)  #"}"
   0x0000555555400b2b <+95>:	movb   $0x0,-0xe(%rbp)   #"0"
   0x0000555555400b2f <+99>:	lea    -0x20(%rbp),%rax
   0x0000555555400b33 <+103>:	mov    %rax,%rdi
=> 0x0000555555400b36 <+106>:	callq  0x555555400aaa <print_flag>
   0x0000555555400b3b <+111>:	nop
   0x0000555555400b3c <+112>:	mov    -0x8(%rbp),%rax
   0x0000555555400b40 <+116>:	xor    %fs:0x28,%rax
   0x0000555555400b49 <+125>:	je     0x555555400b50 <flag_1+132>
   0x0000555555400b4b <+127>:	callq  0x5555554008e0 <__stack_chk_fail@plt>
   0x0000555555400b50 <+132>:	leaveq 
   0x0000555555400b51 <+133>:	retq   
End of assembler dump.
Beim dissasemblieren fällt besonders das Setzen eines Nullbits auf. Geschrieben wird aus dem CHAR Raum
Annahme: ein Sting wird geschrieben.
Hex-Werte als Chars ergeben 
movb Analyse
movb ist eine Assembly Anweisung und bewegt Bytes von einer Quelle zu einem Ziel. In unserem Fall müssen wir die Quellen der movb, vom offset <+23> bis <+95>, von Hexadezimal in String umwandeln, um das Flag 
"FLAG{do not stack}" zu erhalten.
```
### FLAG 2
```
 Es gibt eine schleife  die bei Adresse 0x0000000000000b77 beginnt:
   0x0000000000000b77 <+37>:    mov    -0x1c(%rbp),%eax
   0x0000000000000b7a <+40>:    movslq %eax,%rdx
   0x0000000000000b7d <+43>:    mov    -0x18(%rbp),%rax
   0x0000000000000b81 <+47>:    add    %rdx,%rax
   0x0000000000000b84 <+50>:    movzbl (%rax),%eax
   0x0000000000000b87 <+53>:    lea    0x10(%rax),%ecx
   0x0000000000000b8a <+56>:    mov    -0x1c(%rbp),%eax
   0x0000000000000b8d <+59>:    movslq %eax,%rdx
   0x0000000000000b90 <+62>:    mov    -0x18(%rbp),%rax
   0x0000000000000b94 <+66>:    add    %rdx,%rax
   0x0000000000000b97 <+69>:    mov    %ecx,%edx
   0x0000000000000b99 <+71>:    mov    %dl,(%rax)
   0x0000000000000b9b <+73>:    addl   $0x1,-0x1c(%rbp)
In dieser Schleife wird auf jedes Zeichen von FLAG_2 zugegriffen, es modifiziert und dann zurückgespeichert. Die Modifikation beinhaltet das Hinzufügen von 16 (0x10) zum ASCII-Wert des Zeichens, wie durch die Zeile gezeigt wird:
0x0000000000000b87 <+53>:    lea    0x10(%rax),%ecx
Da die Verschlüsselung ein einfacher Caesar-Chiffre mit einer Verschiebung von 16 ist, können wir therotisch den Vorgang umkehren, indem Sie 16 von den ASCII-Werten der Zeichen subtrahieren. aber wir können auch  den Speicherinhalt analysieren  bei der addresse 0x2020c0 findet man den ursprünglichen Wert von FLAG_2
"FLAG{caesar_chiffre}"
```

###  FLAG 3 
```text
### Flag_3
Interpretation:
Es gibt eine for schleife zwischen +73 und +31. In dieser werden die Werte aus dem Array, welcher bei FLAG_3 gespeichert ist, mit einer Bitmaske (0x7f) verundet und die letzten 8 bit (dl) in ein Register gespeichert welches nach dem Ablauf der Schleife die Flag enthält.
Die Schleife läuft 39 mal - erkennbar an den Instruktionen +66...+73

Vorgehen:
Elemente des Arrays bei Flag_3 mit 0x7f verunden und ausgeben lassen.
Daten des arrays durch "x /39xb (char*) FLAG_3"
Verarbeitung erfolgt durch python und ergibt:
"FLAG{don't get high on your own supply}"
```
### FLAG 4
```text
Aufbau ähnlichkeiten zu flag 3.
(for loop, array etc)
xor instruktion 
vermutlich handelt es sich hier also um eine XOR Verschlüsselung.

In den Lösungshinweisen ist vermerkt, das in diesem Falle der Schlüssel 4 Zeichen lang ist die Flagge natürlich mit "FLAG{" beginnt.

lässt man sich also z.B. die nächsten 11 Byte in hexadezimal ausgeben

´ x /11xb (char*) &FLAG_4 ´

so bekommt man Folgende HEX-Werte:
~~~
2D 29 38 34  10 1D 16 01  19 1C 04 
~~~
Wenn wir die ersten vier Werte mit den HexWerten der jeweiligen ASCII Zeichen des Strings "FLAG" kombinieren bekommen wir die Werte:
~~~
6b 65 79 73 
~~~
Als ASCII Character interpretiert ergibt das den Schlüssel: "keys"

Wenn wir nun den Schlüssel "keys" wiederholt auf die verschlüsseklen HEX-Werte mit XOR anwenden, erhalten wir die Werte:
~~~
46 4c 41 47 7b 78 6f 72 72 79 7d
~~~
Interpretiert man diese wieder als ASCII Zeichen erhält man den Text:
~~~
"FLAG{xorry}"


```
### FLAG 5 
```
Indizien:
    Array pointer mit Offset "QWORD PTR [rbp - 0x8]"
    Incrementierender Offset beim beschrieben (add rax 0x1...0xd)
    0x0 Nullbit wahrscheinlich ein String
Annahme: Array wird mit Werten gefüllt.
Untersuchung mit "p /c .." -> FLAG{2+2*2=4}
"FLAG{2+2*2=4}"
```
### FLAG 6
```
Es werden anscheinend drei Hexdatensätze  mit einem Offset von 8 bit in das rax register geschrieben. Dies führt zu der Vermutung, dass die Flag zusammengesetzt wird.

Es gibt 3 Instruktionen die wir untersuchen wollen, 0xd2d , 0xd42, 0xd61.
Untersuchen wir dise 3 Instruktionen mit "x /s" und berücksichtigen wir den "Head" der Instuktionen erhalten wir mit:
0xd2f - "FLAG{the"
0xd44 - " little "
0xd61 - "endian}"
"FLAG{the little endian}"
```

### FLAG 7
```
Der assemblierte Code der Funktion flag_7 zeigt, dass ein Counter mit 23 initialisiert wird und anschließend in einer loop der Inhalt des Arrays von FLAG_7 ausgelesen und in den Speicher geschrieben wird. Der Inhalt wird durch einen rechts-shift versteckt. 
0x0000000000000e23 <+0>:  push   %rbp
0x0000000000000e24 <+1>:  mov    %rsp,%rbp
0x0000000000000e27 <+4>:  sub    $0x10,%rsp
0x0000000000000e2b <+8>:  movl   $0x17,-0xc(%rbp)  //Initialisiert eine Variable mit dem Wert 0x17 (23 als Dezimalzahl)
0x0000000000000e32 <+15>: mov    -0xc(%rbp),%eax
0x0000000000000e35 <+18>: cltq
0x0000000000000e37 <+20>: mov    %rax,%rdi
0x0000000000000e3a <+23>: callq  0x950 <malloc@plt>  //Speicher allozieren
0x0000000000000e3f <+28>: mov    %rax,-0x8(%rbp)  
0x0000000000000e43 <+32>: movl   $0x0,-0x10(%rbp)  // Counter für die Loop wird mit 0 initialisiert
0x0000000000000e4a <+39>: jmp    0xe7d <flag_7+90>  // in Loop springen


 Loop:


0x0000000000000e4c <+41>: mov    -0x10(%rbp),%eax
0x0000000000000e4f <+44>: cltq
0x0000000000000e51 <+46>: lea    0x0(,%rax,4),%rdx  //Offset berechnen entsprechend des counters
0x0000000000000e59 <+54>: lea    0x201200(%rip),%rax   # 0x202060 <FLAG_7> //Adresse von Flag_7 wird geladen
0x0000000000000e60 <+61>: mov    (%rdx,%rax,1),%eax  // Wert von Flag_7 in eax Register schreiben
0x0000000000000e63 <+64>: sar    $0x10,%eax           // rechts shift an Wert von Flag_7 durchführen
0x0000000000000e66 <+67>: mov    %eax,%ecx
0x0000000000000e68 <+69>: mov    -0x10(%rbp),%eax
0x0000000000000e6b <+72>: movslq %eax,%rdx
0x0000000000000e6e <+75>: mov    -0x8(%rbp),%rax
0x0000000000000e72 <+79>: add    %rdx,%rax
0x0000000000000e75 <+82>: mov    %ecx,%edx
0x0000000000000e77 <+84>: mov    %dl,(%rax)  // Wert speichern
0x0000000000000e79 <+86>: addl   $0x1,-0x10(%rbp)  //counter um 1 erhöhen
0x0000000000000e7d <+90>: mov    -0x10(%rbp),%eax
0x0000000000000e80 <+93>: cmp    -0xc(%rbp),%eax
0x0000000000000e83 <+96>: jl     0xe4c <flag_7+41>  //jump if less: loop wird solange wiederholt, wie die Bedingung counter < 23 erfüllt ist


Der Inhalt des Flags lässt sich ermitteln, indem man statisch die Speicheradresse des Arrays findet. Diese ergibt sich aus dem Offset des rip Registers und dem Entry Point der Datei welche man mit dem Befehl "info files" findet. Zudem steht die Adresse netterweise in der folgenden Zeile:
0x0000000000000e59 <+54>: lea    0x201200(%rip),%rax   # 0x202060 <FLAG_7> 

Anschließend können wir den Inhalt des Arrays, mit unserem Wissen, dass es eine Größe von 23 hat, byteweise ausgeben lassen mit dem Befehl:
(gdb) x/23b 0x202060

Wir erhalten:

0x202060 <FLAG_7>:	"\377\377F"
0x202064 <FLAG_7+4>:	"\377\377L"
0x202068 <FLAG_7+8>:	"\377\377A"
0x20206c <FLAG_7+12>:	"\377\377G"
0x202070 <FLAG_7+16>:	"\377\377{"
0x202074 <FLAG_7+20>:	"\377\377f"
0x202078 <FLAG_7+24>:	"\377\377i"
0x20207c <FLAG_7+28>:	"\377\377l"
0x202080 <FLAG_7+32>:	"\377\377l"
0x202084 <FLAG_7+36>:	"\377\377e"
0x202088 <FLAG_7+40>:	"\377\377d"
0x20208c <FLAG_7+44>:	"\377\377 "
0x202090 <FLAG_7+48>:	"\377\377u"
0x202094 <FLAG_7+52>:	"\377\377p"
0x202098 <FLAG_7+56>:	"\377\377 "
0x20209c <FLAG_7+60>:	"\377\377w"
0x2020a0 <FLAG_7+64>:	"\377\377i"
0x2020a4 <FLAG_7+68>:	"\377\377t"
0x2020a8 <FLAG_7+72>:	"\377\377h"
0x2020ac <FLAG_7+76>:	"\377\377 "
0x2020b0 <FLAG_7+80>:	"\377\377\060"
0x2020b4 <FLAG_7+84>:	"\377\377}"

Das Flag lässt sich nun ablesen. GDB erkennt dabei eine Folge von Bytes, die einen String repräsentieren sollen. Die Werte an den 3 Byte großen Speicheraddressen bestehen jeweils aus 2 Bytes als nonprintable ASCII Werte und das dritte Byte ist ein ASCII Character. Zu beachten ist, dass der vorletzte Eintrag 060 aufgrund der führenden 0 auf eine oktal repräsentation für das ASCII Zeichen hindeutet (Dezimalwert von 060 ist 48, entspricht in ASCII einer 0). 

Das Flag ist: FLAG{filled up with 0}
```

