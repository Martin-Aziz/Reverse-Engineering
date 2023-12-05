# Executable mit Hex_editor patchen

## Ausführen der Datei mit gdb
```
$ chmod +x password_check_5   #Datei ausführbar machen
$ gdb password_check_5        #Datei mit gdb ausführen

GNU gdb (Ubuntu 9.2-0ubuntu1~20.04.1) 9.2
Copyright (C) 2020 Free Software Foundation, Inc.
License GPLv3+: GNU GPL version 3 or later <http://gnu.org/licenses/gpl.html>
This is free software: you are free to change and redistribute it.
There is NO WARRANTY, to the extent permitted by law.
Type "show copying" and "show warranty" for details.
This GDB was configured as "x86_64-linux-gnu".
Type "show configuration" for configuration details.
For bug reporting instructions, please see:
<http://www.gnu.org/software/gdb/bugs/>.
Find the GDB manual and other documentation resources online at:
    <http://www.gnu.org/software/gdb/documentation/>.

For help, type "help".
Type "apropos word" to search for commands related to "word"...
Reading symbols from password_check_5...
(No debugging symbols found in password_check_5)

(gdb) run                     #Datei runnen
Starting program: /home/oleg/Desktop/REE/auf15/password_check_5 
Enter password:
```


