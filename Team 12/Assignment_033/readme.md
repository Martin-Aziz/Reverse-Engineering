# Crackme-Wettbewerb

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 17.01.2024** 📆

Versuchen Sie so viele Flags wie möglich zu sammeln, indem Sie die Crackmes der anderen Teams lösen.

  * [Team 01](team_01/)
  * [Team 02](team_02/)
  * [Team 03](team_03/)
  * [Team 04](team_04/)
  * [Team 05](team_05/)
  * [Team 06](team_06/)
  * [Team 07](team_07/)
  * [Team 08](team_08/)
  * [Team 09](team_09/)
  * [Team 10](team_10/)
  * [Team 11](team_11/)
  * [Team 12](team_12/)
  * [Team 13](team_13/)
  * [Team 14](team_14/)

Gewonnen hat das Team, das am meisten Flags gesammelt hat. Ihr eigenes Flag gehört mit dazu und sollte von Ihnen auch angegeben werden.

Für die Lösung dieser Aufgabe ist es __nicht zulässig__

  * das Flag aus dem Executable zu extrahieren
  * einen Debugger zu verwenden, um das Flag auszulesen
  * das Executable zu patchen, um das Flag ausgeben zu lassen

Sie können einen Debugger verwenden, um das Programm besser zu verstehen, nicht aber, um das Flag auszulesen.

Ihre Lösung muss das Programm durch geeignete Eingaben dazu bewegen, das Flag auszugeben. Diese Eingaben und die Begründung, warum sie das gewünschte Ergebnis bringen, sind Teil Ihrer Abgabe zu der Aufgabe.

Beschreiben Sie zu jedem Crackme, wie Sie vorgegangen sind und welche Eingaben das Flag ausgeben lassen. Sie können dies entweder in Form eines Writeups (pro Crackme) machen oder ein gut kommentiertes Skript (pro Crackme) schreiben. Man sollte nachvollziehen können, was Sie entdeckt haben und wie der Angriff abläuft. Da es sich um eine große Anzahl von Crackmes handelt, können Sie die Begründung stichpunktartig geben.

Schreiben Sie die Flags in die folgende Datei und laden Sie diese dann ausgefüllt in Ihr Repo hoch:

  * [flags](flags.txt)

**Achtung:** Es gibt Crackmes, die nicht direkt das Flag enthalten, sondern nur eine Funktion, die das Flag ausgibt. Deswegen finden Sie auf der [CTF-Webseite](http://tank.informatik.hs-mannheim.de) die Information, wo Sie dem Executable das Flag entlocken können. Hier ist ein Netzwerkdienst angegeben, z.B. `tank.informatik.hs-mannheim.de:3001`, d.h. auf Port `3001` des Servers `tank.informatik.hs-mannheim.de` lauscht das Programm auf Ihre Eingaben. Der Server ist nur aus dem Hochschulnetz erreichbar.

Verwenden Sie netcat (`nc`), um Ihre Eingaben an das Programm zu senden:

```console
$ nc tank.informatik.hs-mannheim.de 3001
Enter your name: Thomas
Hello Thomas
```

`telnet` ist an dieser Stelle keine gute Wahl, weil es die Daten nicht immer roh überträgt.


## Flags sammeln

Wenn Sie das Flag erhalten haben, so tragen Sie das Flag bitte auf der [CTF-Webseite](http://tank.informatik.hs-mannheim.de) ein. Bei der ersten Benutzung legt sich jedes Team einen Benutzer an, der wie das Team heißt.