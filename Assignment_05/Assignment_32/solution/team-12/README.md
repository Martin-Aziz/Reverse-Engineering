## REE / Prof. Smits / WS 22-23 / Hochschule Mannheim
### Team 12 <br> Names: Mike, Gabriel, Kyrill <br>MatNr.: 1921224, 1925874, 1926420



# Assignment_31

Aufgabe:
Erstellen Sie ein eigenes Reverse Engineering CrackMe.

- Dem kommentierten Quelltext des Crackmes in C.✅
- Einem Makefile, um das Crackme bauen zu können.✅ 
- Ein fertig compiliertes Executable des Crackmes.✅
- Einer Musterlösung für das Crackme Textuelle Beschreibung der Schwachstelle und des Angriffs.✅
- Skript, das die Schwachstelle ausnutzt und das Flag ausgibt.✅


## Musterlösung
Die Musterlösung beschreibt das Vorgehen, wenn es sich um ein unbekanntes CrackMe handeln würde. 


### $ file
Die Datei wurde zunächst mit dem Programm file untersucht. Es handelt sich um eine ausführbare 64-Bit-ELF-Datei, die *dynamisch gelinkt* und *not stripped* ist.
```
$ file crackme_12
crackme_12: ELF 64-bit LSB pie executable, x86-64, version 1 (SYSV), dynamically linked, interpreter /lib64/ld-linux-x86-64.so.2, BuildID[sha1]=b429e7c4e19215f6b7d77fe16d230c648ec5d90f, for GNU/Linux 3.2.0, not stripped
```
---

### $ ./crackme_12

