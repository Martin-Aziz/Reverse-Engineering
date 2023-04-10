# Lösung: Java-Klasse analysieren und patchen

Die entscheidende Klasse ist `KeyCheck`. Diese hat folgenden Inhalt:

```java
public class KeyCheck {

    public boolean checkKey(String key) {
        return (key == "Its so magic" && false);
    }
}
```

Wir ersetzen Sie durch eine neue Version, die bei `checkKey` immer `true` zurückgibt:

```java
public class KeyCheck {

    public boolean checkKey(String key) {
        return true;
    }
}
```

Die neue Version wird compiliert `javac KeyCheck.java` und dann in das JAR eingefügt:

```console
$ javac KeyCheck.java
$ cp flag_printer.jar flag_printer_patched.jar
$ jar uf flag_printer_patched.jar KeyCheck.class
$ java -jar flag_printer.jar
Enter magic key: haha
FLAG{coffee babe}
```
