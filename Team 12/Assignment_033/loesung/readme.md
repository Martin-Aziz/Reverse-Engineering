# Aufgabe 33 Team 12 

# Team 01
In diesem Code ruft die Funktion "Main" eine Validierungsmethode auf, die einen String mit ausschließlich Hexadezimalzeichen akzeptiert. Die Validierungsmethode sieht wie folgt aus:
```c
void validate(char *someString)
{
  undefined relevant;
  undefined local_3a;
  undefined local_39;
  undefined local_38;
  char userInput[25];
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
  printf("Geben Sie den geheimen Code ein: ");
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
  xorHexPairs(someString, &relevant);
  return;
}

```
Das Programm liest eine Nutzereingabe ein, konvertiert sie in eine Zahl, interpretiert sie als Gray-Code, verschiebt sie und übergibt sie dann an die Funktion "xorHexPairs".
```c
void xorHexPairs(char *someString, long someXorShift)
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
      __isoc99_sscanf(&hexInput, &DAT_00100bc8, &hexOutput);
      shifted = (uint)*(char *)(someXorShift + (i / 2) % 4);
      result = hexOutput ^ shifted;
      putchar(result);
    }
  }
  return;
}
```
Diese Funktion verwendet den String aus der "main"-Funktion und den verschobenen Userinput als Shifting-Parameter für eine Reihe von Operationen auf dem String. Das Ziel besteht darin, eine Eingabe zu finden, die den String dekodiert. Um den gesuchten Schlüssel zu finden, wird eine Known Plaintext Attacke angewendet, indem die ersten Bytes des Strings mit "FLAG{" xor'ed werden. Dies genügt, da der Schlüssel maximal 4 Zeichen lang ist. Das Ergebnis ist "lotrl", und es wird festgestellt, dass der Schlüssel sich wiederholt.

Theoretisch könnte man den String direkt mit 2a233535171b1c17153015000930001307061a15331b1c1733071b100e060001331b1b2d051c111c0b0e061611 ^ lotrlotrlotrlotrlotrlotrlotrlotrlotrlotrlotrl = FLAG{they_are_taking_the_hobbits_to_isengard} berechnen. Allerdings wird dies als langweilig angesehen und ist möglicherweise nicht erlaubt, da das direkte Extrahieren aus dem Programm nicht gestattet ist.
### Konstruktion des Eingabeparameters
Um die Variable "on" zu überschreiben, muss ein Buffer Overflow verwendet werden. Hierfür müssen zunächst 25 beliebige Zeichen und dann einige Ziffern eingegeben werden (atoi). Beginnend von hinten wird der String aus der "validate"-Funktion mit dem i-ten Zeichen des Schlüssels xor'ed, daher muss in "on" "lotr" geschrieben werden. Dafür wird "lotr" in Hex umgewandelt (6C 6F 74 72), dann in Graycode (1011010010110001100111001001011) und schließlich wieder in eine Dezimalzahl (1515769419) geparsed.

Daher ergibt sich:
```console
./crackme
Geben Sie den geheimen Code ein: AAAAAAAAAAAAAAAAAAAAAAAAA1515769419
FLAG{they_are_taking_the_hobbits_to_isengard}
```
# Team 2 
Am bearbeitung 
# Team 3 
Mann kann Bufferoverflow beim strcpy ausnutzen,  können wir einfach 14 Zeichen eingeben.

"AAAAAAAAAAcheat" --> buffer overflow beim strcpy vom username in den 10er buffer

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
#  Team 04

Der Code ist zu lange .deswegen werden wir es nicht hinzufügen.
Es gibt jedoch eine Funktion namens "shuffle" in der Hauptmethode, die das erste Zeichen eines Strings durch das letzte ersetzt (und dann tauscht), das zweite durch das vorletzte usw.

Wenn wir diesen Vorgang manuell auf die angegebenen Hexadezimalwerte anwenden, erhalten wir nicht die Flagge, sondern stattdessen:
I_know_Y0U_C4nt_Crack_it wird zu ti_kcarC_tn4C_U0Y_wonk_I

Die Funktion encrypt() verschlüsselt den angegebenen String mit einer Caesar-Verschiebung um 10. Die Funktion encryptDecrypt() verschlüsselt jedes Zeichen eines Strings mit 0x4b. Die Funktion decrypt() verwendet den gleichen Code wie team_03, übergibt jedoch einige zusätzliche Parameter. Auch hier wird eine Caesar-Chiffre implementiert.

