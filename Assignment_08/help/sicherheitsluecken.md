# Typische Sicherheitslücken

Im Folgenden finden Sie eine kleine Auflistung von Sicherheitslücken, die sich gut in Crackmes verwenden können. Die Liste ist natürlich nicht vollständig - lassen Sie Ihrer Kreativität freien Lauf.
Gerne können Sie auch noch weitere Lücken vorschlagen.

## Buffer-Overflow

### Lokale Variablen überschreiben

Buffer auf dem Stack liegen dort zusammen mit allen anderen lokalen Variablen und können diese bei fehlender oder falscher Prüfung der Grenzen überschreiben (Buffer-Overflow).

```c
int i = 0;
char x[3];

printf("%d\n", i); // -> 0
strcpy(x, "Hell");
printf("%d\n", i); // -> 108
```

### Rücksprungadresse überschreiben

Buffer-Overflows können auch dazu benutzt werden, die Rücksprungadresse zur Aufrufenden Funktion zu überschreiben. Stack-Guards sollen dies verhindern, können aber manchmal übergangen oder explizit durch `-fno-stack-protector` beim Compilieren ausgeschaltet werden.


## Stackbasierte Schwachstellen

### Base-Pointer

Auf dem Stack liegt nicht nur die Rücksprungadresse, sondern auch der gespeicherte Base-Pointer (`EBP`) der vorhergehenden Funktion. Wenn man diesen durch einen Buffer-Overflow modifizieren kann, besteht die Möglichkeit lokale Variablen der aufrufenden Funktion zu verändern.

### Reste auf dem Stack

Der Stack wird bei einem Funktionsaufruf nicht gesäubert. Wenn die Funktion ihre Variablen nicht initialisiert, kann man möglicherweise alte Daten auf dem Stack entdecken.

```c
int a(void) {
  short a = 0xbeef;
  short b = 0xdead;

}

int b(void) {
  int z;
  printf("0x%x\n", z);
}

int main() {
  a();
  b(); // -> 0xbeefdead
}
```


## String-Funktionen

### Größe von String-Puffern

Wegen des Nullbytes muss der Buffer für einen String immer mindestens ein Zeichen länger sein, als der String selbst. Wenn man dies nicht berücksichtigt, kommt es Buffer-Overflows.

```c
char *text = "Hallo";
char *copy = alloc(strlen(text)); /* zu klein */
strcpy(copy, text); /* Buffer overflow */
```

### Länge von Strings

Die normalen String-Funktionen (`strcpy`. `strlen` ...) lesen bis zum ersten 0-Byte (`'\0'`) im `char*`-Array. Dies kann man eventuell ausnutzen, um mehr Daten zu verändern als vom Entwickler gewollt, weil man z.B. einen Puffer bis zum letzten Byte füllt.

```c
int k = 0x47554755;
char src[] = { 'H', 'a', 'l', 'l', 'o' };
char dest[30];

strcpy(dest, src);

printf("%s", dest); // -> HalloUGUGJ
```

### Puffer überschreiben

Funktionen wie `gets`, `strcpy` und `sprintf` überprüfen die Größe des Zielpuffers nicht und lassen sich deswegen hervorragend für Buffer-Overflows nutzen.

```c
int i = 0;
char b[5];
gets(b);
printf("%d\n", i);
```

Deswegen sollten die Funktionen nicht mehr genutzt werden. Findet man sie in den Imports eines Programms lohnt sich die Suche nach der Stelle, an der sie verwendet werden.

## Integer-Overflow

Alle Integer-Datentypen ohne `unsigned` (`char`, `short`, `int`, `long`, `long long`) sind vorzeichenbehaftet und laufen von Plus nach Minus über.

```c
int i = 2147483647;
i++;
printf("%d\n", i); // -> -2147483648
```

Alle Integer-Datentypen mit `unsigned` laufen zur `0` über und zum Max-Value unter.

```c
unsigned int i = 0;
i--;
printf("%u\n", i); // -> 4294967295
i++;
printf("%u\n", i); // -> 0
```

## Formatstring-Schwachstelle

Formatstringschwachstellen (`printf`) erlauben es, Variablen auf dem Stack zu lesen und zu schreiben.

```c
int main() {
  long k = 0xcafebabe;
  long *p = &k;

  printf("0x%9$x"); // -> 0xcafebabe
}
```

## Funktionspointer

Funktionspointer auf dem Stack können, wenn sie durch eine der anderen Schwachstellen modifiziert werden können, dazu genutzt werden beliebige Funktionen aufzurufen.

```c
void f() {
  puts("f called");
}

int main() {
  void (*fp)(void);

  fp = f;
  fp(); // -> f called
}
```


## "malloc can never fail"

`malloc()` gibt `0` im Fehlerfall zurück, dies sollte eigentlich vom Programm geprüft werden. Wird dies nicht geprüft, arbeitet das Programm mit einem Pointer weiter, der die Adresse `0x00` hat.

```c
void *p = malloc(1717272222772);
printf("%p\n", p); // (nil)
```

## Use-After-Free

Mit `malloc` allozierter Speicher wird mit `free` wieder freigegeben. Wenn man den Speicher aber nach dem `free` noch weiter benutzt, können beliebige Daten von anderen Teilen des Programms dort landen, weil `malloc` den Speicher natürlich "recycled". Hierdurch kann man Daten exfiltrieren oder Funktionen sogar eigene Daten unterschieben.

```c
void printer() {
    static char *text = 0;
    if (!text) {
        text = (char*) malloc(sizeof(char) * 9);
        strcpy(text, "mutti123");
    }
    printf("%s\n", text); /* use after free */
    free(text);
}

int main(int argc, char** argv) {
    printer(); /* -> mutti123 */
    char *pwnd = (char*) malloc(sizeof(char) * 9);
    strcpy(pwnd, "pwned!");
    printer(); /* -> pwned! */
}
```


## GOT.PLT

Wenn das Programm `-z,norelro` compiliert ist, kann man die Funktionen im global offset-table (GOT.PLT) ersetzen, so man durch eine andere Schwachstelle Zugriff darauf bekommt. Hierdurch kann man dann Standard-Funktionen der Library durch eigene ersetzen.
