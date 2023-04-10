# Assignment: Java-Klasse analysieren und patchen

 [Musterlösung](solution/)

In diesem Assignment werden Sie Java-Klassen analysieren und so verändern, dass ein Flag ausgegeben wird. Hierzu verwenden wir den [Java Decompiler (JD)](http://java-decompiler.github.io/).


## Flags

Die Executables enthalten ein Geheimnis (Flag), das in der Form `FLAG{GEHEMNIS}` ausgegeben wird, wenn Sie das richtige Passwort angeben. Leider kennen Sie das Passwort nicht.

_Beispiel:_

```console
$ ./password_check_1
Enter password: my_password
FLAG{a secret string}
```

Ihre Aufgabe ist es, diese Geheimnisse aus den Dateien zu extrahieren. Sie können versuchen, das Passwort oder direkt das Flag zu finden. Ein Brute-Force-Angriff auf das Passwort ist aber nicht Teil dieser Übung -- wir betreiben hier Reverse-Engineering und kein Cracking ;-)


## Aufgabe

Die folgende Datei gibt das Flag nicht aus, auch wenn Sie das richtige Passwort eingeben. Es ergibt also keinen Sinn, das Passwort aus der Datei extrahieren zu wollen.

  * [flag_printer.jar](flag_printer.jar)

Deswegen werden wir die Java-Klassen dekompilieren und untersuchen.

Da es sich hier um ein Java-Archive (jar) handelt, können Sie es einfach mit `java -jar flag_printer.jar` starten.

Gehen Sie wie folgt vor:

  * Installieren Sie den [Java Decompiler (JD)](http://java-decompiler.github.io/)
  * Untersuchen Sie das vorliegende Java-Programm und finden Sie die Stelle an der eine Prüfung der Eingabe erfolgt.
  * Schreiben Sie eine neue Klasse, die genauso heißt und dieselben Methoden hat, aber bei der Prüfung des Passwortes immer ein korrektes Passwort meldet.
  * Ersetzen Sie im JAR die Original-Klasse durch ihre eigene.
  * Starten Sie das Programm.

## Abgabe

Überlegen Sie sich eine sinnvolle Verzeichnis-Struktur, um dieses und die folgenden Assignments abzulegen.

  * Schreibern Sie auf, was Sie über die vorhandenen Klassen herausgefunden haben.
  * Schreiben Sie auf, wie Sie bei der Lösung der Aufgabe vorgegangen sind. Dies umfasst die eingegebenen Befehle und weitere Informationen, sodass ein fachkundiger Dritter Ihr Vorgehen nachvollziehen kann.
  * Checken Sie die geänderte Klasse und das veränderte JAR ein.

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.