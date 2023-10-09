# Assignment 31: Eigene Crackme schreiben

In dieser Aufgabe geht es darum, die Flag aus der Datei `crackme`zu entschlüsseln. Hilfreich ist dabei auch ein eigenes Skript zu schreiben.

`Hinweis`: Nutzt alles, was ihr bereits gelernt hat, z.B. zur statischen Analyse (Dekompilieren in Ghidra), etc.

---

## Allgemeine Informationen
Das Werkzeug "file" zeigt die folgende Informationen für die bereitgestellte Datei `crackme`ohne Erweiterung:

		crackme: ELF 64-bit LSB shared object, x86-64, version 1 (SYSV), dynamically linked,
		interpreter /lib64/ld-linux-x86-64.so.2, for GNU/Linux 3.2.0, not stripped

Wenn wir die Datei ausführen, wird eine einfache Anwendung gezeigt:

		./crackme
		Usage: ./crackme FLAG

Wir geben eine Kauderwelsch-Flag ein:

		./crackme deadbeef
		Wrong flag

## Statische Analyse

Wenn wir `strings crackme` ausführen, finden wir sofort die Zeichenfolge `sup3r_s3cr3t_k3y_1337`. Glücklicherweise ist sie falsch, denn das wäre ja zu trivial gewesen.
Über "sup3r_s3cr3t_k3y_1337" befindet sich eine weitere interessante Zeichenfolge: `You found a flag! %s`
Starten wir Ghidra und analysieren wir die ausführbare Datei. Das Fenster "Funktionen" zeigt allerdings nicht viele Funktionen an.

Zunächst schauen wir uns die main-Funktion an. Die ursprüngliche Datei findet ihr hier: [crackme.c](/ree-lecture/team-07/src/branch/master/Assignments/Assignment_31/solution/crackme.c).

Die Zeile

    else { sVar2 = strlen(*(char **)(param_2 + 8)); if (sVar2 == 0x15)

sagt uns die gewünschte Länge des Flags (21), wobei param_2 + 8 (sVar2) das angegebene Flag ist.
Wenn die angegebene Flagge nicht 21 Zeichen hat, wird sofort "Wrong Flag" angezeigt.
Es folgt eine weitere, kompliziertere Prüfung. Wir treffen auf unseren alten Freund: "sup3r_s3cr3t_k3y_1337". Auffällig ist, dass diese Zeichenfolge genau 21 Zeichen hat.

Dieser "Schlüssel" wird als Initialisierungsschlüssel verwendet, wie man im folgenden dekompilierten Code sehen kann:

    for (local_90 = 0; local_90 < 0x15;  local_90 = local_90 + 1) {
    	local_88[local_90 + 0x18] = "sup3r_s3cr3t_k3y_1337"[local_90] + -0x22;}

oder besser (aus Original-Datei):

    for ( i = 0; i < 21; i++ ) // Schleife durch Initialisierungsschlüssel
    { v6[24+i]= "sup3r_s3cr3t_k3y_1337"[i] - 34; // Ablenkungsmanöver
    }
local_88 (oder v6) bezeichnet ein Byte-Array der Größe 24 und ist eine Art Puffer: `int local_88 [24]`

Vom Schlüssel wird von jedem Zeichen 34 subtrahiert. Beachte auch, dass der Index des Arrays bei jeder Iteration um 24 erhöht wird.
Daher ist die Struktur des Arrays "buffer" wie folgt: {24 * 0x00} {sup3r_s3cr3t_k3y_1337}
Unterhalb dieser Schleife befindet sich eine lange Liste von 21 Anweisungen. Jedes Mal wird local_88 (v6) mit einem einzelnen Byte gefüllt, beginnend mit 0x37 und endend mit 0x68.
Die 0x00-Bytes werden durch Daten ersetzt. Schauen wir uns an, wohin das führt:

    local_88[0] = 0x37;
    local_88[1] = 0x3f;
    local_88[2] = 0x2f;
    local_88[3] = 0x76;
    local_88[4] = 0x2b;
    local_88[5] = 0x62;
    local_88[6] = 0x28;
    local_88[7] = 0x21;
    local_88[8] = 0x34;
    local_88[9] = 0xf;
    local_88[10] = 0x77;
    local_88[11] = 0x62;
    local_88[12] = 0x48;
    local_88[13] = 0x27;
    local_88[14] = 0x75;
    local_88[15] = 8;
    local_88[16] = 0x56;
    local_88[17] = 0x6a;
    local_88[18] = 0x68;
    local_88[19] = 0x4e;
    local_88[20] = 0x68;

Es gibt eine weitere Iteration von local_8c (oder j=0 bis j<21).
Diese Schleife dient dazu, die Benutzereingabe aus param_2+8 zu überprüfen. Jedes einzelne Zeichen der Eingabe wird mit local_88[local_8c] (oder: v6[j]) verglichen:

        if ((int) (char) (byte)local_88[local_8c + 0x18] ^
    * (byte *)((long) local_8c + *(long *) (param_" + 8))) != local_88[local_8c])

^ steht für die XOR-Operation. Es war die ganze Zeit eine XOR-Verschlüsselung.
Um das Kennzeichen zu erhalten, müssen wir einfach alles wiederholen, was vorher gemacht wurde, und XOR (byte)local_88[local_8c + 0x18] mit local_88[local_8c]  (bzw. (v6[24+j])) mit v6[j]).
Der Skript in Python tut genau das:
[skript.py](/ree-lecture/team-07/src/branch/master/Assignments/Assignment_31/solution/script.py).
Wirf einen Blick ins nächste Abschnitt.

## Python-Skript gibt Flag zurück

Dieser Code implementiert eine einfache XOR-Chiffre, um eine durch die Schlüsselzeichenfolge dargestellte Nachricht zu verschlüsseln.

    FlagLength = 21

    Key = "sup3r_s3cr3t_k3y_1337"

    buffer = bytearray(FlagLength + 30) //Puffer wird zum Speichern der verschlüsselten Nachricht verwendet

    for i in range(FlagLength):

    buffer[i + 24] = ord(Key[i]) -34 //der ASCII-Wert jedes Zeichens wird in eine Ganzzahl umgewandelt und mit 34 subtrahiert

    xorStream = bytearray([0x37, 0x3F, 0x2F, 0x76, 0x2B, 0x62, 0x28, 0x21, 0x34, 0xF, 0x77, 0x62, 0x48, 0x27, 0x75, 0x8, 0x56, 0x6A, 0x68, 0x4E, 0x68]) //Dieser xorStream wird als Schlüssel zum Verschlüsseln der Nachricht verwendet

    buffer[:len(xorStream)] = xorStream //xorStream wird mittels Slicing an den Anfang des Pufferobjekts kopiert

    for i in range(FlagLength):

    buffer[i] ^= buffer[i + 24] //XOR-Verknüpfung

    print(buffer[:FlagLength].decode("ASCII")) //Als ASCII-Zeichen dekodiert

Nun führen wir die `crackme` erneut aus und dieses mal mit dem Python Skript: "./crackme 'python3 script.py'".
Wir erhalten als Ergebnis: `You found a flag! flag{_y0u_f0und_key_}`
