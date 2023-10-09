# Assignment: Eigenes Crackme schreiben

## Verlinkte Dateien

| Name        |                                   Link                                      |
|------------------------------------------|---------------------------------------------------|
| crackme           |[Ausführbare Exe](crackme)                      |
| crackme.c         |[Quellcode der C-Datei](crackme.c)|
| MAKEFILE.mk       |[Makefile zum Erstellen der Datei](MAKEFILE.mk)|
| a31_crackme.rb    |[Skript zur automatischen Lösung](a31_crackme.rb)|
| crackme.rb        |[Hilfskript vom Papi](crackme.rb)|

## Musterlösung

Zuerst starten wir die Datei.

```console
 $ ./crackme
Please enter your input: 
1
2
3
You won't get my flag this way
```

Wie wir sehen, brauchen wir drei Eingaben, um an die Flag zu gelangen. Daher öffnen wir erst einmal die Datei in Ghidra und schauen uns die `main`-Methode an.

```c
undefined8 main(void)

{
  int iVar1;
  int iVar2;
  void *pvVar3;
  void *pvVar4;
  char *__nptr;
  char *__s;
  size_t sVar5;
  undefined2 *__dest;
  
  pvVar3 = malloc(0x40);
  pvVar4 = malloc(0x40);
  __nptr = (char *)malloc(0x40);
  puts("Please enter your input: ");
  __isoc99_scanf(&DAT_00102061,pvVar3);
  __isoc99_scanf(&DAT_00102061,pvVar4);
  __isoc99_scanf(&DAT_00102061,__nptr);
  checkInput(pvVar3);
  iVar1 = checkInput(pvVar4);
  iVar2 = checkInput(__nptr);
  if ((iVar1 != 0) && (iVar2 != 0)) {
    __s = (char *)someFunc(pvVar4);
    sVar5 = strlen(__s);
    __dest = (undefined2 *)malloc(sVar5 + 5);
    *__dest = 0x2d;
    strcat((char *)__dest,__s);
    iVar1 = atoi((char *)__dest);
    iVar2 = atoi(__nptr);
    if ((iVar1 == 0x539) && ((iVar2 % 0x665 == 0 && (iVar2 % 0xde5 == 0)))) {
      win();
      return 0;
    }
  }
  lose();
  return 0;
}

```

Wir können direkt sehen, dass zuerst unsere drei Eingaben in den Variablen `pvVar3`, `pvVar4` und `__nptr` mit der `scanf`-Methode gespeichert werden. Danach wird die Methode `checkInput()` jeweils mit ihnen als Parameter aufgerufen. 

```c
  pvVar3 = malloc(0x40);                    # Variablen werden erstellt
  pvVar4 = malloc(0x40);
  __nptr = (char *)malloc(0x40);
  puts("Please enter your input: ");
  __isoc99_scanf(&DAT_00102061,pvVar3);     # Eingaben werden gelesen
  __isoc99_scanf(&DAT_00102061,pvVar4);
  __isoc99_scanf(&DAT_00102061,__nptr);     
  checkInput(pvVar3);                       # CheckInput wird ausgeführt
  iVar1 = checkInput(pvVar4);
  iVar2 = checkInput(__nptr);
```
Wir gucken uns zunächst an, was `checkInput()` macht. Wie wir sehen können, wird `checkInput()` ein String übergeben. Jedes Zeichen dieses String wird innerhalb einer `while`-Schleife darauf geprüft, ob das Zeichen eine Zahl von 0 bis 9 ist. Ist dies der Fall, wird 1 zurück gegeben, sonst 0.

```c
undefined8 checkInput(char *param_1)

{
  size_t sVar1;
  int local_1c;
  
  local_1c = 0;
  while( true ) {
    sVar1 = strlen(param_1);
    if (sVar1 <= (ulong)(long)local_1c) {
      return 1;
    }
    if ((param_1[local_1c] < '0') || ('9' < param_1[local_1c])) break;          # Zeichen muss eine Zahl von 0-9 sein
    local_1c = local_1c + 1;
  }
  return 0;
}
```

Wenn wir jetzt nochmal einen Blick auf die `main` werfen, können wir sehen, dass das Ergebnis von `checkInput(pvVar3)` nicht gespeichert wird. Ebenso fällt auf, dass die Variable `pvVar3` sonst auch nicht verwendet wird. Daher ignorieren wir die erste Eingabe erstmal. Die Methode `checkInput()` sagt uns auch, dass die zweite und dritte Eingabe nur aus Zahlen bestehen darf, da sonst die Methode `lose()` aufgerufen wird und das Programm ohne Flagausgabe abbricht.

```c
iVar1 = checkInput(pvVar4);
iVar2 = checkInput(__nptr);

if ((iVar1 != 0) && (iVar2 != 0)) {
    ...
  }
  lose();
  return 0;
}


# Lose Methode
void lose(void)

{
  puts("You won\'t get my flag this way");
  return;
}
```

Nun werfen wir einen Blick auf das Ende des `if`-Blocks in `main`. Hier sehen wir, dass drei Bedingungen erfüllt sein müssen, um die `win()`-Methode auszuführen. Wir können zwar die Flag sehen, jedoch wissen wir immer noch nicht, welche Eingabe notwendig ist, um sie durch das Programm ausgeben zu lassen.

```C
void win(void)

{
  puts("FLAG{it\'s_less_than_9000!}");
  return;
}
```

Wir müssen also dafür sorgen, dass `iVar1` und `iVar2` bestimmte Werte annehmen.

```C
if ((iVar1 == 0x539) && ((iVar2 % 0x665 == 0 && (iVar2 % 0xde5 == 0)))) {
      win();
      return 0;
    }
```

