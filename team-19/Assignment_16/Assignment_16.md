### Problem


### Flag_1
Beim dissasemblieren fällt besonders das Setzen eines Nullbits auf. Geschriebene Werde aus dem CHAR Raum
Annahme: ein Sting wird geschrieben.
Hex-Werte als Chars ergeben "FLAG{do not stack}"

### Flag_2

~~~
bissel leer hier...
~~~

### Flag_3
Interpretation:
Es gibt eine for schleife zwischen +73 und +31. In dieser werden die Werte aus dem Array, welcher bei FLAG_3 gespeichert ist, mit einer Bitmaske (0x7f) verundet und die letzten 8 bit (dl) in ein Register gespeichert welches nach dem Ablauf der Schleife die Flag enthält.
Die Schleife läuft 39 mal - erkennbar an den Instruktionen +66...+73

Vorgehen:
Elemente des Arrays bei Flag_3 mit 0x7f verunden und ausgeben lassen.
Daten des arrays durch "x /39xb (char*) FLAG_3"
Verarbeitung erfolgt durch python und ergibt:
"FLAG{don't get high on your own supply}"

### Flag 4
Aufbau ähnlichkeiten zu flag 3.
(for loop, array etc)
xor instruktion 
vermutlich handelt es sich hier also um eine XOR Verschlüsselung.

In den Lösungshinweisen ist vermerkt, das in diesem Falle der Schlüssel 4 Zeichen lang ist die Flagge natürlich mit "FLAG{" beginnt.

lässt man sich also z.B. die nächsten 11 Byte in hexadezimal ausgeben

´ x /11xb (char*) &FLAG_4 ´

so bekommt man Folgende HEX-Werte:
~~~
2D 29 38 34  10 1D 16 01  19 1C 04 
~~~
Wenn wir die ersten vier Werte mit den HexWerten der jeweiligen ASCII Zeichen des Strings "FLAG" kombinieren bekommen wir die Werte:
~~~
6b 65 79 73 
~~~
Als ASCII Character interpretiert ergibt das den Schlüssel: "keys"

Wenn wir nun den Schlüssel "keys" wiederholt auf die verschlüsseklen HEX-Werte mit XOR anwenden, erhalten wir die Werte:
~~~
46 4c 41 47 7b 78 6f 72 72 79 7d
~~~
Interpretiert man diese wieder als ASCII Zeichen erhält man den Text:
~~~
FLAG{xorry}
~~~
### Flag_5
Indizien:
    Array pointer mit Offset "QWORD PTR [rbp - 0x8]"
    Incrementierender Offset beim beschrieben (add rax 0x1...0xd)
    0x0 Nullbit wahrscheinlich ein String
Annahme: Array wird mit Werten gefüllt.
Untersuchung mit "p /c .." -> FLAG{2+2=4}

### Flag_6
Es werden anscheinend drei Hexdatensätze  mit einem Offset von 8 bit in das rax register geschrieben. Dies führt zu der Vermutung, dass die Flag zusammengesetzt wird.

Es gibt 3 Instruktionen die wir untersuchen wollen, 0xd2d , 0xd42, 0xd57.
Untersuchen wir dise 3 Instruktionen mit "x /s" und berücksichtigen wir den "Head" der Instuktionen erhalten wir mit:
0xd2f - "FLAG{the"
0xd44 - " little "
0xd59 - "ndian}"
"FLAG{the little ndian}"

### Flag_7

~~~
keine Lösung:
~~~