Daher können wir das umgekehrte Passwort durch eine Caesar-Verschlüsselung um 10 verschlüsseln und erhalten ds_umkbM_dx4M_E0I_gyxu_S, was die Eingabe für das Passwort ist.

```console
┌──(mindh㉿TT)-[//Desktop]
└─$
Enter the password: ds_umkbM_dx4M_E0I_gyxu_S
4Ole�Flag{Humpty Shuffly BOOO}
## Flag
Flag{Humpty Shuffly BOOO}
```

# Team 5 
Ein dreistufiges CTF, bei dem mehrere Eingaben erforderlich sind, um die Flagge zu erhalten. (Oder man schaut einfach in den Code..)

Stufe 1:
Bufferüberlauf auf zwei Variablen, die "ScoobyDo" ergeben müssen.

Stufe 2:
Malloc muss null zurückgeben, daher muss zu viel Speicher allokiert werden; einfach eine sehr große Zahl eingeben (siehe Skript).

Stufe 3:
Zeichen müssen 2024 ergeben, wenn man die charCodes addiert. Der String muss mit einem Nullbyte enden (oder genau 21 Zeichen lang sein). Wir verwenden 16-mal das Zeichen 'x' (120) und einmal 'h' (104), und erhalten 2024 in unter 21 Zeichen (plus ein Nullbyte).
```python
from pwn import *

pty = process.PTY
p = process("./team_05", stdin=pty, stdout=pty)
# p = remote("tank.informatik.hs-mannheim.de", 3105)
# context.log_level = 'debug'

p.sendlineafter(b":", b"AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAScoobyDo")
p.sendlineafter(b"!", b"99999999999999999999999")
p.sendlineafter(b"...", b"xxxxxxxxxxxxxxxxh\x00")  # 2024 = 16 * 120 + 104 

# p.recvuntil("FLAG{")
flag = p.recvall().decode()

print(flag)
## Flagge
FLAG{scooby_dooby_doo_where_are_you?}
````
# Team 6 
```python
  for (i = 0; i < 6; i = i + 1) {
    for (inputNum = 0; inputNum < 6; inputNum = inputNum + 1) {
      if (drawnNumbers[i] == *(byte *)((long)&eingabe + (long)inputNum)) {
        correctNumbers = correctNumbers + 1;
      }
    }
  }
```
In dieser Schleife wird nicht überprüft, ob eine Ziffer doppelt in der Eingabe vorkommt. Daher kann man einfach 6-mal dasselbe Zeichen einfügen und mehrmals versuchen, bis die Zahl dabei ist (die dann 6-fach gewertet wird).

Wir verwenden hier ****** (42)
```python
from pwn import *

while True:
    # pty = process.PTY
    # p = process("./team_06", stdin=pty, stdout=pty)
    p = remote("tank.informatik.hs-mannheim.de", 3106)

    p.sendlineafter(b": ", b"******")
    flag = p.recvall().decode()
    print(flag, "FLAG{" in flag)
    if "FLAG{" in flag:
        print("hat funktioniert", flag)
        break
```
#### Flag
FLAG{LuckyNumberSlevin} 

# Team 7 
```c
/*
 * Funktion zur Verarbeitung der Benutzereingabe.
 * Die Funktion enthält eine Schleife, die auf Benutzereingaben wartet und entsprechende Aktionen ausführt.
 */

