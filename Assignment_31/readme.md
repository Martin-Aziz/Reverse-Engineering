# Assignment: Eigenes Crackme schreiben

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 08.01.2023** 📆

Nachdem Sie jetzt viele Erfahrungen im Reverse Engineering gewonnen haben, sollen Sie in diesem Assignment ein eigenes _Crackme_ erstellen. Dieses wird dann im nächsten Schritt von anderen Teams geknackt werden.

## Aufgabe

Schreiben Sie ein Crackme, das von anderen Teams durch Reverse Engineering gelöst werden kann. Das Crackme sollte ein Flag enthalten und dieses nur ausgeben, wenn man eine Schwachstelle in Ihrem Programm erfolgreich ausnutzt. Das Format des Flags ist `FLAG{geheimer_text}`.

Das andere Team darf Ihr Programm debuggen und mit beliebigen Tools reverse engineeren. Die Ausgabe des Flag muss aber letztendlich durch entsprechende Eingaben provoziert werden, welche eine Sicherheitslücke oder einen Logikfehler ausnutzen. Orientieren Sie sich an den Crackmes, die Sie bereits im Rahmen der Vorlesung gelöst haben.

Die Wahl der Sicherheitslücke ist Ihnen überlassen. Sie sollten das Crackme allerdings so gestalten, dass es von einem anderen Team auch gelöst werden kann aber auch nicht trivial ist.

Ein paar Tipps zu Sicherheitslücken finden Sie [hier](../help/sicherheitsluecken.md)
## Abgabe

Ihre Abgabe besteht aus:

  * Dem kommentierten Quelltext des Crackmes in C.
  * Einem Makefile, um das Crackme bauen zu können.
  * Ein fertig compiliertes Executable des Crackmes.
  * Einer Musterlösung für das Crackme
    - Textuelle Beschreibung der Schwachstelle und des Angriffs
    - Skript, das die Schwachstelle ausnutzt und das Flag ausgibt

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.