# Problem:

Der Lizenzchecker verbirgt die Flag hinter einer Lizenzabfrage. Führt man den Script normal aus so bekommt man die Ausgabe:



```
You have 0 license(s). Key: ababbabe
You need at least 1 license to win
```


Zwar haben wir einen Lizenz Schküssel bekommen, jedoch scheint dieser nicht als solcher erkannt zu werden, da der Lizenzchecker behauptet wir hätten keinen.

# Lösungsweg

Überprüfen wir den Lizenschlüssel mit einm hex-editor wie z.b. Hexedit bekommen wir folgende ausgabe: `00 BE BA AB  AB 00 00 00  00`

Uns fältt folgendes auf: 

 - Der HexOutput ist im little-Endian Format geschrieben. 
 - Nach bzw. vor dem kleinsten Byte ist ein 0 Byte vorhanden - vielleicht handelt es sich hierbei um einen Wert von Bedeutung

Untersuchen wir also den Lizenzchecker mit ghidra und schauen uns mal die main-function an.

Diese schaut folgendermaßen aus:


```

undefined8 main(void)

{
  int __fd;
  uint uVar1;
  ssize_t sVar2;
  long in_FS_OFFSET;
  byte local_118;
  uint local_117;
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  __fd = open("license_file.key",0);
  if (__fd < 0) {
    fprintf(stderr,"File %s not found\n","license_file.key");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  sVar2 = read(__fd,&local_118,0xff);
  if (sVar2 < 0) {
    fprintf(stderr,"Cannot read file %s\n","license_file.key");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  close(__fd);
  uVar1 = crc32(&local_118,sVar2);
  printf("You have %d license(s). Key: %x\n",(ulong)(uint)local_118,(ulong)local_117);
  if (local_117 != 0xababbabe) {
    puts("License key not correct");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  if (local_118 == 0) {
    puts("You need at least 1 license to win");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  if (uVar1 != 0xd55c8f7f) {
    puts("Checksum of license file not correct. You cheated!");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  win();
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return 0;
```

Wir sehen, das der Lizenzchecker die Lizenz hauptsächlich auf drei Tatsachen untersucht:

-das eine Lizenz den Hexwert 0xababbabe als Schlüssel enthält
-das eine eingelesene Datei als Lizenz funktioniert / eine Lizenz vorweisen kann. Dies wird überprüft indem ein Byte auf seinen Nullwert überprüft wird. Entspricht das "Lizenz"-Byte dem Wert Null, so wird die Datei nicht als Lizenz erkannt.
-das die Prüfsumme des Schlüssels dem Wert "0xd55c8f7f" entspricht

Sind diese Bedingungen erfüllt, so wird die win() funtion aufgerufen, die die Flag mit dem in der Lizenz enthaltenten Schlüssel mit XORG verschlüsselt.

Uns ist vorhin im Lizenzschlüssel das vorgeschobene Nullbyte aufgefallen. Vielleicht handelt es sich dabei ja um das Lizenz-Prüfbit der zweiten Bedingung. 
Also ändern wir mit einem hexeditor die HexWerte des Schlüssels von `00 BE BA AB  AB 00 00 00  0` in `01 BE BA AB  AB 00 00 00  0` um und führen den Lizenzchecker nocheinmal aus.

Nun bekommen wir die Ausgabe:

```
You have 1 license(s). Key: ababbabe
Checksum of license file not correct. You cheated!
```

Unsere Vermutung war also richtig. Wir haben jetzt einen Lizenzschlüssel, der als Lizenz erkannt wird und den richtigen Schlüssel beinhaltet. Nur stimmt jetzt die Prüfsumme nichtmehr überein.

Jedoch war der Entwickler wohl etwas unvorsichtig und hat keinen Kryptographischen Algorithmus zur Erstellung der Prüfsumme verwendet sondern CRC32.
Da CRC32 ein Algorithmus zur Überprüfung von Übertragungsfehlern ist und nicht mit streng kryptographischen Grundsätzen entwickelt wurde, ist es möglich systematisch Kollisionen zu erzeugen. Das bedeutet das CRC32 für zwei unterschiedliche Dateien die selbe Prüfsumme berechnet. Dies ist auch bei kryptographischen Algorithmen möglich, jedoch sind dort diese Kollisionen nicht systematisch produzierbar sondern sind für uns als Menschen zufällig verteilt.

Wir könnten den Ansatz aus dem Lösungshinweis nachprogrammieren und somit den Lizenzschlüssel mit sinnfreien Bytes patchen um die gewünschte Prüfsumme von `0xd55c8f7f` zu erzeugen.

Das könnten wir, doch zum Glück sind wir zwar faule aber auch kluge Informatiker und haben uns die als Lösungshinweis verlinkte Stackoverflow-Debatte genau durchgelesen. Deswegen verwenden wir einen der in den Kommentaren erwähnten Scripts, der uns diese Aufgabe abnimmt.

z.B.
	
- https://github.com/rr-/CRC-manipulator
oder
- https://www.nayuki.io/page/forcing-a-files-crc-to-any-value 

Lassen wir unsere manipulierte Lizenz nun wieder auf den gewünschten CRC32-Prüfsummenwert von `0xd55c8f7f` flicken, so erhalten wir eine Datei mit den HexWerten:
`01 BE BA AB  AB 00 00 00  00 0C 31 96  3D `

Führen wir nun den Lizenzchecker mit dieser manipulierten Lizenz aus, so erhalten wir folgende Ausgabe:
```
You have 1 license(s). Key: ababbabe
FLAG{crc32_is_still_not_secure}
```

Der Flag können wir nur zustimmen. CRC32 ist für kryptographische Zwecke ungeeignet, da es nicht verhindern kann das eine Datei nicht doch manipuliert ist.

