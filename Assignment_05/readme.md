# Assignment: Exports und Imports mit rabin2 untersuchen

**🎓 Benotetes Assignment 🎓**

📆 **Fällig: 18.10.2022** 📆 [Musterlösung](solution/)

In diesem Assignment geht es darum, durch die statisch Analyse einer Datei Aussagen über deren Funktionalität und die Intentionen des Programmierers zu machen. Hierzu werden wir das `rabin2`-Tool aus dem Radare 2 Paket verwenden.


## Radare 2

Für diese Übung werden wir das Kommandozeilen-Reverse-Engineering-Werkzeug Radare 2 einsetzen. Sie finden Tipps zur Installation und Verwendung in der [Kurzanleitung](../help/radare2.md).

## Aufgabe

Das Werkzeug `rabin2` kann dazu verwendet werden, die exportierten und importierten Funktionen einer Binärdatei zu untersuchen. Damit sind die Funktionen gemeint, die das Programm zur Laufzeit aus der Standardbibliothek importiert und benutzt. Die Importe lassen sich mit `rabin2 -i DATEINAME` ausgeben, die Exporte mit `rabin2 -s DATEINAME`.

Da es sich hier um eine Shared-Library (Dateiendung unter Linux `.so`) handelt, die möglicherweise zu einer Malware gehört, sind insbesondere die Funktionen interessant, die von der Bibliothek exportiert werden.

Nehmen Sie sich die folgende Datei vor und verwenden Sie `rabin2`, um sich die Importe und Exporte anzeigen zu lassen.

  * [payload_2.so](payload_2.so)


## Hinweis

Bei dem Executable handelt es sich um ein Programm unbekannter Funktionalität, wie man sie z.B. bei der Untersuchung von kompromittierten Rechner finden könnte. Es kann gut sein, dass es sich um eine _Malware_ handelt, welche bei der Ausführung Schaden verursacht, bis hin zur Zerstörung aller Daten auf dem Rechner. Deswegen sollten Sie die Datei __auf keinen Fall__ ohne Schutzmaßnahmen (virtuelle Maschine etc.) __ausführen__. Die hier vorgenommene Analyse kommt ohne Ausführung der Datei aus und ist insofern sicher auch ohne Schutzmaßnahmen durchführbar.

Sie müssen in der Realität damit rechnen, dass die Malware Schwachstellen in den von Ihnen verwendeten Werkzeugen nutzt, um bei einem Reverse-Engineering Ihren Rechner anzugreifen. Da wir uns hier in einem Übungskontext befinden, ignorieren wir dieses Problem.


Sie werden bei den Symbolen eine Reihe von Funktionen aus der C-Standard-Bibliothek sehen. Rufen Sie die Hilfeseiten zu den Funktionen auf, z.B. `man memset`, oder googeln Sie die Funktionsnamen. Versuchen Sie aus diesen Informationen abzuleiten, was das Programm möglicherweise tut.

Hinweis: Da Malware oft versucht, die Importe über diverse Techniken zu verschleiern, bedeutet die Abwesenheit von "gefährlichen" Bibliotheksfunktionen nicht zwingend, dass ein Programm gutartig ist. Im vorliegenden Fall macht es Ihnen das Programm aber einfach und verwendet keine Techniken zur Verschleierung der Importe.

## Abgabe

  * Schreiben Sie auf, was Sie über die Datei herausgefunden haben.
  * Geben Sie eine Einschätzung ab, ob es sich möglicherweise um eine Malware handelt.
  * Welche Art von Malware könnte vorliegen? Was macht sie wahrscheinlich?

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.