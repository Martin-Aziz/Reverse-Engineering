# Challenge

```
Es wird ein Passwort bzw Text  benötigt um das Flag auszugeben
```
```console
┌─[root@parrot]─[/home/twotimer/Desktop]
└──╼ #./password_check_11 
Show us your 1337 brain:
```
#### Analyse in GHIDRA
```
In der Main Methode werden 255 Bit Speicher mit Nullen beschrieben. Auf diesen Speicher zeigt ein Pointer, hier ConstantPointer genannt.

Daraufhin werden zwei Methoden,
read_password und interpreter_loop aufgerufen.

Die zu erfüllende Kondition um das Flag auslesen zu können ist, dass sich an dem ConstantPointer ein String befindent, welcher identisch zu "1337" ist.
```
##### read_password
```
In einen übergebenen Buffer wird die eingabe des Nutzers geschrieben. Diese Eingabe hat eine Größenbeschrenkung von 254.
Der Inhalt des Buffers wird dann 0 terminiert um mögliche HACKERZ(TM) das mitschneiden zu erschweren.
```
##### interpreter_loop
```
In dieser Methode wird über die eingabe des Users itteriert. Diese Itteration endet mit eindem 0 Bit.
Interpretiert werden die Zeichen {+,-.>< []}.
Das Interpretierten dieser 8 Zeichen und das vorherige füllen eines Speichers sieht sehr nach der esotherischen Programmiersprache "Brainfuck" aus. Bei näherer Untersuchung der Interpretation der Zeichen bewahrheitet sich diese Vermutung.
```
# Brainfuck Programm schreiben
```
Als Eingabe schrieben wir also ein Programm in brainfuck, welches den String "1337" in seinen Speicher schreibt.
Eine solches Programm sähe dann folgendermaßen aus.

"-[----->+<]>--  > -[----->+<]>  > -[----->+<]> >  -[----->+<]>++++"
Das Programm schreibt die gewünschten Zeichen in den Speichr, funktioniert jedoch nicht.

Eine einfachere lösung bietet uns das das Brainfuck "," Symbol. Dieses dient zum einlesen von Chars.
Unsere Eingabe ist also ",>,>,>," Das Programm erwartet dann die Eingabe von 4 Chars, also geben wir "1337" ein.
```
```console
┌─[✗]─[root@parrot]─[/home/twotimer]
└──╼ #nc tank.informatik.hs-mannheim.de 3011
Show us your 1337 brain: ",>,>,>,"
1337
FLAG{what_a_brain_fuck}
```
```
Damit ist die Kondition erfüllt und das Flag  "FLAG{what_a_brain_fuck}" wird ausgegeben.
```

