# Lösung: Eigenes Crackme schreiben

## Sicherheitslücke in unserem crackme

Die Sicherheitslücke in unserem `crackme` ist ein buffer overflow durch die Verwendung der unsicheren `gets`-Funktion.

```c
int main() {
    if (check_password() == 1095586632) {
        print_flag();
    } else {
        printf("%s\n", "Falsches Passwort :(");
    }

    return 0;
}
```

In unserer main-Funktion schauen wir, ob die `check_password`-Funktion die korrekte `magic number` zurückgibt. Wenn das der Fall ist, geben wir unsere Flag (`FLAG{Greetings_from_Team_10}`) in der `print_flag()`-Funktion aus. Unsere Flag ist XOR-Verschlüsselt im Programm gespeichert und wird durch den im Programm gespeicherten Key `cr4zy_x0r_key` entschlüsselt. Theoretisch könnte man die Flag mit dem Key auch händisch entschlüsseln, wenn man das Programm bspw. in Ghidra öffnet und diese Werte ausliest. Da die crackmes jedoch **ausschließlich** durch Eingaben gelöst werden sollen, haben wir hier keine weiteren/komplizierteren Verschlüsselungen vorgenommen.

```c
int check_password() {
    int magic_number = 0;
    char input[32];

    gets(input);

    if (hash(input) == password) {
        magic_number = 1095586632;
    };

    return magic_number;
}
```

In der `check_password`-Funktion wird die Eingabe des Nutzers durch `gets` in `input` eingelesen.
Die `gets`-Funktion ist jedoch nicht sicher und ignoriert die Größe von `input`, wodurch ein buffer overflow möglich ist, wenn man zu viele Zeichen eingibt. Dadurch lassen sich die Werte von anderen verwendeten Variablen überschreiben.

Anschließend wird durch die `hash`-Funktion ein Hash vom `input` berechnet und mit dem Passwort-Hash verglichen. Der Hash-Wert des Passworts in unserem Programm ist `6488353955584119754` und entspricht dem Passwort: `Cr4zy_s3cr3t_p4ssword!!!`. Da wir jedoch nur die Hashes vergleichen und niemals das Passwort im Klartext im Programm haben, sollte eigentlich keiner dieses Passwort herausfinden können. (Außer jemand hat zu viel Zeit und brute-forced das Passwort mit unserer `hash`-Funktion).

Wenn das richtige Passwort eingegeben wird und die Hash-Werte übereinstimmen, gibt die Funktion die `magic number: 1095586632` zurück. Bei falschem Passwort wird der Initialwert (0) zurückgegeben.
Hier kommt die Sicherheitslücke ins Spiel. Durch die Eingabe bei `gets` kann man einen buffer overflow verursachen, wodurch man den Wert von `magic_number` zu `1095586632` ändert. Dadurch wird selbst bei falschem Passwort die korrekte `magic number` zurückgegben, wodurch anschließend in der `main`-Funktion `print_flag` aufgerufen wird und die Flag ausgegeben wird.

Die Zahl `1095586632` entspricht dem Hex-Wert `0x414D5348`. Die zugehörigen ASCII-Zeichen davon sind `AMSH`. Bei little endian muss man diese Zeichen umdrehen und somit im `input` an der korrekten Stelle `HSMA` eingeben, damit ein buffer overflow auftritt und der Wert von `magic_number` `auf `1095586632` geändert wird (siehe Vorgehen in der Musterlösung).

Im Repo ist eine `Makefile` und ein Python-Script vorhanden. Mit der `Makefile` kann man mit `make` unser `crackme.c` zu `crackme` compilen. Mit `make clean` wird die gebaute executable wieder entfernt.
Mit dem Python-Script wird das `crackme` einmal mit dem korrekten Passwort und einmal mit dem Input für den buffer overflow ausgeführt. Bei beiden wird anschließend die Ausgabe des Programms in der Konsole ausgegeben, wodurch man die Flag auslesen kann.

## Musterlösung

Zuerst analysiert man das `crackme` mit `Ghidra` und schaut dort die `main-Funktion` an:

```c
undefined8 main(void)
{
    int iVar1;

    iVar1 = check_password();
    if (iVar1 == 0x414d5348) {
        print_flag();
    }
    else {
        puts("Falsches Passwort :(");
    }
    return 0;
}
```

Hier sieht man direkt, dass `check_password` die Zahl `1095586632 (0x414d5348)` zurückgeben muss, damit `print_flag` aufgerufen wird. Als nächstes schaut man deshalb in die `check_passwort`-Funktion:

```c
undefined4 check_password(void)

