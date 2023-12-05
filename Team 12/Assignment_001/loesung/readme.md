
 `KeyCheck klasse `. Diese hat folgenden Inhalt:

```java
public class KeyCheck {

    public boolean checkKey(String key) {
        return (key == "Its so magic" && false);
    }
}
```

Es muss true zürckgegeben werden.

```java
public class KeyCheck {

    public boolean checkKey(String key) {
        return true;
    }
}
```

Die neue Version wird compiliert `
javac KeyCheck.java` und dann in das JAR eingefügt:

```konsole
$ javac KeyCheck.java
$ cp flag_printer.jar flag_printer_patched.jar
$ jar uf flag_printer_patched.jar KeyCheck.class
$ java -jar flag_printer.jar
Enter magic key: haha
FLAG{coffee babe}
```