void handleUserInput(void)
{
  int iVar1;
  size_t sVar2;
  char userInput[112]; // Puffer zur Speicherung der Benutzereingabe
  
  while (true) {
    do {
      // Benutzer zur Eingabe auffordern
      printf("\n[Narrator] Was beabsichtigen Sie zu tun?\n> ");
      fgets(userInput, 100, stdin);
      
      // Zeilenumbruch entfernen, falls vorhanden
      sVar2 = strcspn(userInput, "\n");
      userInput[sVar2] = '\0';
    } while (userInput[0] == '\0');

    // Vergleich der Benutzereingabe mit verschiedenen Befehlen und Ausführung der entsprechenden Funktion
    iVar1 = strcmp(userInput, "ask");
    if (iVar1 == 0) {
      ask();
    } else {
      iVar1 = strcmp(userInput, "give");
      if (iVar1 == 0) {
        give();
      } else {
        iVar1 = strcmp(userInput, "The Grinch");
        if (iVar1 == 0) {
          askGrinch();
        } else {
          iVar1 = strcmp(userInput, "Narrator");
          if (iVar1 == 0) {
            askNarrator();
          } else {
            iVar1 = strcmp(userInput, "leave");
            if (iVar1 == 0) {
              leave();
            } else {
              iVar1 = strcmp(userInput, "guess");
              if (iVar1 == 0) {
                guess();
              } else {
                // Fehlermeldung bei unbekannter Eingabe
                printf("[Narrator] Sie können '%s' unmöglich wollen! Oder doch?\n", userInput);
                printf("Segmentation fault (core dumped)");
                return;
              }
            }
          }
        }
      }
    }
  }
}
```
Ghidra offenbart hier eine undurchsichtige Methode, die mehrere Vergleiche durchführt und auf Grundlage dieser Vergleiche verschiedene Funktionen aufruft. Innerhalb dieser Funktionen fällt sofort auf, dass ein Strukt existiert, das den Grinch repräsentieren soll. Die in diesem Strukt gespeicherten Werte erscheinen jedoch nicht besonders aufschlussreich und können nicht direkt genutzt werden, um eine Flag auszugeben. Neben den sichtbaren Befehlen wird bei einer kurzen Analyse deutlich, dass das Programm weitere Fälle unterscheiden kann. Diese werden nun genauer betrachtet.

Die Funktion `ask()` scheint eine Benutzereingabe einzulesen, diese anschließend mit etwas zu vergleichen und dann einen Check auf ein Feld des Grinch auszuführen. Falls dieser Wert größer als 3000 ist, wird ein geheimer Wert ausgegeben.

### The Grinch
```c
/*
 * Die Funktion askGrinch() wird aufgerufen, wenn der Spieler mit dem Grinch interagieren möchte.
 * Der Grinch fordert den Spieler auf, ihm etwas zu geben ("present"). 
 * Bei korrekter Eingabe und einer geheimen Zahl (magicNum) von 0x1337 werden bestimmte Aktionen ausgeführt.
 * Diese umfassen das Löschen des Inhalts einer Datei (pseudo Flag) und Manipulation von theGrinch.
 * Andernfalls wird der Spieler für eine kurze Zeit pausiert.
 */

