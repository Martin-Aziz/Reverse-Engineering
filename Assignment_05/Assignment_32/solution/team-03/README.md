## Assignment 31: Solution (Writeup)

back to main menu: [overview assignments](../readme.md)

## result: FLAG{REE_CAN_BE_FUN}
---

## Kapitel 1: Kommentierter Quellcode in C - File crackme.c

```c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

 //Verschlüsselte Flag sonst ist es ja zu einfach :)
#define KEY "\xBF\xA8\xF2\xBA"
#define ENCRYPTED "\xf9\xe4\xb3\xfd\xc4\xfa\xb7\xff\xe0\xeb\xb3\xf4\xe0\xea\xb7\xe5\xf9\xfd\xbc\xc7"

//simple Binary to Int interpreter
int binary_to_int(char *binary)
{
  int len = strlen(binary);
  int result = 0;
  for (int i = 0; i < len; i++)
  {
    if (binary[i] == '1')
    {
      result += pow(2, len - i - 1);
    }
  }
  return result;
}

void win()
{
  int j = 0;

  // das Flag wird durch verXORen mit dem Key entschlüsselt
  while (j < 20)
  {
    printf("%c", ENCRYPTED[j] ^ KEY[j % 4]);
    j = j + 1;
  }
  printf("%s", "\n");
}

int main()
{

  printf("Geben Sie meine Lieblingszahl ein: ");
  // Eingabe führt zur erstellung eines mallocs

  int eingabe;
  scanf("%d", &eingabe);
  //Malloc never fails, hier wird ein Malloc Fail nicht abgefangen sondern mit einem hint zum Flag geführt
  int *ptr = malloc(eingabe * sizeof(int));
  if (ptr == NULL)
  {
    printf("FALSEFALG{SHIT_1337_BIN_UR_CLOSE_SECRETCODE_69}\n");
    exit(0);
  } if (eingabe == 69)  {
    // Wenn die Eingabe 1337 ist, wird das Flag ausgegeben bzw. wenn sich die Binäreingabe in 1337 konvertieren lässt 
    printf("SECRET CODE?\n");
    char eingabe[100];
    scanf("%s", eingabe);
    if (binary_to_int(eingabe) == 1337)
    {
      encrypt_flag();
      exit(0);
    } else
    {
      printf("LOL FAILED");
      exit(0);
    }
  }
    //eye candy
    printf("Was ist denn ihre ID?: ");
    int eingabe2;
    scanf("%d", &eingabe2);
    printf("Cool :) ");

    return 1;
  }
```


## Kapitel 2: Makefile und fertig compiliertes Executable
Das Makefile ist hochgeladen unter dem Namen Makefile und das fertig compilierte Executable heißt crackme.

## Kapitel 3: Textuelle Beschreibung der Schwachstelle und des Angriffs
Wir haben uns für die Schwachstelle "Malloc never fails" entschieden, bei einem Fehler gibt malloc ein 0 Pointer zurück der normalerweise abgefangen und behandelt gehört.
In unserem Fall geben wir wenn eine zu große Zahl eingegeben wird einen Hinweis zu den richtigen Eingaben zurück.
Jetzt muss man nur noch mit dem FALSEFALG Hinweisen darauf kommen das die Eingaben einmal 69 und dann Binär 1337 also 10100111001 sind.

## Kapitel 4: Python Skript das die Schwachstelle ausnutzt 
Wir haben es in 2 Skripts aufgeteilt skript2.py nutzt die Schwachstelle aus um den Hinweis zu erhalten:

```bash
$ ./skript2.py
Geben Sie meine Lieblingszahl ein: 999999999999999
 FALSEFALG{SHIT_1337_BIN_UR_CLOSE_SECRETCODE_69}
 ```

```python
#!/usr/bin/python3
# -*- coding: utf-8 -*-

import subprocess
import os

# Absoluter Pfad zum Skript
script_path = os.path.abspath(__file__)

# Verzeichnis in dem das Skript liegt (Gleiches Verzeichnis in dem auch das Python Skript liegt)
script_dir = os.path.dirname(script_path)

# Speichere den Pfad zu unserer Crackme in dem Executable_Path
executable_path = os.path.join(script_dir, 'crackme')

# Festlegen der korrekten Inputs (Um die Sicherheitslücke und den Hinweis zu erhalten müsste man das Skript 2x starten mit einer sehr großen Zahl)
input1 = '999999999999999'

# Executable in einem Subprocess laufen lassen und den Output aufzeichnen
result = subprocess.run([executable_path], input=f'{input1}\n', capture_output=True, encoding='utf-8')

# Aufteilen des Ergebnisses für richtiges Layout
lines = result.stdout.strip().split(':')

# Ausgabe der Ein und Ausgaben
input1_entered = False

for line in lines:
	if not input1_entered:
		print(f'{line}: {input1}')
		input1_entered = True
		continue
	print(line)
```

 Und skript.py gibt dann die richtigen Eingaben ein damit das Flag ausgegeben wird:

 ```bash
$ ./skript.py
Geben Sie meine Lieblingszahl ein: 69
 Wer ist die Elite: 10100111001

FLAG{REE_CAN_BE_FUN}
```

```python
#!/usr/bin/python3
# -*- coding: utf-8 -*-

import subprocess
import os

# Absoluter Pfad zum Skript
script_path = os.path.abspath(__file__)

# Verzeichnis in dem das Skript liegt (Gleiches Verzeichnis in dem auch das Python Skript liegt)
script_dir = os.path.dirname(script_path)

# Speichere den Pfad zu unserer Crackme in dem Executable_Path
executable_path = os.path.join(script_dir, 'crackme')

# Festlegen der korrekten Inputs (Um die Sicherheitslücke und den Hinweis zu erhalten müsste man das Skript 2x starten mit einer sehr großen Zahl)
input1 = '69'
input2 = '10100111001'

# Executable in einem Subprocess laufen lassen und den Output aufzeichnen
result = subprocess.run([executable_path], input=f'{input1}\n{input2}\n', capture_output=True, encoding='utf-8')

# Aufteilen des Ergebnisses für richtiges Layout
lines = result.stdout.strip().split(':')

# Ausgabe der Ein und Ausgaben
input1_entered = False

for line in lines:
	if not input1_entered:
		print(f'{line}: {input1}')
		input1_entered = True
		continue
	#Aufsplitten des Outputs damit input2 zwischen output geschrieben wird
	print(f'{line.split("?", 1)[0]}: {input2}')
	#Flag Ausgabe
	print(f'{line.split("?", 1)[1]}')
```

