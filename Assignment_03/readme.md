# Assignment: Speicherlayout eines Prozesses



In diesem Assignment werden Sie ein kleines C-Programm schreiben, um das Speicherlayout eines Prozesses besser zu verstehen.

## Aufgabe

### Hintergrund

In C hat man direkten Zugriff auf die Adressen aller Objekte, die im Speicher eines Programms vorkommen. Hierzu gehören:

  * Das Programm selbst
  * Funktionen aus der Standardbibliothek
  * Statische Variablen
  * Lokale Variablen auf dem Stack
  * Konstanten
  * Dynamisch allozierter Speicher auf dem Heap

Deswegen werden wir diese Flexibilität von C ausnutzen, um ein Programm zu schreiben, dass die Adressen dieser Objekte ausgibt.

Die `printf`-Funktion aus `<stdio.h>` bietet mit dem `%p`-Formatstring die Möglichkeit, eine Adresse direkt in hexadezimaler Form auszugeben, ohne umständliche Konvertierungen machen zu müssen.

```c
int i = 5;
printf("%p\n", &i); /* Adresse von i ausgeben */
```

### Umsetzung

Schreiben Sie ein Programm in C namens `addresses.c`. In diesem

  1. legen Sie verschiedene Variablen an und geben dann deren Adressen aus,
  2. allozieren Sie Speicher mit `malloc` aus `<stdlib.h>` und geben die Adresse des Speichers aus,
  3. schreiben eine Funktion und geben deren Adresse aus und
  4. geben Sie die Adresse einer Funktion aus der Standardbibliothek aus, z.B. `printf`.

Sie sollen mindestens die folgenden Variablen zu Punkt 1. anlegen:

  * eine globale Variable, die initialisiert wird
  * eine globale Variable, die nicht initialisiert wird
  * eine globale `const`-Variable
  * eine lokale Variable in einer Funktion
  * eine lokale, `static`-Variable in einer Funktion

### Speicherlayout

Führen Sie Ihr Programm aus und notieren Sie sich die Adressen. Versuchen Sie daraus _Schlüsse auf das Speicherlayout des Prozesses_ zu ziehen.

Bei der _Funktion aus der Standardbibliothek_ liegt die Adresse an einer seltsamen Stelle. Können Sie hierfür eine _Erklärung_ finden?

Führen Sie das Programm _mehrmals_ aus. Was _fällt Ihnen auf_? Beschreiben Sie Ihre Erkenntnisse kurz.


## Abgabe

Bitte geben Sie folgendes über Ihre Repository ab:

  * Das Programm `addresses.c`
  * Die Ausgaben des Programms von zwei bis drei Läufen
  * Ihre Erkenntnisse zum Speicheraufbau
  * Ihre Erkenntnisse zu den Veränderungen bei mehrfachen läufen

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.