void askGrinch(void)
{
  int comparisonResult;
  size_t nullCharPos;
  char userInput[108]; // Puffer für Benutzereingabe
  int magicNum;

  // Grinch spricht den Spieler an und fordert nach einem Geschenk ("present")
  printf("[The Grinch] Was möchtest du von mir? Ich muss Weihnachten stehlen! Wenn ich mich nur an meinen Lieblingsspruch erinnern könnte..\n> ");
  
  // Benutzereingabe einlesen und Zeilenumbruch entfernen
  fgets(userInput, 0x73, stdin);
  nullCharPos = strcspn(userInput, "\n");
  userInput[nullCharPos] = '\0';
  
  // Vergleich mit dem erwarteten Wert "present" und einer geheimen Zahl
  comparisonResult = strcmp(userInput, "present");
  if ((comparisonResult == 0) && (magicNum == 0x1337)) {
    // Aktionen bei korrekter Eingabe und geheimer Zahl
    puts("[The Grinch] Oh, du hast etwas für mich gestohlen? Sehr gut! Warte.. ich glaube, ich erinnere mich!");
    puts("[The Grinch] Ich habe es in eine Geschenkbox in diesem Stapel von Boxen gelegt! Moment mal..");
    sleep(2);
    puts("[The Grinch] Gefunden!");
    deleteFileContents(&DAT_001029d3);
    theGrinch = theGrinch + 1000;
    puts("[The Grinch] ...");
    puts("[The Grinch] Teilen? Warum sollte ich das jemals tun? Es ist MEIN Lieblingsspruch.");
    theGrinch = theGrinch + -2;
  }
  else {
    // Aktionen bei inkorrekter Eingabe oder geheimer Zahl
    printf("[The Grinch] '%s'? Wirklich? Musstest du mich damit belästigen? Weißt du was, ich denke, du machst eine Pause."
           ,userInput);
    theGrinch = theGrinch + -1000;
    sleep(5);
  }
  return;
}
```
### Buffer-Overflow
Der durch einen  Buffer beim strcpy verursacht wird. Das Userinput-Array ist auf eine Länge von 100 begrenzt, jedoch werden 115 Zeichen geschrieben. Anschließend wird mit strcmp überprüft, ob der Userinput "present" war und ob eine geheime Zahl von 0x1337 übereinstimmt. Dies kann erreicht werden, indem der Buffer-Overflow nach den Buchstaben "present" mit \x00 terminiert wird, während zusätzliche Bytes übergeben werden.
Der Grinch ruft dann die Funktion "deleteFileContents()" auf, die einen Dateinamen übergeben bekommt. Der Name der Methode ist absichtlich irreführend gewählt. Bei erstmaligem Aufruf lädt die Methode nicht die Flag, sondern xor'ed jeden Wert in einem Byte-Array mit 0x10 und setzt dies als die Flag im Gehirn des Grinches. Bei einem zweiten Aufruf mit dem gleichen Exploit wird die tatsächliche Flag geladen. Dies soll sicherstellen, dass Löser der Aufgabe den gesamten Code lesen, bevor sie ihn ausführen. In der realen Welt hätte ein Angreifer beliebigen Code in dieser if-Bedingung verbergen können, daher dient dies der Sensibilisierung.
Durch das Abrufen der Flag werden positive Erinnerungen im Grinch hervorgerufen, was dazu führt, dass sein Herz wächst. Dies ist eine Voraussetzung dafür, dass die Flag ausgegeben wird.
Der Spieler versucht, ein Geheimnis vom Grinch zu erfahren, indem er eine "beliebige" Zahl errät, die durch eine unseeded rand()-Funktion generiert wird. Die Funktion verwendet immer den Seed 0, wodurch auf allen Plattformen der gleiche Startwert erzeugt wird. Wenn der Spieler es nicht schafft, diesen Exploit zu nutzen, muss er von vorne beginnen, und Versprechen müssen eingehalten werden. Es wird kein Code angezeigt, da nur die rand()-Funktion von Bedeutung ist.
Nachdem der Spieler das Geheimnis des Grinch herausgefunden hat, kann er den Grinch ansprechen und ihm das Geheimnis nennen. Dabei muss der Spieler jedoch einen weiteren geheimen Wert übergeben, der durch die Funktion christmasMagic(int x, int y, int z) berechnet wird (x + y). Vorher erfolgt eine Überprüfung des geheimen Kennworts, dem Namen des Haustiers des Grinches. Der Spieler muss dieses Kennwort erneut mit einem Exploit der strcmp-Methode übergeben, wobei die christmasMagic()-Funktion den gewünschten Wert berechnet. Nach erfolgreichem Abschluss gibt der Grinch seine Flag oder das YouTube-Video aus und beendet das Spiel.
```c
int christmasMagic(uint x,uint y,uint z)

{
  return (~x & z) * 3 +
         ((~(z ^ x) +
          ((((~(y | x) * 4 + (((y & ~x) * 4 - (y ^ x)) - (y | x))) - ~(y ^ x)) - ~y) - (~y | x)) + 1
          + x * 6 + ~z * 5) - (x | z)) + ~x * -2 + ~(z | x) * -4 + (x & ~z) * -4;
}
```
Der Ausdruck in der Funktion christmasMagic wird zunächst möglicherweise nicht als Mixed-Boolean-Algebra-Ausdruck erkannt. Durch die Erstellung eines Karnaugh-Diagramms wird jedoch deutlich, dass es sich um eine triviale Addition handelt, und die Schaltung wird zu einem einfachen "return x + y" vereinfacht. Somit berechnet die christmasMagic-Funktion lediglich eine einfache Addition.
FLAG{Road Runners can't read and don't drink. Meep meep! Honig, Fenster, Balkon, Brot, Frühling, Gardinen}

# Team 8

Um das crackme zu lösen schauen wir uns die passCheck Funktion an, die in der main aufgerufen wird.

```c
void passCheck(long param_1)

