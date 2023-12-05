# Assignment: Dateien mit `file` untersuchen

 [Musterlösung](solution/)

In diesem Assignment werden Sie unbekannte Dateien mit dem `file`-Werkzeug untersuchen. Hierbei geht es darum, in einem allerersten Schritt einer Analyse herauszufinden, um was für Dateien es sich handeln _könnte_.


## Aufgabe

Das Werkzeug `file` kann dazu verwendet werden, um den Typ einer Datei zu erkennen. Hierzu analysiert `file` den Inhalt und vergleicht ihn mit einer Datenbank von bekannten Dateitypen. Die Ausgabe ist zwar nicht absolut zuverlässig, immerhin aber ein erster Hinweis auf den Inhalt. Mit dieser Information kann man dann weitere Analysen durchführen, die zu dem jeweiligen Dateityp passen.

Gegeben sind die folgenden unbekannten Dateien in Form eines Archivs, die Sie in einem ersten Schritt mit `file` untersuchen werden:

  * [files.zip](files.zip)

Entpacken Sie das Archiv und wenden Sie dann auf jede Datei das `file`-Kommando an.

Sie bekommen zu einer Datei Informationen, ähnlich der folgenden:

```console
$ file files.zip
files.zip: Zip archive data, at least v2.0 to extract, compression method=deflate
```

Schauen Sie sich die Informationen zu jeder Datei an und notieren Sie sich Ihre Erkenntnisse.

Ausgehend von den gewonnenen Erkenntnissen können Sie versuchen, die Dateien mit Ihnen bekannten Werkzeugen weiter zu untersuchen, z.B. können Sie Bilddateien in einem Bildbetrachter ansehen. **Auf keinen Fall sollten Sie ohne Vorsichtsmaßnahmen Dateien ausführen, da sie ein Risiko darstellen könnten!***


## Abgabe

  * Schreiben Sie auf, um welchen Dateityp es sich wahrscheinlich handelt.
  * Nennen Sie weitere Werkzeuge, mit denen Sie die Datei untersucht haben.
  * Beschreiben Sie, was Sie zum Inhalt der Datei herausgefunden haben, falls dies möglich war.

Die Abgabe erfolgt über das Repository, das Ihrem Team zugeordnet ist.