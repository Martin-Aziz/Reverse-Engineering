# Assignment 31

`main.c` ist das Hauptprogramm. `payload.c` ist ein zweites Programm, welches erst zu einer object Datei `payload.o` kompiliert wird, von der anschließend der x86 code in `payload.bin` extrahiert wird. Mit Hilfsprogramm `encrypt.cpp` wird `payload.bin` verschlüsselt und dann mit `main.c` kombiniert in `crackme.c` geschrieben. Von `crackme.c` wird das Finale Programm `crackme` erzeugt.

## Beispiel Lösung

Zuerst haben wir das crackme in Ghidra geöffnet.
Dort haben wir in der `main` angefangen. Hier haben wir den Variablen sinnvolle Typen und Namen gegeben:
```c
int main()
{
  time_t current_time;
  char input [21];
  
  current_time = time((time_t *)0x0);
  srand((uint)current_time);
  printf("password: ");
  input._0_8_ = 0;
  input._8_8_ = 0;
  input._16_4_ = 0;
  input[20] = '\0';
  __isoc99_scanf("%20s",input);
  reconstruct_password(input);
  win(input);
  return 0;
}
```
Daran kann man sehen, dass eine Benutzereingabe in `input` geschrieben wird und an `reconstruct_password` gegeben wird. Zum Schluss wird `input` auch noch an `win` übergeben.

Also haben wir uns `reconstruct_password` angeschaut und auch bessere variablen Namen vergeben:
```c
void reconstruct_password(char *password)
{
  size_t length;
  uint i;
  int j;
  char temp;
  
  length = strlen(password);
  for (i = 0; (int)i < (int)length; i = i + 1) {
    j = (int)((i * 2 ^ i) * 0x1d) % (int)length;
    temp = password[(int)i];
    password[(int)i] = password[j];
    password[j] = temp;
  }
  return;
}
```
In dieser Funktion werden die Zeichen des eingegebenen Passworts vertauscht.

Dann haben wir uns noch die `win` Funktion angeschaut und ebenfalls ein paar Variablen typisiert und umbenannt:
```c
void win(char *password)
{
  void *function_buffer;
  ulong uVar1;
  long offset;
  undefined8 *puVar2;
  undefined8 *puVar3;
  byte bVar4;
  
  bVar4 = 0;
  function_buffer = mmap((void *)0x0,0x1a9,7,0x22,0,0);
  *(undefined8 *)function_buffer = 0xb89fde3080ed263c;
  *(undefined8 *)((long)function_buffer + 0x1a1) = 0x7568735f7865646e;
  puVar3 = (undefined8 *)((long)function_buffer + 8U & 0xfffffffffffffff8);
  offset = (long)function_buffer - (long)puVar3;
  puVar2 = (undefined8 *)(&encrypted_program + -offset);
  for (uVar1 = (ulong)((int)offset + 0x1a9U >> 3); uVar1 != 0; uVar1 = uVar1 - 1) {
    *puVar3 = *puVar2;
    puVar2 = puVar2 + (ulong)bVar4 * -2 + 1;
    puVar3 = puVar3 + (ulong)bVar4 * -2 + 1;
  }
  xor_decrypt(function_buffer,0x1a9,password);
  (*(code *)function_buffer)(rand,printf,__isoc99_scanf,memset,malloc);
  return;
}
```
Hier wird mithilfe von `mmap` der `function_buffer` allokiert, mit irgendwelchen Werten beschrieben, mit `xor_decrypt` entschlüsselt und anschließend als Funktion aufgerufen.

Zur Sicherheit haben wir uns nochmal `xor_decrypt` angeschaut, aber diese Funktion macht nichts Unerwartetes:
```c
void xor_decrypt(byte *buffer,ulong buffer_length,char *password)
{
  size_t password_length;
  ulong i;
  
  password_length = strlen(password);
  for (i = 0; i < buffer_length; i = i + 1) {
    buffer[i] = password[i % password_length] ^ buffer[i];
  }
  return;
}
```

Also müssen wir erstmal das Passwort herausfinden, dann können wir die Zeichen darin so vertauschen, dass sie durch `reconstruct_password` wieder das eigentliche Passwort ergeben und in das Programm eingeben.

Also haben wir uns das Programm mit `strings` angeschaut und mit `grep password` nach einem Passwort gesucht:
```shell
$ strings crackme | grep password
huffleindex_shuffleindex_shuffleindex_shuffleindex_shuffleindex_password: 
reconstruct_password
```