{
  char local_68 [84];
  int local_14;
  int *local_10;
  
  local_14 = 0;
  local_10 = &local_14;
  puts("You shall not pass! ");
  printf(*(char **)(param_1 + 8));
  printf("\nPsst, don\'t look: %p\n",secret);
  printf("Did you hear something?");
  gets(local_68);
  if (*local_10 != 0) {
    win();
  }
  return;
}
```
Zunächst wird ein char array local_68 wird mit 84 Bytes angeleget
Danach wird die die variable local_14 und der pointer local_10 angelegt.
local_10 zeigt auf den Inhalt von local_14.
in local_68 wird der user input gespeichert. da fgets benutzt wird, können wir einen buffer overflow nutzen um in local_14 zu schreiben.
Wenn wir einen Wert != 0 in local_14 schreiben wird die win() Funktion aufgerufen und die Flag ausgegeben
```console
echo -ne "AAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAAA" | ./crackme

You shall not pass!
Psst, don't look: 0x56455de0071a
Did you hear something?FLAG{Format Is Important}
```
#  Team 09

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Funktion zum Verschlüsseln des Strings mit einer Caesar-Cipher
void encrypt(char* str, int key);

// Funktion zum Durchführen einer XOR-Verschlüsselung
void xor_crypt(void* dest, void* src, long size, void* key, long key_size);

// Funktion zum Ausgeben eines Arrays von Bytes
void print_array(void* arr, long size);

// Globale Variable 'key'
undefined key[4] = "frp";

// Hauptfunktion
undefined8 main(void) {
  int cmpresult;
  size_t keylength;
  long in_FS_OFFSET;
  undefined key[4];
  int local_60;
  int local_5c;
  void* someBuff;
  undefined2 magic;
  undefined local_49;
  undefined userInput[40];
  long canary;

  // Speichere den aktuellen Stack-Schutzwert
  canary = *(long*)(in_FS_OFFSET + 0x28);

  // Initialisierung von lokalen Variablen
  local_60 = 0x13;
  keylength = strlen(::key);
  local_5c = (int)keylength;
  someBuff = malloc(0x13);
  magic = 0x7266;
  local_49 = 0x70;

  // Initialisiere den userInput-Array mit Nullen
  memset(userInput, 0, 0x20);

  // Benutzereingabe für die Nachricht
  printf("Enter message: ");
  __isoc99_scanf(&readString, userInput);

  // Benutzereingabe für den Schlüssel
  printf("Enter key: ");
  __isoc99_scanf(&readDouble, key);

  // Länge des magischen Strings (constant "frp")
  keylength = strlen((char*)&magic);

  // Verschlüssele den magischen String
  encrypt((char*)&magic, (int)keylength);

  // Vergleiche den verschlüsselten String mit "secure"
  cmpresult = strcmp((char*)&magic, "secure");

  // Überprüfe das Ergebnis des Vergleichs
  if (cmpresult == 0) {
    // Führe XOR-Verschlüsselung durch
    xor_crypt(someBuff, crypt, (long)local_60, ::key, (long)local_5c);

    // Gib das verschlüsselte Array aus
    print_array(someBuff, (long)local_60);
  } else {
    puts("Done.");
  }

  // Überprüfe den Stack-Schutzwert
  if (canary != *(long*)(in_FS_OFFSET + 0x28)) {
    // Stack-Schutzfehler: Beende das Programm
    __stack_chk_fail();
  }

  // Erfolgreiches Beenden des Programms
  return 0;
}
```
magic and local have the string "frp" (fr + p), and user input is appended to it in the encrypt function. Subsequently, the string is encrypted using a Caesar cipher with a shift of 13. Our objective is to ensure that the user input, combined with "frp," results in the word "secure." This is achievable because shifting "frp" by 13 yields "sec," and we only need to insert "ure." To accomplish this, we perform an additional shift of 13 (Double ROT13), resulting in "her."
 
Nach der Eingabe:  
```bash
./crackme
Enter message: her
Enter key: 13
FLAG{the_real_flag}
```
 
erhalten wir die Flag.
## Flag  
FLAG{LuckyNumberSlevin}


# Team 10
Man muss zwei Eingaben  machen, einmal für Länge des Zauberspells (%d), dann einmal für Name des Zauberspells (%s).
 Relevante Stelle
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

Das Spiel liest eine Eingabe (spellInput) ein, fügt ein Nullbyte hinzu und kopiert diese Eingabe dann in einen 20-Byte großen Buffer (spellName), der über dem Stack mit dem Damage und den Boss-HP liegt. Durch einen gezielten Buffer-Overflow können wir diese Werte einfach überschreiben.
Ein erster Ansatz könnte sein, die Boss-HP direkt auf 0 zu setzen. Dies funktioniert jedoch nicht, da die Funktion `strcpy` den Buffer kopiert und beim ersten Nullbyte stoppt. Somit würden wir nicht die Boss-HP überschreiben können. Stattdessen schreiben wir direkt einen negativen Wert in den Speicher (0xFFFFFFFF). Da noch eins abgezogen wird, erreichen wir -2. Die Ausgabe lautet daher:


