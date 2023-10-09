# CrackMe

Diese Crackme ist nicht besonders kompliziert an und für sich, ist jedoch dafür zweiteilig und beschäftigt sich mit Overflows.
Einmal mit einem Bufferoverflow und anschließend mit einem Integer Overflow.

---

## Probleme - Spoiler:

Leider wird die Manipulation des Pointers bei manueller Eingabe erkannt und das Programm wird beendet.

```
segmentation fault (core dumped)  ./crackme
```

Lässt man jedoch die notwendigen Zeichen über einen Script eingeben, so lässt sich die Flag dennoch ausgeben.

Zuerst dachten wir das es sich um den Stackguard des GCC handelt, jedoch scheint dies nicht der Fall zu sein und wir haben auch keine Lösung gefunden, die dieses Verhalten unterbindet.


Dieser Fehler ist uns leider erst sehr spät aufgefallen nachdem wir schon den zweiten Teil programmiert haben. Da es jetzt relativ knapp vor der Deadline ;) und der zweite Teil auch recht einfach ist haben wir jetzt keine andere CrackMe mehr geschrieben.

Wenn Sie uns sagen können wie man den Fehler beheben kann würden wir die Crackme natürlich noch anpassen.

---

### Teil 1
Im ersten Teil der crackme wird der Nutzer nach einem Passwort gefragt, welches an eine obligatorische verschlüsselungsfunktion weitergegeben wird.

Dabei handelt es sich jedoch nur um einen roten Hering. Die Funktion kombiniert jeden Chars des Inputs mit einem zufälligen Wert per XOR und Bitshiftet das Ergebnis um die Stelle des Chars im String

Die eigentliche Lösung ist es den mit einem Bufferoverflow die Schwachstelle von `gets()` auszunutzen und direkt zur gewünschten funktion `next()` zu springen.

### Teil 2

In der Funktion `next()` werden zwei weitere Eingaben des Nutzers erfordert. Die Summe der einzelnen Chars der Eingaben werden mit einem `Array` abgeglichen welches negative Zahlen beinhaltet.

Da es sich um vorzenbehaftete `Chars` handelt, lässt sich mit einer passenden Eingabe ein Integer-Overflow erzwingen und die Equals-Bedingung erfüllen.

Die erwünschten Inputs wären: "zzzz" und "i<3u"
