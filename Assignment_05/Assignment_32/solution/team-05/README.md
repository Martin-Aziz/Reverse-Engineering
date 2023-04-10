# Assignment 31 Eigenes Crackme schreiben   
Team 5  
Kalle Macekas (1820774)  
Martin Havasi (2022986)  
Firat Ata Sahin (2025209)  

# Beschreibung Crackme und Schwachstelle 
Bei unserem Crackme handelt es sich um ein Programm welches ein Passwort entgegennimmt und auf Gültigkeit prüft. Das eingebene Passwort zusätzlich mit einem weiteren String erweitert um so die Sicherheit zu verbessern. Dieses Vorgehen bezeichnet man als "Salting", dabei wird der Klartext eines Passworts mit einem zufälligen String versehen und zusammengeführt. Die Aufgabe ist es, das korrekte Passwort zu finden inklusive dessen Salt.

Die Schwachstelle des Crackme (eine Art Log-In Interface) ist das nicht ein zufälliges, sich veränderndes Salt verwendet wird, sondern dieser als ein fest codierter Wert im Programm existiert. Das Salt ist zwar verschlüsselt, dies wurde aber mit einer leicht "Reverse-Engineer"-baren Caesar-Verschlüsselung realisiert.    

# Ausnutzung der Schwachstelle (Vorgehen)

Das Programm wird unter der Datei `crackmeTeam5` von uns bereitgestellt. Diese muss zusätzlich über den Konsolenbefehl
`chmod a+x crackmeTeam5` ausführbar gemacht werden. Alternativ kann die Datei auch über einen Quellcode und MakeFile erzeugt werden.

Mit dem `file`-command wird die Art der Datei ermittelt. In unserem Fall wird diese Datei als entsprechende Executable angezeigt. Auch wenn beim stumpfen Ausführen von unbekannten Executables normalerweise eher davon abgeraten wird, können wir versichern das bei diesem CrackMe darin keine Gefahr besteht.

Daher führen wir das Programm aus und erhalten folgende Textanweisung:
`Geben Sie das Passwort ein. Achtung es ist salty: `

Das Programm wartet wie erwartet auf eine Passworteingabe. Zusätzlich gibt es den kleinen Hinweis `Achtung es ist salty`. Wird eine falsche Eingabe getätigt erhalten wir zu dem die Fehlermeldung: `Not Salty enough tho`. Anhand dieser zwei Hinweise können folgende zwei Sachen abgeleitet werden. Das Passwort heißt `salty` und wird zudem mit einem unbekannten Salt versehen. Sprich das Passwort `salty` muss mit um einen zusätzlichen String erweitert werden um so die Flag zu erhalten.

Um weitere Informationen zu erhalten wir die Datei nun mit Ghidra näher betrachtet.

Wir betrachten über Ghidra die main-Methode. Da fällt uns unter anderem auf das eine Variable namens `tlas` existiert. Rückwärts ergibt das `salt`, ein weiterer Hinweis auf den Aufbau des Passwortes.

Nach Eingabe des Passwort wird ein kryptischer String `lZem[Z^` (siehe Z. 27 in Ghidra) mit einer Funktion `encrypt` verschlüsselt. Dies lässt vermuten das die Verschlüsselungsmethode sowie die Verschlüsselung resversibel sind.   
In Zeile 37 wird mithilfe von strcat die lokale Variable und Passwort `salty` mit einem String im Klartext konkateniert. In einer If-Bedingung wird der entsprechende Eingabe-String mit einem festen String(das Passwort mit dem Salt) verglichen. Stimmen die zwei Strings überein, sprich das richtige Passwort + Salt wurde eingeben, wird die Flag geprintet.  

Wir versuchen die Funktion `encrypt` zu reversen. Wir sehen das in der ersten while-Schleife alle Chars von einem String in ein Int Array umgewandelt werden. Auch die Funktion `charAsciiToVal` lässt darauf vermuten. Jeder Wert im Int-Array wird in Zeile 39 
um den Wert 7 subtrahiert. Zusätzlich erkennen wir eine Laufvariable die auf eine for-schleife schließen lässt. Wir sehen außerdem eine zweite Schleife die das neue Int-Array durchläuft, hier werden die neuen Werte des Arrays mithilfe der Funktionen `itoa` und `atoi` von der Standard-C-Library in einen String umgewandelt.

Da in der Verschlüsselung die einzlenen Chars eines String um einen bestimmten Wert innerhalb der Ascii-Tabelle verschoben werden können wir von einer Caesar-Verschlüsselung ausgehen. Für die Entschlüsselung benötigen wir also auch die Ascii-Tabelle. Mithilfe der Ascii-Tabelle können wir nun den Ascii-Wert des vorhanden Chars um 7 aufaddieren um so auf den ursprünglichen Wert zukommen.  

Verwenden wir diese simple Addition des Ascii-Wert auf den kryptischen String `lZem[Z^` von vorhin an. So erhalten wir den Salt `saltbae`. Kombinieren wir nun das Passwort `salty` mit dem herausgefundenem Salt `saltbae` erhalten wir `saltysaltbae`. Wird dieser String nun nach Eingabeaufforderung des Programmes eingeben, erhalten wir die `Flag: {messi}`. 