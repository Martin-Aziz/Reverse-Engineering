# Crackme Team 02

Das Crackme wird mit den Compiler-Flags `-fno-stack-protection` und `-no-pie`
kompiliert. Dadurch wird der Schutz vor Stack-Smashing-Angriffen deaktiviert
und es findet keine Adressrandomisierung statt.

Wir haben einige Vorkehrungen vorgenommen, um eine Manipulation am Crackme
auszuschließen. Diese ist zwar durch die Regeln ausgeschlossen, wir wollten
uns aber dennoch mal daran versuchen.

Die Flag liegt XOR-verschlüsselt in einer Variable, das Passwort zur Entschlüsselung
wird bereitgestellt, wenn eine Request an einen von uns geschriebenen 
Server gestellt wird. Bei dieser Request werden die Bytes der Datei übertragen,
ein Hash berechnet und mit einer Hashmap der autorisierten Binaries abgeglichen.

Um die Binary zu autorisieren, wird durch das Makefile nach dem Kompilieren
des crackmes die Datei über das Ruby-Skript `setup_crackme.rb` mit dem Passwort
an den Server übertragen.

## Schwachstelle und Ausnutzung

Die Flag wird durch eine `win()`-Funktion ausgegeben, die jedoch nicht erreichbar
ist, da die Funktion `read_password()` immer 0 zurückgibt.

```c
    int has_won = read_password();

    if (has_won) {
        win();
    }
```

Die Funktion `read_password()` schreibt jedoch einen vom Nutzer bereitgestellten
String in ein Array fester Größe(10), das in Folge overflowt. Da die Compiler-Flag
`-fno-stack-protection` gesetzt wurde, schützt gcc den Return-Pointer nicht.
Dieser kann also durch den Nutzerinput überschrieben werden und auf die Adresse
der `win()`-Funktion gesetzt werden. Die `-no-pie` Option deaktiviert die
Randomisierung von Adressen und ermöglicht eine konsistente Ausnutzung der
Schwachstelle ohne einen Debugger wie gdb.

In gdb finden wir zunächst die Adresse des Aufrufs von `win` heraus:

```gdb
   0x0000000000401d2f <+521>:	mov    eax,0x0
   0x0000000000401d34 <+526>:	call   0x401aa2 <win>
```
Wir können z.B. an die Adresse `0x401d2f` springen um dann direkt `win` aufzurufen.
Experimentell (oder durch Inspektion des Stacks), lässt sich bestimmen, dass
der Return-Pointer 18 Bytes nach dem Beginn der Eingabe anfängt.

Auszug des Stacks in der angegriffenen Funktion `read_password` vor Texteingabe:
```
(gdb) x /30b $rsp
0x7fffffffd7b0:	0xd0	0xcb	0x41	0x00	0x00	0x00	0x00	0x00
0x7fffffffd7b8:	0x00	0x02	0x00	0x00	0x6f	0x00	0x00	0x00
0x7fffffffd7c0:	0x10	0xd8	0xff	0xff	0xff	0x7f	0x00	0x00
0x7fffffffd7c8:	0x26	0x1d	0x40	0x00	0x00	0x00
```
Wir sehen die korrekte Rücksprungadresse `0x401d26` beginnend genau 18 Bytes
nach Beginn unseres Arrays (10 Bytes Array + 8 Bytes Basepointer).

Wir puffern zur Ausnutzung also 18 Bytes mit einem beliebigen Zeichen um an
der richtigen Stelle im Speicher zu schreiben und schreiben dann die ASCII-Werte
für unsere Zieladresse (in Little Endianness). Für die automatisierte Lösung können
wir direkt die benötigten Bytes schreiben.

```
  Enter password:
  000000000000000000/^]@
  FLAG{stack_guards_are_for_noobs}
```

Wir nutzen Nullen als Puffer, `/` mit dem Hex-Wert `0x2f`, `^]` muss über 
`ctrl + v + ]` eingegeben werden und repräsentiert den Hex-Wert `0x1d`, `@`
den Hex-Wert `0x40`. Wir springen daher zum Aufruf der `win`-Funktion, die Flag
wird entschlüsselt und ausgegeben.