Fangen wir mit `iVar2` an, da dies deutlich simpler ist. Wir können sehen, dass `iVar2` einfach nur unsere dritte Eingabe (`__nptr`) ist, welche zu Integer typisiert wurde. Wir müssen also als dritte Eingabe einfach eine Zahl eingeben, die sowohl durch 1637 als auch durch 3557 glatt teilbar ist.

```C
...
iVar2 = atoi(__nptr);                                                           
if ((iVar1 == 0x539) && ((iVar2 % 0x665 == 0 && (iVar2 % 0xde5 == 0)))) {       # 0x665 == 1637
    ...                                                                         # 0xde5 == 3557
}
```
Die einfachste Methode diese Zahl zu finden ist einfach die beiden Werte zu multiplizieren. In diesem Fall ist es auch die effizienteste Lösung, da die Prüfwerte Primzahlen sind.

```
1637 * 3557 = 5822809
```

Somit wissen wir nun, dass unsere erste Eingabe egal ist und unsere dritte Eingabe `5822809` sein muss. 

Bevor wir jedoch zu `iVar1` kommen, gucken wir uns einmal die Methode `someFunc()` an.

```C
void * someFunc(char *param_1)

{
  size_t sVar1;
  void *pvVar2;
  int local_2c;
  char *local_28;
  
  sVar1 = strlen(param_1);
  local_28 = param_1 + (sVar1 - 1);
  sVar1 = strlen(param_1);
  pvVar2 = malloc(sVar1);
  local_2c = 0;
  while( true ) {
    sVar1 = strlen(param_1);
    if (sVar1 <= (ulong)(long)local_2c) break;
    *(char *)((long)local_2c + (long)pvVar2) = *local_28;
    local_28 = local_28 + -1;
    local_2c = local_2c + 1;
  }
  return pvVar2;
}
 ```
Wir können sehen, dass diese Methode einfach nur einen String übergeben bekommt und danach die Reihenfolge aller Zeichen umdreht. Beispielsweise wird aus dem String `1234W` der String `W4321`.

Kommen wir also zu `iVar1`. Wir schauen uns zunächst alle relevanten Zeilen des `if`-Blockes an. Zunächst wird unsere Eingabe umgedreh und dessen Ergebnis wird in `__s` gespeichert. Danach wird eine neue Variable `__dest` erstellt, welche den Wert "-" bekommt. Danach werden die beiden Variablen mit `strcat()` zu einem String zusammengefügt. Im Prinzip bekommt `__s` einfach ein negatives Vorzeichen. Das Ganze wird anschließend zu Integer typisiert und in `iVar1` abgespeichert. Um die Flag zu erhalten, muss `iVar1` am Ende den Wert `1337` haben.

```C
    __s = (char *)someFunc(pvVar4);                                                 
    sVar5 = strlen(__s);                                                            
    __dest = (undefined2 *)malloc(sVar5 + 5);
    *__dest = 0x2d;                                                                 # 0x2d == "-"
    strcat((char *)__dest,__s);                                                     
    iVar1 = atoi((char *)__dest);                                                   
    ...
    if ((iVar1 == 0x539) && ((iVar2 % 0x665 == 0 && (iVar2 % 0xde5 == 0)))) {       # 0x539 == 1337
```
Wir müssen also eine Eingabe tätigen, die umgedreht und mit negativem Vorzeichen `1337` ergibt. Das wäre in unserem Fall die Eingabe `7331-`. Jedoch gibt es hier ein Problem. Wir haben schon festgestellt, dass die zweite Eingabe nur aus Zahlen bestehen darf und die Funktion `atoi`kann "--1337" nicht umwandeln. Somit müssen wir uns einer Schwachstelle bedienen. Wir können an dieser Stelle einen `Integer Overflow` ausnutzen, um eine negative Zahl in eine positive umzuwandeln. Wir wissen, dass ein (vorzeichenbehafteter) Integer bei modernen Systemen 32 Bit groß ist, wobei die Hälfte davon für negative Zahlen verwendet wird. Da im Prinzip eine Zahl gesucht wird, die mit einem negativen Vorzeichen durch einen `Integer Overflow` auf `1337` kommt, müssen wir eine Zahl eingeben, die den Integer-Rahmen sprengt. Da die Zahl im Anschluss ein negatives Vorzeichen bekommt, passiert der `Integer Overflow` im negativen Bereich. Der Bereich für negative Zahlen erstreckt sich bis (-2<sup>31</sup>). Um wieder auf 0 zu kommen , müssen wir noch (-2<sup>31</sup>) hinzuaddieren. Damit kommen wir auf (-2<sup>32</sup>). Jetzt sind wir aber über das Ziel hinausgeschossen, da wir auf 1337 kommen müssen. Daher addieren wir 1337 zu (-2<sup>32</sup>). In dem Programm wird zu unserer zweiten Eingabe ein Minuszeichen hinzugefügt, somit müssen wir das von unserem Ergebnis entfernen und die Zahl anschließend umdrehen. 
```
-2^32 + 1337 = -4294965959 == 1337
4294965959                                                                        # Vorzeichen weglassen
Umgekehrt: 9595694924
```

Werte während der Methode:
   
```C
    ...                                                                             # "9595694924"
    __s = (char *)someFunc(pvVar4);                                                 # "4294965959"       
    ...
    strcat((char *)__dest,__s);                                                     # "-4294965959" 
    iVar1 = atoi((char *)__dest);                                                   # 1337
```

Somit haben wir die zweite Eingaben `9595694924`. Jetzt geben wir unsere Eingaben `irgendetwas`, `9595694924` und `5822809` ein und benutzen diese, um uns die Flag auszugeben.

```Console
$ ./crackme
Please enter your input: 
egal
9595694924
5822809
FLAG{it's_less_than_9000!}
```

Somit erhalten wir unsere Flag.