# Radare 2

[Radare 2 ](https://rada.re) ist ein Reverse-Engineering-Werkzeug für die Kommandozeile. Es gibt mit [iato](https://github.com/radareorg/iaito/) auch eine grafische Oberfläche. Diese setzen wir hier aber nicht ein, sondern verwenden ein anderes Werkzeug namens Ghidra.

## Installation

Sie müssen Radare 2 installieren, bevor Sie es benutzen können. Unter Ubuntu können Sie eine ältere Version einfach mit `sudo apt install radare2` installieren. Diese Version reicht für diese und folgende Übungen vollständig aus. Möchten Sie eine aktuellere Version, so finden Sie diese auf [GitHub](https://github.com/radareorg/radare2/releases).

Die Version 4.1.x von radare2 hat Probleme mit der Instruktion `endbr64` (`f3 0f 1e fa`) am Anfang von Funktionen und zeigt diese als "invalid" an. Deswegen können Sie Funktionen nicht einfach mit `pd@ FNAME` disassemblieren, sondern müssen die Funktion über `s` suchen und dann mit `pd` disassemblieren. Um dieses Problem zu umgehen, installieren Sie die aktuelle Version.

## Wichtige Kommandos

### rabin2

`rabin2` ist ein Werkzeug, um Informationen über ein vorliegendes Binary zu erhalten. Sie übergeben `rabin2` den Pfad des Executables und legen über ein Flag fest, welche Informationen Sie sehen wollen. Beispielsweise zeit das Kommando `rabin2 -i /usr/bin/ls` die Imports des `ls`-Kommandos an.

Die wichtigsten Flags für `rabin2` sind:

  * `-z`: Strings in der `.data`-Section ausgeben
  * `-zzz`: Strings aus allen Sektionen ausgeben
  * `-i`: Imports ausgeben
  * `-E`: Exports ausgeben
  * `-l`: Verwendete Libraries ausgeben

### r2

`r2` ist das eigentliche Reverse-Engieering-Werkzeug mit einem integrierten Disassembler. Das zu analysierende Programm wird `r2` als Parameter übergeben, z.B. `r2 /usr/bin/ls`. Üblicherweise startet man `r2` mit dem zusätzlichen Parameter `-AA`, um das Programm auch direkt zu analysieren, also `r2 -AA /usr/bin/ls`. Will man Änderungen am Binary vornehmen, muss man es im Write-Mode mit `-w` öffnen.

Nach dem Start zeigt `r2` einen Prompt mit der aktuellen Adresse. Im folgenden sollen die wichtigsten Kommandos aufgelistet werden:

  * `s`: Sucht nach einem Symbol und springt an die Startadresse des Symbols, z.B. `s main`
  * `pd`: Gib ab der aktuellen Position ein Assembler-Listing aus (*p*rint *d*issassembly). Die Anzahl der Zeilen (Opcodes) kann als Parameter angegeben werden, also `pd 10` für 10 Zeilen.
  * `pdr`: Gibt ab der aktuellen Position ein Assembler-Listing aus, verwendet aber einen rekursiven Disassembler.
  * `v`: Startet den visuellen Modus, den man mit `q` wieder verlassen kann. Im visuellen Modus kann man durch `ENTER` die Anzeige verbreitern
  * `CTRL-D` verlässt `r2`