```console
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
```python
# Importieren der pwn-Bibliothek für Exploitation-Aufgaben
from pwn import *

# Verwendung von PTY (Pseudo Terminal) für die Prozesskommunikation
pty = process.PTY

# Starten des Prozesses "crackme" mit PTY als stdin und stdout
p = process("./crackme", stdin=pty, stdout=pty)

# Senden der Zeichenkette "100" gefolgt von der Eingabe ": " an den Prozess
p.sendlineafter(b": ", b"100")

# Senden einer manipulierten Zeichenkette mit einem Buffer Overflow an den Prozess
p.sendlineafter(b": ", b"qqqqqqqqqqqqqqqqqqqqqqqq\xAA\xAA\xAA\xAA")

# Empfangen aller Ausgabedaten des Prozesses und Dekodieren der Zeichenkette
flag = p.recvall().decode()

# Ausgabe der erhaltenen Flagge
print(flag)

```

FLAG{Y0u_4r3_4_W1z4rd_H4rry}


# Team 11 
Main Methode 
```c
// Initialisierung von Variablen und Puffern
undefined *puVar1;
int iVar2;
time_t tVar3;
size_t sVar4;
char random_number[10];                // Puffer für zufällige Zahlen
char string_buffer_overflow[10];       // Puffer für Eingabeüberlauf
undefined8 local_4e;
undefined2 local_46;
undefined local_44;
char strcmp_condition_1[10];           // Puffer für den Vergleichszweck 1
char local_39;
char *local_28;
int local_20;
ulong strcmp_condition_2;
// Setup-Funktion aufrufen
setup();

// Aktuelle Zeit abrufen und als Seed für den Zufallszahlengenerator verwenden
tVar3 = time((time_t *)0x0);
srand((uint)tVar3);

// Zufallszahl für den Vergleich generieren
strcmp_condition_2._0_4_ = genRandomSuperKey(0x14);
// Überprüfung, ob es sich um einen Bot handelt
local_20 = checkIfRobot();
if (local_20 == 0) {
   // Benutzer ist kein Bot

   // Benachrichtigung und Initialisierung von Werten
   putchar(10);
   local_4e = 0x20656d6f636c6557;
   local_46 = 0x7325;
   local_44 = 0;
   printf("Geben Sie Ihren Namen ein [max. 9 Zeichen]: ");

   // Eingabezeichenfolge über Pufferüberlauf einlesen
   fgets(string_buffer_overflow, 255, stdin);
   fgets(string_buffer_overflow, 255, stdin);
   printf((char *)&local_4e, string_buffer_overflow, (ulong)(uint)strcmp_condition_2);
   local_39 = '\0';

   // Überprüfung der eingegebenen Zeichenfolge mit dem geheimen Wert "chipichipi"
   iVar2 = strcmp(strcmp_condition_1, string_to_win);
   if (iVar2 == 0) {
     // Benutzer hat geheime Zeichenfolge erraten
     puts("\nHerzlichen Glückwunsch, Sie haben einen geheimen Bereich betreten");
     printf("Raten Sie, an welche Zahl ich denke [0-20]: ");

     // Eingabe für die geheime Zahl und Vergleich
     __isoc99_scanf("%s", string_buffer_overflow);
     sprintf(random_number, "%d", (ulong)(uint)strcmp_condition_2);
     iVar2 = strcmp(random_number, string_buffer_overflow);

     if (iVar2 == 0) {
        // Benutzer hat die geheime Zahl erraten
        puts("\nHallo Boss");
        win();
        putchar(10);
     } else {
        // Falsche Zahl eingegeben
        puts("\nWas für eine kluge Vermutung");
        printf("Hier ist Ihre Flagge: ");
        puVar1 = KEY;
        sVar4 = strlen(FLAG);
        local_28 = (char *)xor_decrypt(FLAG, sVar4 & 0xffffffff, puVar1);
        printFlag(local_28);
        putchar(10);
     }
   } else {
     // Falsche geheime Zeichenfolge eingegeben
     puts("\nDiese APP befindet sich in Bearbeitung, versuchen Sie es später erneut...");
   }
} else {
   // Bot erkannt
   puts("BOT");
}
return 0;
```
### 1 Eingabe
Bei der ersten Eingabe in der checkIfRobot Funktion ist eine mathematische Aufgabe zu lösen. Hierbei werden zufällig zwei Zahlen im Bereich von 1 bis 100 ausgewählt, sowie ein zufälliger Operator (+, -, *). Diese Eingabe dient wahrscheinlich als Captcha, um Brute-Force- oder Fuzzing-Angriffe mittels eines Skripts zu verhindern. Sobald die korrekte Lösung eingegeben wurde, wird der Benutzer zur nächsten Eingabe weitergeleitet.
```bash
$ ./crackme
Solve this test: 97 - 6 = 91