Hier ist auffällig das sich `index_shuffle` mehrmals wiederholt, was auf XOR-Verschlüsselte null Bytes hinweisen kann, also gehen wir davon aus, dass es sich um das Passwort handelt.
Jetzt müssen wir noch die Zeichen so vertauschen das `reconstruct_password` das tatsächliche Passwort herstellt.
Dafür müssen wir dieselben Vertauschungen nur in umgekehrter Reihenfolge durchführen. Dafür haben wir ein kleines Script mit JavaScript erstellt:
```js
function shuffle_reverse(password)
{
	let length = password.length;
	for (let i = length - 1; i >= 0; i--)
	{
		let j = ((i ^ (i << 1)) * 29) % length;
		let temp = password[i];
		password[i] = password[j];
		password[j] = temp;
	}
	return password;
}
console.log(shuffle_reverse([..."index_shuffle"]).join("")); // iexdul_nhesff
```
Wenn wir dieses Passwort in das Programm eingeben kommt Folgendes heraus:
```shell
$ ./crackme
password: iexdul_nhesff
Input: 
```
Es scheint also das wir noch nicht Fertig sind.

Deshalb haben wir mit `gdb` den entschlüsselten code extrahiert:
```shell
$ gdb crackme
...
(gdb) break main
Breakpoint 1 at 0x1353
(gdb) r
...
Breakpoint 1, 0x0000555555555353 in main ()
(gdb) break win
Breakpoint 2 at 0x555555555279
(gdb) c
Continuing.
password: iexdul_nhesff

Breakpoint 2, 0x0000555555555279 in win ()
(gdb) x /60i $rip
=> 0x555555555279 <win+4>:      sub    rsp,0x20
   0x55555555527d <win+8>:      mov    QWORD PTR [rbp-0x18],rdi
   0x555555555281 <win+12>:     mov    r9d,0x0
   0x555555555287 <win+18>:     mov    r8d,0x0
...
   0x555555555346 <win+209>:    mov    rdi,rax
   0x555555555349 <win+212>:    call   r8
   0x55555555534c <win+215>:    nop
   0x55555555534d <win+216>:    leave
   0x55555555534e <win+217>:    ret    
   0x55555555534f <main>:       push   rbp
   0x555555555350 <main+1>:     mov    rbp,rsp
...
(gdb) break *0x555555555349
Breakpoint 4 at 0x555555555349
(gdb) c
Continuing.

Breakpoint 4, 0x0000555555555349 in win ()
(gdb) p $r8
$2 = 140737354117120
(gdb) x /100i $r8
   0x7ffff7ffb000:      push   rbp
   0x7ffff7ffb001:      mov    rbp,rsp
   0x7ffff7ffb004:      sub    rsp,0xd0
...
   0x7ffff7ffb171:      leave
   0x7ffff7ffb172:      ret    
   0x7ffff7ffb173:      add    BYTE PTR [rax],al
   0x7ffff7ffb175:      add    BYTE PTR [rax],al
   0x7ffff7ffb177:      add    BYTE PTR [rax],al
   0x7ffff7ffb179:      add    BYTE PTR [rax],al
   0x7ffff7ffb17b:      add    BYTE PTR [rax],al
   0x7ffff7ffb17d:      add    BYTE PTR [rax],al
   0x7ffff7ffb17f:      add    BYTE PTR [rax],al
...
(gdb) dump binary memory decrypted_dump.bin 0x7ffff7ffb000 0x7ffff7ffb17f
```

