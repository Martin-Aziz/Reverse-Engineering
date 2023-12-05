# Assignment: Analyse mit Ghidra (license_check)

## challenge 
```
Der Lizenzchecker verbirgt das Flag hinter einer Lizenzabfrage. Führt man das Script normal aus so bekommt man die Ausgabe:
```
```console
You have 0 license(s). Key: ababbabe
You need at least 1 license to win
```
```
Zwar haben wir einen Lizenz Schlüssel bekommen, jedoch scheint dieser nicht als solcher erkannt zu werden, da der Lizenzchecker behauptet wir hätten keinen.
```
```
Überprüfen wir den Lizenschlüssel mit einem hex-editor wie z.b. Hexedit bekommen wir folgende ausgabe:
```
```console
00000000   00 BE BA AB  AB 00 00 00  00                        .........
00000010
00000020
00000030
00000040
00000050
00000060
00000070
00000080
00000090
000000A0
000000B0
000000C0
000000D0
000000E0
000000F0
00000100
00000110
00000120
00000130
00000140
00000150
00000160
---  license_file.key       --0x0/0x9--0%--------------------------------------
```
```
 -Der HexOutput ist im little-Endian Format geschrieben. 
 - Nach bzw. vor dem kleinsten Byte ist ein 0 Byte vorhanden - vielleicht handelt es sich hierbei um einen Wert von Bedeutung

```
### Lizenzchecker mit ghidra untersuchen
### main funktion
```console
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
### Man kann  sehen, dass der Lizenzchecker die Lizenz hauptsächlich auf drei Tatsachen untersucht:
```
-das eine Lizenz den Hexwert 0xababbabe als Schlüssel enthält
-das eine eingelesene Datei als Lizenz funktioniert / eine Lizenz vorweisen kann. Dies wird überprüft indem ein Byte auf seinen Nullwert überprüft wird. Entspricht das "Lizenz"-Byte dem Wert Null, so wird die Datei nicht als Lizenz erkannt.
-das die Prüfsumme des Schlüssels dem Wert "0xd55c8f7f" entspricht
```
```
Sind diese Bedingungen erfüllt, so wird die win() funtion aufgerufen, die das Flag mit dem in der Lizenz enthaltenten Schlüssel mit XOR verschlüsselt.
```
```
Uns ist vorhin im Lizenzschlüssel das vorgeschobene Nullbyte aufgefallen. Vielleicht handelt es sich dabei ja um das Lizenz-Prüfbit der zweiten Bedingung. 
Also ändern wir mit einem hexeditor die HexWerte des Schlüssels von `00 BE BA AB  AB 00 00 00  0` in `01 BE BA AB  AB 00 00 00  0` um und führen den Lizenzchecker nocheinmal aus.
````
### Führt man das Script aus, bekommt man nun die Ausgabe:

```console
You have 1 license(s). Key: ababbabe
Checksum of license file not correct. You cheated!
```
```
Wir haben jetzt einen Lizenzschlüssel, der als Lizenz erkannt wird und den richtigen Schlüssel beinhaltet. 
Nur stimmt jetzt die Prüfsumme nichtmehr überein.
```
```
-zur Erstellung der Prüfsumme wurde CRC32 verwendet.
-CRC32 ein Algorithmus zur Überprüfung von Übertragungsfehlern
- daher sollen wir den Ansatz aus dem Lösungshinweis nachprogrammieren und somit den Lizenzschlüssel mit sinnfreien Bytes patchen um die gewünschte -Prüfsumme von `0xd55c8f7f` zu erzeugen.
 ```
 ```
 wir verwenden "https://github.com/rr-/pycrcmanip" um das CRC32 werte zu manipulieren.
 Lassen wir unsere manipulierte Lizenz nun wieder auf den gewünschten CRC32-Prüfsummenwert von 0xd55c8f7f flicken, so erhalten wir eine Datei mit den HexWerten:
01 BE BA AB  AB 00 00 00  00 0C 31 96  3D 
### Führen wir nun den manipulierten Lizenzchecker  aus, so erhalten wir folgende Ausgabe:
```console
[root@parrot]─[/home/twotimer/Downloads]
└──╼ #./license_check 
You have 1 license(s). Key: ababbabe
FLAG{crc32_will_never_be_secure}
```
# Das Flag lautet  
```
FLAG{crc32_will_never_be_secure}
```








