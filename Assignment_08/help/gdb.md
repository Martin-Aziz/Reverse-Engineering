# Der GNU Debugger (gdb)

## Installation

Der GNU Debugger (gdb) ist auf den meisten Systemen bereits installiert. Sollte er bei Ihnen fehlen, können Sie ihn mit dem Kommando `sudo apt install gdb` installieren.

## Konfiguration

`gdb` verwendet standardmäßig die AT&T-Syntax für die Ausgabe von Assembler-Befehlen. Da dies aber die unüblichere Form ist, werden wir ausschließlich die Intel-Syntax verwenden. Sie können `gdb` nach jedem Aufruf mit dem Kommando `set disassembly-flavor intel` auf die Intel-Syntax umstellen. Einfacher ist es jedoch, diese Einstellung dauerhaft abzulegen. Erzeugen Sie hierzu einfach eine Datei `.gdbinit` in Ihrem Home-Verzeichnis und schreiben Sie dort das Kommando für die Syntax hinein.

```console
$ echo "set disassembly-flavor intel" > ~/.gdbinit
```

## Wichtige Kommandos

Sie laden ein Programm, indem Sie den Pfad zum Programm nach dem Aufruf von `gdb` angeben, also z.B. `$ gdb ./crackme`.

Wenn Sie `gdb` gestartet haben, können Sie hinter dem Prompt `(gdb)` Ihre Kommandos eingeben. Einige wichtige Kommandos sind:

  * `run` oder `r`: Startet das Programm
  * CTRL-C: Unterbricht das Programm
  * `backtrace` oder `bt`: Zeigt den Stack an
  * `frame NO`: Springt zum Frame mit der angegebenen Nummer
  * `disassemble` oder `disas`: Disassembliert die Funktion für den aktuellen Stack-Frame
  * `break` oder `b`: Setzt einen Breakpoint. Hierbei können Sie angeben
    - Funktionsnamen: `break strcmp`
    - Adresse: `break *0x7ffff7f39660`
  * `continue` oder `c`: Setzt das Programm fort
  * `x`: Untersucht eine Speicherstelle, d.h. der übergebene Wert wird als Adresse interpretiert
    - als Hexadezimalwert: `x /x $rdi` oder `x /x 0x555555559ac0`
    - als Dezimalwert: `x /d $rdi` oder `x /d 0x555555559ac0`
    - als Fließkommazahl: `x /f $rdi` oder `x /f 0x555555559ac0`
    - als String: `x /s $rdi` oder `x /s 0x555555559ac0`
    - als Instruktionen: ` x /i $rip` oder `x /i 0x555555559ac0`
    - es können mehrere Werte auf einmal ausgegeben werden, z.B. `x /10x $rdi`
  * `print` oder `p`: Gibt einen Wert aus
    - eines Registers: `p $rdi`
    - eines Ausdrucks: `p 2*2`
    - Sie können auch die Flags `/x`
  * CTRL-D: Beendet den Debugger

Sowohl `print` als auch `x` unterstützen sogenannte Formatzeichen, die angeben, wie der Wert zu interpretieren und formatieren ist:

  * `x`: Hexadezimal
  * `d`: Vorzeichenbehaftete Dezimalzahl
  * `u`: Vorzeichenlose Dezimalzahl
  * `o`: Octal
  * `t`: Binär
  * `a`: Adresse (hexadezimal + Offset zu nächsten bekannten Symbol)
  * `c`: ASCII-Zeichen
  * `f`: Fließkommazahl
  * `s`: String (nur `x`)
