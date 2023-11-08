### Gefundene Flag:
- FLAG{humpy dumpy}

---
### Probleme:

- GCore benötigt die Prozess ID um den korresponiderenden Speicher herauszusuchen, doch der Prozess wird mit dem  `top` command nicht angezeigt. Vermutlich weil der Prozess nicht genügend Resourcen verbraucht um angezeigt zu werden weil `top` nach CPU-Time sortiert. (Alternativ kann das auch vom dumpme script bewusst verursachtes Verhalten sein)

Kennt man die PID bereits, lässt er sich durch `top`jedoch finden, was für Sortiertheorie spricht.

Lösungansatz: Wir installieren uns htop. Ein verbesserter Prozessmanager.

<br>

- 
  ```
  User:$ grep FLAG gcore-dump.205517
  grep: gcore-dump.205517: binary file matches
  ```
  Der Grep Befehl liefert nur die Aussage das es sich um BinärInhalt haltet
  
  <br>

    ```
    User:$  grep -a FLAG gcore-dump.205517 
    �E�S�@ÜS����S����S����S�`WCV�<�S�@wzS�`�zS�@wzS�1���5�Ҧ�p�F 3��0�S��0�S��" zzS� zzS�����������:2�PzzS���:2�pzS��vzS�UCV�)UCV�2�S��&UCVP- UCVP0 UCV�2�S��&UCV�zS�P�S�`a�S�LޘS���S��2�S��*�S�į�S�`=2��m=2��8�S�Te=2�ELF>P�@��!@8@BA@@0>0>0>������D�D�x�x�H!�X!�X!�O`%�{!��!��!�PPP0���DD�H!�X!�X!S�tdPPP0P�tdL>L>L>�p�pQ�tdR�td�����D*@�V<- N�H&�ЎNUi8�HZ����s��,��.���=GNU�0\� ���E��X� p
                    ��:fȀ�3�
                            P	 �	�
                                            $ ($�$Z0X��DB(�:C�T�IPQ�P  H�P��!�����۴0P�D2 Z�
    ```
    grep kann die Datei auch nicht vernünftig als Text lesen (vermutlich wegen dem Text-Encoding)

Lösungsansatz: wir lassen uns mit dem `string` Befehl alle erkennbaren Strings in eine Datei schreiben und suchen anschließend mit grep in der "gefilterten" Datei.

Alternativ kann man die gcore-dump Datei auch mit einem Texteditor der Wahl (z.B. nano) öffnen und nach den String "FLAG" suchen.



---
### Vorgehen:

Wir führen die Datei dumpme aus und finden über htop die PID heraus.

In unserem Falle handelt es sich dabei um die PID 205517

Den genutzten Speicher des Prozesses schreiben wir in die Datei `gcore-dump.205517 `mit dem Befehl

```
User:$ sudo gcore -o gcore-dump 205517`
```




Anschließend führen wir den Befehl

```
User:$ strings gcore-dump.205517 >> strings.dump
```
aus und filtern so alle direkt erkennbaren Strings in die Datei `strings.dump`

anschließend suchen wir mit grep nach einer Flag und bekommen folgende Ausgabe:

```
User:$ grep FLAG strings.dump 
FLAG{humpy dumpy}
```