Das Programm `crackme_12` startet und verlangt eine Passworteingabe. Wir wissen, dass die Lösung des CrackMe\`s eine Flag im Format Flag{RandomText} sein muss. 
```
$ ./crackme_12 
Enter the password: test
Incorrect password.
```
Wenn das korrekte Passwort eingegeben ist, müsste das Programm die `Flag` ausgeben.

Da wir auf diesem Weg nur `BruteForcen` können, ist es clever ein Tool wie `ghidra` zu benutzen. 

### ghidra

Das Tool analysiert den Code für uns und gibt folgenden C Code für die `main` Funktion aus. 

#### main()
```
  int iVar1;
  long in_FS_OFFSET;
  char local_32 [5];
  char local_2d [5];
  undefined8 local_28;
  undefined8 local_20;
  undefined2 local_18
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  printf("Enter the password: ");
  __isoc99_scanf(&DAT_00102019,local_32);
  set_and_obfuscate_password(local_2d);
  local_28 = 0x73695f7b47414c46;
  local_20 = 0x7230775f6568745f;
  local_18 = 0x7d64;
  iVar1 = strcmp(local_32,local_2d);
  if (iVar1 == 0) {
    puts((char *)&local_28);
  }
  else {
    puts("Incorrect password.");
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
```
In der `main` Funktion kann man erkennen, dass erstens nach einer Eingabe der Passwortes gefragt wird, und dieses Passwort auf der Variable `local_32` gespeichert wird.

Danach wird durch die Funktion `set_and_obfuscate_password` ein obfuscated Passwort auf der variable `local_2d` gespeichert, das später mit den vom User eingegebenen Passwort mit `strcmp(local_32,local_2d)` verglichen wird.

Schauen wir uns die `set_and_obfuscate_password` Funktion genauer an.

#### set_and_obfuscate_password()
```
  size_t sVar1;
  int local_1c;
  
  *param_1 = 'b';
  param_1[1] = 'h';
  param_1[2] = 'p';
  param_1[3] = 'a';
  param_1[4] = '\0';
  local_1c = 0;
  while( true ) {
    sVar1 = strlen(param_1);
    if (sVar1 <= (ulong)(long)local_1c) break;
    param_1[local_1c] = param_1[local_1c] + (char)local_1c;
    local_1c = local_1c + 1;
  }
  return;
```
Hier kann man erkennen, dass ein String zusammengestellt wird. erstmal mit den Buchstaben `b`,`h`,`p`,`a`. Später werden diese Buchstaben noch durch eine Schleife verändert.

Hier gibt es nun 2 Ansätze wir man versuchen kann das Passwort zu entschlüsseln.
1) Man erkennt durch den Aufbau des Passwortes, dass es sich um 4 Buchstaben handelt, also ein Passwort das sehr kurz ist. Somit kann man mit einer Brute-Force attacke einfach alle möglichen char Werte durchgehen und versuchen das Passwort zu erraten.
2) Man erkennt wie die Schleife funktioniert entschlüsselt hierdurch das Passwrot. Schauen wir uns die Schleife nochmal an, und bennenen die Variablen einfacher:
```
    i = 0;
    while( true ) {
    string_length = strlen(password);
    if (string_length <= i) break;
    password[i] = password[i] + i;
    i = i + 1;
  } 
```
so sieht die Schleife viel verständlicher und einfacher aus. Man kann auch direkt erkennen, dass es eine einfache `for` Schleife ist, die den Buchstaben an der Stelle [i] einen den Wert von [i] addiert und somit in der ACSII Tabelle den Buchstaben verschiebt:
```
password[0] = `b`   --->  `b`+0 = `b`
password[0] = `h`   --->  `h`+1 = `i`
password[0] = `p`   --->  `p`+2 = `r`
password[0] = `a`   --->  `a`+3 = `d`
```
Somit kommen wir auf das Password = `bird`

#### Enter the right password
Jetzt bleibt nur noch das Programm zu starten und als Passwort `bird` einzugeben.
```
$ ./crackme_12
Enter the password: bird
FLAG{_is_the_w0rd}
```


### Flag

Wenn wir dem Programm das richtige Passwort `bird` übergeben erhalten wir die Flagge:
`FLAG{_is_the_w0rd}`
 

## Schwachstelle
Bei der Schwachstelle handelt es sich um eine String-Obfuscation, die das geheime Kennwort im Code verbirgt. Das Passwort wird in einem Char-Array gespeichert und durch eine arithmetische Operation verschleiert. Wenn die Verschleierung entdeckt wird, kann die arithmetische Operation verwendet werden, um den verschleierten Text zu dechiffrieren und das geheime Passwort auslesen.


### CrackMe Code

```
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char *password;
    password = malloc(10);
    printf("Enter the password: ");
    gets(password);

    char correct_password[4];
    correct_password[0] = 'b';
    correct_password[1] = 'h';
    correct_password[2] = 'p';
    correct_password[3] = 'a';
    correct_password[4] = '\0';

    for (int i = 0; i < 4; i++) {
        correct_password[i] = correct_password[i] + i;
    }

    char flag[] = {70, 108, 97, 103, 123, 116, 114, 97, 108, 97, 108, 97, 108, 97, 125, 0};
    
    printf("you entered- %s\n", password);
    printf("it should be- %s\n", correct_password);

    if (strcmp(password, correct_password) == 0) {
        printf("%s\n", flag);
    } else {
        printf("Incorrect password.\n");
    }

    return 0;
}
```

### makefile
Das `makefile` kompiliert unser Programm `crackme_12` und implemntiert einen Stack-Guard `-fstack-protector` der die Executbale vor einem Stack-Smash-Angriff schützt.
```
crackme_12: crackme_12.c
	gcc -fstack-protector crackme_12.c -o crackme_12

clean:
	rm crackme_12
```

### script
Das von uns erstellte Script startet das Programm `crackme_12` und übergibt dem Passwort-Input unser geheimes Passwort `bird`. 

```
import os
from subprocess import Popen, PIPE

p = Popen('./crackme_12', stdin=PIPE, text=True) #NOTE: no shell=True here
p.communicate('bird')
```  