{
    long lVar1;
    char local_38 [44];
    undefined4 local_c;

    local_c = 0;
    printf("%s","Bitte geben Sie das Passwort ein: ");
    gets(local_38);
    lVar1 = hash(local_38);
    if (lVar1 == 0x5a0b438bbb9793ca) {
        local_c = 0x414d5348;
    }
    return local_c;
}
```

Hier erkennt man, dass `gets` verwendet wird und die eingelesenen Werte in `local_38` zu speichern.
`local_38` ist unser `input` char-Array und hat hier nach dem compilen sogar Platz für 44 Zeichen, obwohl im Programm nur 32 angegeben waren. Da bekannt ist, dass `gets` unsicher ist, kann man versuchen damit ein buffer overflow zu verursachen. Man erkennt hier, dass `0x414d5348` nur dann `local_c` (= `magic_number`) zugewiesen und zurückgegeben wird, wenn der Hash-Wert vom `input` in `local_38` der Zahl `0x5a0b438bbb9793ca` entspricht. Ansonsten wird der Initialwert 0 zurückgegeben. Man könnte nun versuchen, einen buffer overflow zu verursachen und dadurch den benötigten Wert `1095586632 (0x414d5348)` in `local_c` zu schreiben, wodurch auch mit falschem Passwort die korrekte Zahl zurückgegeben wird.

Dafür startet man das Programm in `gdb` um die Werte der einzelnen Variablen vergleichen zu können.
Man kann nach dem Start das Programm direkt abbrechen und mit `bt` den Stack untersuchen:

```c
$ gdb ./crackme
(gdb) r
(gdb) bt

#0  0x00007ffff7e97992 in __GI___libc_read (fd=0, buf=0x5555555596b0, nbytes=1024) at ../sysdeps/unix/sysv/linux/read.c:26
#1  0x00007ffff7e0fcb6 in _IO_new_file_underflow (fp=0x7ffff7f9caa0 <_IO_2_1_stdin_>) at ./libio/libioP.h:947
#2  0x00007ffff7e10e16 in __GI__IO_default_uflow (fp=0x7ffff7f9caa0 <_IO_2_1_stdin_>) at ./libio/libioP.h:947
#3  0x00007ffff7e03613 in _IO_gets (buf=0x7fffffffdb70 "") at ./libio/iogets.c:38
#4  0x00005555555552f0 in check_password ()
#5  0x0000555555555326 in main ()
```

Anschließend schaut man sich die `main`-Funktion an:

```c
(gdb) disas main

Dump of assembler code for function main:
   0x0000555555555314 <+0>:     endbr64
   0x0000555555555318 <+4>:     push   rbp
   0x0000555555555319 <+5>:     mov    rbp,rsp
   0x000055555555531c <+8>:     mov    eax,0x0
   0x0000555555555321 <+13>:    call   0x5555555552ae <check_password>
   0x0000555555555326 <+18>:    cmp    eax,0x414d5348
   0x000055555555532b <+23>:    jne    0x555555555339 <main+37>
   0x000055555555532d <+25>:    mov    eax,0x0
   0x0000555555555332 <+30>:    call   0x5555555551fe <print_flag>
   0x0000555555555337 <+35>:    jmp    0x555555555348 <main+52>
   0x0000555555555339 <+37>:    lea    rax,[rip+0xcee]        # 0x55555555602e
   0x0000555555555340 <+44>:    mov    rdi,rax
   0x0000555555555343 <+47>:    call   0x555555555080 <puts@plt>
   0x0000555555555348 <+52>:    mov    eax,0x0
   0x000055555555534d <+57>:    pop    rbp
   0x000055555555534e <+58>:    ret
