# Lösung: Executable mit Ghidra analysieren (license_check)

Man kann die Anzahl der Lizenzen (1. Byte) erhöhen, indem man dieses Byte auf den Wert `0x01` setzt und dann die verbleibenden Nullbytes (Bytes 9-13), die nicht benutzt werden so zu verändern, dass wieder der korrekte Hashwert herauskommt.

```console
$ ./license_check
You have 0 license(s). Key: ababbabe
You need at least 1 license to win

$ crc32 license_file.key
d55c8f7f

$ echo -ne "\x01\xBE\xBA\xAB\xAB\x00\x00\x00\x00" > license_file.key
$ hexedit license_file.key
$ ./license_check
You have 1 license(s). Key: ababbabe
Checksum of license file not correct. You cheated!

$ crc32 license_file.key
c2279b3c

$ python crc32_padding.py d55c8f7f c2279b3c
Padding-Bytes: 0xb029603d

$ echo -ne "\x01\xBE\xBA\xAB\xAB\xB0\x29\x60\x3D" > license_file.key
$ ./license_check
You have 1 license(s). Key: acabbabe
FLAG{crc32_is_still_not_secure}
```

Siehe auch den Source-Code des Programms:

  * [license_check.c](license_check.c)