Type your name [max 9 chars]:
```
### 2 Eingabe
Die zweite Eingabe weist eine Schwachstelle im Puffer auf, da mittels `fgets(string_buffer_overflow, 255, stdin);` 255 Zeichen eingelesen werden, während das Ziel nur Platz für 10 Zeichen bietet.

Die Variable `char string_buffer_overflow[10];` wird zunächst mit den Werten "9889988998" gefüllt. Danach wird der 11 Zeichen lange String "Welcome %s\0" erstellt, bestehend aus den Variablen `undefined8 local_4e;`, `undefined2 local_46;` und `undefined local_44;`, welche mit den Werten "89898989887" gefüllt werden. Schließlich wird `char strcmp_condition_1[10];` mit dem Wert "tiatatiaop" aus der globalen Variable `string_to_win`, die im `strcmp` verwendet wird, belegt.

Zusammen ergibt sich für die zweite Eingabe die Zeichenfolge "988998899889898989887tiatatiaop", um Zugang zur letzten Eingabe im "geheimen Bereich" zu erhalten.
```bash
$ ./crackme
Solve this test: 97 - 6 = 91

Type your name [max 9 chars]: 988998899889898989887tiatatiaop
12345678901chipichipi

Congrats you entered a secret area
Guess what number I am thinking of [0-20]:
```
### Eingabe 3 

Es befindet sich im vorher betrachteten Codeabschnitt die folgende Zeile:
```c
printf((char *)&printed_string, user_input, (ulong)rand_value);
```
Da printed_string ebenfalls im überschreibbaren Abschnitt liegt, ermöglicht es uns, den in der Konsole angezeigten String so zu manipulieren, dass er uns die zufällige Geheimzahl preisgibt:
```
```console
$ ./crackme                                                   
Solve this test: 5 + 5 = 10

Type your name [max 9 chars]: 988998899000000000000tiatatiaop
Type your name [max 9 chars]: 9889988998%s-$d-00000tiatatiaop
9889988998%s-$d-00000tiatatiaop
16-00000tiatatiaop

Congrats you entered a secret area
Guess what number I am thinking of [0-20]: 16

Hi Boss
FLAG{chipi chipi chapa chapa dubi dubi daba daba}
```


# Team 12 
#### Malloc never fails

Wir haben uns entschieden, die Schwachstelle "Malloc never fails" zu behandeln. Wenn ein Fehler auftritt, gibt malloc normalerweise einen Nullpointer zurück, der üblicherweise erkannt und entsprechend behandelt werden sollte. In unserem Szenario geben wir einen Hinweis auf die richtige Eingabe, wenn eine zu große Zahl eingegeben wird.

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
# Team 13

### Schritt 1:
Einfach das, was an der Wand steht, mit "brainbrainbrain" xor'en, Ergebnis: xorgenius!

### Schritt 2:
Benutzername und Passwort stehen in der jeweiligen Methode als Hexadezimalcode, Benutzername = Dev, Passwort = 1337 ABER

### Schritt 3:
Es wird eine andere Variable benutzt --> ein Bufferoverflow wird bei einem der Eingaben benötigt.
Da der Benutzername komplett egal ist, muss das Passwort gefälscht werden.

Dabei fällt auf, dass die ersten drei Zeichen als Benutzername genommen werden müssen (muss Dev sein), dann muss der Stack mit 8 Zeichen überbrückt werden und der Wert 1337 im Speicher abgelegt werden.

Benutzername: egal
Passwort: DevAAAAAAAA1337