```

Hier sieht man bei `<+18>`, dass `eax` mit `0x414d5348` verglichen wird. Das ist der Vergleich aus `main`, bei dem geprüft wird, ob die von `check_password` zurückgegebene `magic_number` tatsächlich `1095586632 (0x414d5348)` enspricht. Hier setzt man deshalb einen breakpoint. Dadurch kann man sich beim Erreichen des breakpoints den Wert von `eax` ausgeben lassen und schauen, ob man durch den buffer overflow tatsächlich die zurückgegebene `magic_number` verändert hat:

```c
(gdb) b *0x0000555555555326
Breakpoint 1 at 0x555555555326
```

Anschließend kann man das Programm starten. In Ghidra hat man gesehen, dass in das input Array 44 Elemente reinpassen. Deshalb gibt man nun 44 "A"-Zeichen ein und anschließend ein "B". Dadurch kann man prüfen, ob ein buffer overflow stattfindet und der Wert der `magic number` geändert wird. Nach erreichen des breakpoints kann man sich dann den Wert von `eax` anzeigen lassen. Normalerweise sollte der Wert 0 sein, da wir nicht das korrekte Passwort eingegeben haben.

```c
(gdb) r
Bitte geben Sie das Passwort ein: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAB
Breakpoint 1, 0x0000555555555326 in main ()
(gdb) p /d $eax
$1 = 66
```

Man erkennt hier, dass der Wert der zurückgegebenen `magic number` 66 ist. 66 ist in Hex `0x42` und entspricht dem ASCII-Zeichen `B`. Man konnte also ein buffer overflow durch `gets` ausnutzen, um den Wert der `magic number` zu ändern. In gdb sieht man auch, dass beim breakpoint mit dem Hex-Wert `0x414D5348` verglichen wird. Man muss also durch die Eingabe den Wert `1095586632 (0x414D5348)` in `eax` speichern, damit die Flag ausgegeben wird. Wie bereits oben erwähnt entspricht `0x414D5348` den ASCII-Zeichen `AMSH`. Durch little endian muss man also `HSMA` an die 44 "A"-Zeichen anhängen, damit durch den buffer overflow die Zahl `1095586632` von `check_password` zurückgegeben wird.

```c
(gdb) r
Bitte geben Sie das Passwort ein: AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHSMA
Breakpoint 1, 0x0000555555555326 in main ()
(gdb) p /d $eax
$1 = 1095586632
(gdb) continue
Continuing.
FLAG{Greetings_from_Team_10}
```

Durch die Eingabe von `AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHSMA` kommt man somit durch einen buffer overflow an die Flag, obwohl das nicht das richtige Passwort ist. Logischerweise können die ersten 44 Zeichen in der Eingabe beliebig gewählt werden.

Mit dem Script `crackme_script.py` kann der String `AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHSMA` automatisch an das crackme übergeben werden und anschließend werden alle Ausgaben des Programms in der Konsole ausgegeben. Dadurch kommt man auch mit dem Script an die Flag. Zusätzlich wird im Script das Programm auch noch mit dem richtigen Passwort `Cr4zy_s3cr3t_p4ssword!!!` aufgerufen, wodurch man auch an die Flag kommt:

```sh
$ python3 crackme_script.py

Using this string for buffer overflow:
AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAHSMA

Output of the crackme with buffer overflow:
Bitte geben Sie das Passwort ein: FLAG{Greetings_from_Team_10}


Using password of the crackme:
Cr4zy_s3cr3t_p4ssword!!!

Output of the crackme with correct password:
Bitte geben Sie das Passwort ein: FLAG{Greetings_from_Team_10}
```