Diesen haben wir uns dann wieder in Ghidra angeschaut. Wir haben die Parameter Namen angepasst damit sie mit den Namen der in `win` übergebenen Funktionen übereinstimmen und auch die Namen und Typen der anderen Variablen angepasst:
```c
void encrypted_function(code *rand,code *printf,code *scanf,code *memset,code *malloc)
{
  int temp_rand;
  char flag_string [25];
  char result_string [13];
  char scan_format_string [8];
  char input_string [8];
  long value;
  long index;
  long buffer [12];
  int scan_res;
  long *rand0_check;
  long rand1;
  long rand0;
  
  temp_rand = (*rand)();
  rand0 = (long)temp_rand;
  temp_rand = (*rand)();
  rand1 = (long)temp_rand;
  index = 0;
  value = 0;
  rand0_check = (long *)(*malloc)(8);
  *rand0_check = rand0;
  while( true ) {
    (*memset)(buffer,0,0x58);
    input_string = 0x203a7475706e49; // \0 :tupnI
    (*printf)(input_string);
    scan_format_string = 0x646c2520646c25; // \0dl% dl%
    scan_res = (*scanf)(scan_format_string,&index,&value);
    if (scan_res != 2) break;
    buffer[index] = value;
    result_string._0_8_ = 0x203a746c75736552; //  :tluseR
    result_string._8_4_ = 0xa646c25; // \ndl%
    result_string[12] = '\0';
    (*printf)(result_string,buffer[index]);
  }
  if (rand1 == *rand0_check) {
    flag_string._0_8_ = 0x6e61687b47414c46; // nah{GALF
    flag_string._8_8_ = 0x796d20666f207364; // ym fo sd
    flag_string._16_8_ = 0xa7d6b6361747320; // \n}kcats
    flag_string[24] = '\0';
    (*printf)(flag_string);
  }
  return;
}
```
Hier kann man sehen, dass die Bedingung `rand1 == *rand0_check` gegeben sein muss damit die Flagge ausgegeben wird. Es fällt außerdem auf, dass wie beim Assignment 30 in einen Buffer an einer beliebigen Stelle geschrieben werden kann und auch von dieser Stelle wieder ausgelesen wird. Im Gegensatz zum Assignment 30 reicht es allerdings nicht nur einen Wert auf dem Stack zu überschreiben da die verglichenen Werte zufällig erzeugt werden und `rand0_check` auf dem Heap an einer unbekannten Stelle gespeichert wird. Deshalb muss `rand1` auf den Wert `*rand0_check` gesetzt werden welcher auch in `rand0` steht.

Um an den Wert von `rand0` dranzukommen ist es allerdings notwendig vom Stack zu lesen, ohne zuvor den Wert zu überschreiben. Damit der Wert nicht überschrieben wird, muss der beschriebene Index also ein anderer sein als der Gelesene. Dies kann erreicht werden, indem man einen Index angibt, der auf die Indexvariable selbst auf dem Stack zeigt und dann einen Wert zuweist welcher die eigentliche Leseposition beinhaltet.

Dafür benötigen wir erstmal die Positionen auf dem Stack, die uns Ghidra gibt:
```
undefined8        Stack[-0x10]:8 rand0
undefined8        Stack[-0x18]:8 rand1
undefined8        Stack[-0x20]:8 rand0_check
undefined4        Stack[-0x24]:4 scan_res
undefined1[96]    Stack[-0x88]   buffer
undefined8        Stack[-0x90]:8 index
long              Stack[-0x98]:8 value
```
Damit haben wir die folgenden Offsets relativ zu `buffer`:
| Variable | Byte Offset | 8 Byte Offset |
| --- | --- | --- |
| rand0 | 120 | 15 |
| rand1 | 112 | 14 |
| index | -8 | -1 |


> Edit: In der Finalen Datei, die im Assignment 32 zur Verfügung steht, ist der Verschlüsselte teil etwas anders.
> 
> Die Funktion wird nicht so gut in Ghidra dekompiliert und man muss Ghidra auch manuell (indem man d drückt) dazu bringen es zu dekompilieren. Außerdem können Variablentypen und Namen nicht angepasst werden.
> 
> Die Offsets sind auch anders und müssen aus dem Assembler-Code gelesen werden.
> Darin sieht man die neuen Offsets (die relativen Offsets sind wieder relativ zum `buffer`):
> | Variable | Base Pointer Offset | relativer Byte Offset | relativer 8 Byte Offset |
> | --- | --- | --- | --- |
> | buffer | -160 | 0 | 0 |
> | index | -200 | -40 | -5 |
> | rand0 | -184 | -24 | -3 |
> | rand1 | -176 | -16 | -2 |
> 
> Dementsprechend müssen auch die folgenden Eingaben und das Skript angepasst werden:
> - `-5 -3` um `rand0` zu lesen
> - `-2 <value>` um `rand1` zu setzen.


Also kann `rand0` mit der Eingabe `-1 15` gelesen werden. Da 15 erst an die Position -1 geschrieben wird und somit den Index überschreibt und anschließend an der Position 15 ausgelesen wird.
```shell
Input: -1 15
Result: 1985437028
```
Jetzt kann mithilfe der Eingabe `14 1985437028` der Wert 1985437028 in die Variable `rand1` geschrieben werden und mit Ctrl+D die Eingabe beendet werden, um die Flagge zu erhalten.
```shell
Input: 14 1985437028
Result: 1985437028
Input: FLAG{hands of my stack}
```
[Das Lösungsskript in JavaScript](./solve.js)