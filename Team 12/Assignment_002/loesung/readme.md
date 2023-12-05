

### 1: Auspacken des Archivs
### 2:aufrufen  `file *` 

| Datei                | Ausgabe von `file`               | Werkzeug                            | Inhalt |
|---|---|---|---|
| `a` | PNG image data, 100 x 100, 8-bit gray+alpha, non-interlaced | Bildbetrachter | Rick Astley |
| `b` |JPEG image data, ... , 250x157, components 3 | Bildbetrachter | JPG-Bild eines Egg Mac Muffins |
| `c` | PE32 executable (DLL) (console) Intel 80386 (stripped to external PDB), for MS Windows | `rabin2` | Shared Library für Windows mit nur zwei Exports: `GetDiskKey` und `GetDiskKey_Version` |
| `d` | PE32 executable (GUI) Intel 80386, for MS Windows | `rabin2` | Ausführbare Datei für Windows. 
| `e` | ELF 64-bit LSB shared object, ... , not stripped | `rabin2` | Bibliothek (shared object) für Linux x86, nicht gestrippt |
| `f` | ELF 64-bit LSB pie executable, ... , not stripped | `rabin2` | Ausführbares Programm für Linux. Ausführen der Datei ist zu riskant. |
| `g` | ELF 64-bit LSB shared object, ... , stripped | `rabin2` | Bibliothek (shared object) für Linux x86, gestrippt |
| `h` | ELF 64-bit LSB pie executable, ... , stripped | `rabin2` | Ausführbares Programm für Linux. |
| `i` | ELF 64-bit LSB relocatable, ... , not stripped | `rabin2` | Objekt-Datei mit der Main-Funktion eines Programms. |
| `j` | Compiled Java class data, version 61.0 | `javap` | Java-Klasse  `FlagPrinter`, die nur eine `main`-Methode enthält. |
| `k` | ASCII text | `less` | Rick Astley Song |
| `l` | data | `hexyl` | Binärdaten: ff ff 00 00 ca fe ba be 00 00 00 |
| `m` | Atari ST M68K contiguous executable | `strings` | Teil des Softwarepaketes Degas |
| `n` | gzip compressed data, was "n" ... | `gzip`, `less` | Komprimierte Version von k  |

## zu `e`, `f`, `g`, `h`

 Build-IDs

```console
e: ELF ... BuildID[sha1]=82d337f3906e7639b404001a5c501e9308848c80
f: ELF ... BuildID[sha1]=94fbda07657d2a358c1844e7682632621affde92
g: ELF ... BuildID[sha1]=82d337f3906e7639b404001a5c501e9308848c80
h: ELF ... BuildID[sha1]=94fbda07657d2a358c1844e7682632621affde92
```

`e` + `g` und `f` + `h` haben jeweils dieselben Build-IDs. Dies deutet darauf hin, dass es auch dieselben Bibliotheken sind -- nur  gestrippt.

## Zu `j`

`javap` muss man die Namen der Klasse wissen ,  mit dem `strings`-Kommando  kann man den finden , weil der Namen der Quelldatei ebenfalls in der Klasse gespeichert ist.

```console
$ strings j

SourceFile
FlagPrinter.java

```

Damit kann man die Datei umbenennen und `javap` verwenden:

```console
$ cp j FlagPrinter.class
$ javap -cp . FlagPrinter
Compiled from "FlagPrinter.java"
public class FlagPrinter {
  public FlagPrinter();
  public static void main(java.lang.String[]) throws java.lang.Exception;
  static {};
}
```

## zu `l`

Der Inhalt der Datei kann man  einfach mit einem Hexeditor  `hexedit` sehen  :

```console
$ hexedit l

│00000000│ ff ff 00 00 ca fe ba be ┊ 00 00 00                │××00××××┊000     │

```

## zu `m`

Da  handelt sich um eine alte Format

```console
$ strings -n 10
...
D:\DEGASART\ART1.SCPD:\DEGASART\PICS\D:\DEGASART\DEGASART.RSCTITLE.PC1
...
```

## zu `n`

Nach dem Auspacken sieht man, dass `n` nur eine komprimierte Version von `k` ist.