(oder irgendein beliebiges Zeichen statt A)

Anschließend erhalten wir die Flagge.

statt  ENTER, muss man  MIT CTRL + D besttätigen.
FLAG{FLAG{FLAG{FLAG{FLAG}}}}

# Team 14


```text

Hat drei rounds ...

```
Round 1:
```
Es wird nach der Faktorisierung von X * Y = 2023 gefragt, wobei X und Y eingegeben werden müssen. Natürlich kann man nicht einfach 1 und 2023 eingeben, wäre ja zu einfach. Es existiert keine weitere Faktorisierung, da 2023 eine Primzahl ist. Daher muss ein Integer-Overflow / Underflow verwendet werden.

Wir wählen:
4294967295 + 2004 = 4294969299 (2004 statt 2003, weil 0 existiert)

-> 10071 426469 (Primfaktorzerlegung..)
```
Round 2:
```
Normaler Check mit Bufferoverflow, eine Variable muss 0xdeadbeef sein. Wir müssen also 10 Zeichen eingeben und dann 0xdeadbeef im richtigen Encoding angeben (jetzt mal ernsthaft, wer kann denn bitte schon little endian auf den ersten Versuch richtig eingeben, danke dass ihr es printet).
```
Round 3:
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

# Round 2
p.sendlineafter(b"?", b"AAAAAAAAAA\xEF\xBE\xAD\xDE")

# Round 3
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

# PTY steht für Pseudo-Terminal
pty = process.PTY


# Funktion zum Knacken des Zeitbasierten Einmalschlüssels
def crack(curr, goal):
    i = 0
    while True:
        # Versuche, den Schlüssel zu finden, indem du ihn mit einer Inkrementierung probierst
        tmp = curr + i
        tmp = tmp ^ (tmp >> 0xc)
        tmp = tmp ^ (tmp << 0x19)
        tmp = tmp ^ (tmp >> 0x1b)

        if tmp == goal:
            return i

        # Versuche das Gleiche mit einer Dekrementierung
        tmp = curr - i
        tmp = tmp ^ (tmp >> 0xc)
        tmp = tmp ^ (tmp << 0x19)
        tmp = tmp ^ (tmp >> 0x1b)

        if tmp == goal:
            return -i

        i = i + 1


# Endlosschleife für die Kommunikation mit dem Server
while True:
    # Verbindung zum Server herstellen
    p = remote("tank.informatik.hs-mannheim.de", 3114)

    # Round 1: Primfaktorzerlegung
    p.sendlineafter(b"?", b"10071 426469")

    # Round 2: Senden eines speziellen Strings
    p.sendlineafter(b"?", b"AAAAAAAAAA\xEF\xBE\xAD\xDE")

    # Round 3: Manipulation der Serverzeit
    currtime = int(time.time())  # Aktuelle Serverzeit
    tmp = currtime
    currtime = currtime ^ (currtime >> 0xc)
    currtime = currtime ^ (currtime << 0x19)
    currtime = currtime ^ (currtime >> 0x1b)

    # Senden der manipulierten Zeit und Empfangen der Zielzeit
    p.sendlineafter(b"?", str.encode(str(currtime)))
    p.recvuntil(b"an ")
    goaltime = p.recvall().decode()[:-1]
    timeoffset = crack(tmp, int(goaltime[:-1]))

    # Erneute Verbindung zum Server herstellen
    p = remote("tank.informatik.hs-mannheim.de", 3114)

    # Round 1: Primfaktorzerlegung
    p.sendlineafter(b"?", b"10071 426469")

    # Round 2: Senden eines speziellen Strings
    p.sendlineafter(b"?", b"AAAAAAAAAA\xEF\xBE\xAD\xDE")

    # Round 3: Anpassen der Serverzeit mit dem berechneten Offset
    currtime = int(time.time()) + timeoffset
    currtime = currtime ^ (currtime >> 0xc)
    currtime = currtime ^ (currtime << 0x19)
    currtime = currtime ^ (currtime >> 0x1b)

    # Senden der manipulierten Zeit und Empfangen der Flagge
    p.sendlineafter(b"?", str.encode(str(currtime)))
    flag = p.recvall().decode()

    # Überprüfen, ob die Flagge gefunden wurde
    if "FLAG{" in flag:
        break

# Ausgabe der gefundenen Flagge
print(flag)

```
FLAG{climbing_the_mountain}












