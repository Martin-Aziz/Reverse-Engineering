# Assignment: Erstellen eines eigenen Crackme's
## Die gewählte Sicherheitslücke
Wir haben uns dazu entschieden die die `Formatstring-Schwachstelle` für unser Crackme auszunutzen.

Wir erwaten eine Eingabe des Users, diese wird dann über die `printf`-Funktion ausgegeben. Dort geben wir allerdings kein Format für die Eingabe ein. Dadurch werden die Eingaben nicht validiert. Das kann einem Angreifer ermöglichen die Ausgabe der Funktion zu manipulieren um zum Beispiel Speicheradressen zu referenzieren und beliebe Stellen im Speicher zu lesen oder zu beschreiben.

Beispiel:
```console
Enter password: %p %p %p %p %p
0x1 0x1 0x7ffff7f9aaa0 (nil) (nil)
```

## Der Plot Twist
Da wir es unseren Kommilitonen nicht zu einfach machen wollten, wird jedes Zeichen der Eingabe (außer Sonderzeichen) nochmal mit der Caeser Chiffre mit 20 Schritten verschlüsselt. Also führt `%s` Beispielsweise nicht zur gewünschten Ausgabe als String, sondern einfach zu einer Ausgabe von `%y`.

```console
Enter password: %s
%y
```

## Weitere Maßnahmen
Um die einfache Lösung über Tools wie `strings` zu vermeiden, haben wir das Flag als xor Verschlüsselten Hex-String hinterlegt und entschlüsseln es erst zur Laufzeit.
Außerdem haben wir das Executable gestrippt.

## Die Lösung
Um an das Flag zu kommen kann beispielsweise folgendes Eingegeben werden. 

```console
Enter password: %j %j %j %j %j %j %m
0x1f 0x20 0x7b 0x7f2d47d3bf10 0x7f2d47d63040 0x7fff00000008 FLAG{Mittwochs gibts Kartoffeln}
```

**FLAG{Mittwoch gibts Kartoffeln}**