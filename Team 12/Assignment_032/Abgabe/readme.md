# Eigenes Crackme schreiben Abgabe
### *Dem kommentierten Quelltext des Crackmes in C. Alle Warnings, die Sie nicht entfernen konnten, sind unterdrückt.
- [Kommentierten Quelltext](https://gitty.informatik.hs-mannheim.de/ree-lecture/team-12/src/branch/master/Assignment_032/Abgabe/kommentiertenQuelltext.c)
### *Einem Makefile mit dem Namen Makefile, um das Crackme bauen zu können mit den passenden Compileroptionen, einschließlich -Wall. Das Executable, das erzeugt wird heißt crackme.
- [Makefile](https://gitty.informatik.hs-mannheim.de/ree-lecture/team-12/src/branch/master/Assignment_032/Abgabe/Makefile)
### *Eine Datei flag, welche nur das Flag enthält.
- [Flag](https://gitty.informatik.hs-mannheim.de/ree-lecture/team-12/src/branch/master/Assignment_032/Abgabe/Flag.txt)
### *Ein fertig compiliertes Executable des Crackmes.
- [Crackme](https://gitty.informatik.hs-mannheim.de/ree-lecture/team-12/src/branch/master/Assignment_032/Abgabe/crackme)
# *Einer Musterlösung für das Crackme
#### Malloc never fails
```
Wir haben uns entschieden, die Schwachstelle "Malloc never fails" zu behandeln. Wenn ein Fehler auftritt, gibt malloc normalerweise einen Nullpointer zurück, der üblicherweise erkannt und entsprechend behandelt werden sollte. In unserem Szenario geben wir einen Hinweis auf die richtige Eingabe, wenn eine zu große Zahl eingegeben wird.
```
#### vorgehenweise :
```
Der Bildschirm fordert den Agenten auf, einen speziellen Passcode einzugeben, um den Zugriff zu aktivieren. 
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file:
```
```
Wenn ein ungültiges Passwort eingegeben wird, wird ein Standardtext ausgegeben
```
``` console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 665664t4
Accessing personal identification required: Verifying... Access granted. Welcome, Agent. Proceed with caution.
```
```
Wenn beide Eingaben falsch sind, wird ein Alert ausgegeben.
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 43343
Accessing personal identification required: 4334
Spy Alert !!!!!!!!!!!!!!!!!!!
```
```
Sobald die Speicheranforderung zu groß wird, gibt Malloc einen Nullpointer zurück. Dies könnte dazu führen, dass ein Null-Byte willkürlich im Speicher geschrieben wird.
Der Agent sollte eine große Zahl eingeben, sodass malloc einen Nullpointer zurückgibt.
```
```
Hier ist eine falsche Flagge zu sehen, begleitet von dem Text 'Malloc never fails' und einigen Hexadezimalzahlen. Der Agent muss diese Zahlen analysieren und versuchen herauszufinden, was sie bedeuten. 378 in Dezimal ist 888,16D61 = 93537,2C61761=46536545 ,025DBF5B=39698267 .
```
```
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 99999999999999999999999999999999999
Access denied. Security breach detected. Initiating lockdown protocol.
       /\     /\
      /  \___/  \
     /    | |    \
    /     | |     \
   /______________\
  / |          |   \
 /  |   FALSE  |    \
|   |   FALG{  |    |
|   |   Malloc |    |
|   |   never  |    |
|   |   fail,  |    |
|   |   16D61, |    |
|   |     378, |    |
|   |   2C6176 |    |
|   |   1,025D |    |
|   |   BF5B,   |    |
|___|__________|____|
```
```
Nachdem der Agent herausgefunden hat, dass '888' das Passwort ist und die Zahl '378' in Dezimal umgewandelt hat, muss er noch herausfinden, was der Begriff 'binary access code' bedeuten könnte.
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 888
Secure code verification required. Enter binary access code:

```
```
Nachdem er die Zahlen als Eingabe ausprobiert hat und herausgefunden hat, dass er  '2C61761' als Binärzahl eingeben soll, sieht er die richtige Flagge.
"FLAG{REE_LECTURES_WERE_FUN}"
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ ./crackme
Welcome, Agent. Enter the passcode to access the secure file: 888
Secure code verification required. Enter binary access code: 10110001100001011101100001
Access granted. Decrypting secure file...
  .-----------------.
 /                 /\
/                 /  \
|      _________|    |
|     |         |    |
|     |         |    |
FLAG{REE_LECTURES_WERE_FUN}
|     |         |    |
|     |         |    |
|     |_________|    |
|___________________|
File decrypted successfully. Extracted information: CONFIDENTIAL.
```
### *Skript, das die Schwachstelle ausnutzt und das Flag ausgibt
- [Skript](https://gitty.informatik.hs-mannheim.de/ree-lecture/team-12/src/branch/master/Assignment_032/Abgabe/script.py)
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ python3 script.py

                             / \  //\
                  |\___/|      /   \//  .\
                  /O  O  \__  /    //  | \ \           * Reverse Engineering! *
                 /     /  \/_/    //   |  \  \
                 @___@'    \/_   //    |   \   \
                    |       \_|/   ,/\,,_______\
                    |    \    /   |    /    |   \
                    |     \_ /  |  \//    \   |
                   \  /  __  \   /  /   __/   /
                    \  /   \_\_  /  |  /_____/  |
                     \____\___/  |  /          /
                      \_       \/  /          |
                      | \  |/  \/  |          |
                      |  \//\__/    \         /
                     _|  /  \/   |  \       /\
                    /   /   /  |   \  \_   /
                   /_____/   |____|\   \ |
                   |   \______|----|_\   \  \
                   |_________   \_____|   \   \
                              \__\  \__\    \   \
                                 |   |       \   \
                                 |   |        \___\

Select the information you have:
1. Input
2. Password and Binary Access Code
3. Exit
Enter your choice:
```
```
Der Benutzer kann ein Skript verwenden, um Eingaben vorzunehmen. Alternativ, wenn er sowohl das Passwort als auch den Binary Access Code hat, kann er die Flagge sehen. Das Skript startet das Programm 'crackme' parallel und gibt Eingaben ein
```
```console
┌──(mindh㉿TT)-[/mnt/c/Users/TT/Documents/GitHub/team-12/Assignment_032/Abgabe]
└─$ python3 script.py

                             / \  //\
                  |\___/|      /   \//  .\
                  /O  O  \__  /    //  | \ \           * Reverse Engineering! *
                 /     /  \/_/    //   |  \  \
                 @___@'    \/_   //    |   \   \
                    |       \_|/   ,/\,,_______\
                    |    \    /   |    /    |   \
                    |     \_ /  |  \//    \   |
                   \  /  __  \   /  /   __/   /
                    \  /   \_\_  /  |  /_____/  |
                     \____\___/  |  /          /
                      \_       \/  /          |
                      | \  |/  \/  |          |
                      |  \//\__/    \         /
                     _|  /  \/   |  \       /\
                    /   /   /  |   \  \_   /
                   /_____/   |____|\   \ |
                   |   \______|----|_\   \  \
                   |_________   \_____|   \   \
                              \__\  \__\    \   \
                                 |   |       \   \
                                 |   |        \___\

Select the information you have:
1. Input
2. Password and Binary Access Code
3. Exit
Enter your choice: 2
Enter password: 888
Enter binary access code: 10110001100001011101100001
Welcome, Agent. Enter the passcode to access the secure file: Secure code verification required. Enter binary access code: Access granted. Decrypting secure file...: 888
  .-----------------.: 10110001100001011101100001

 /                 /\: 10110001100001011101100001

/                 /  \: 10110001100001011101100001

|      _________|    |: 10110001100001011101100001

|     |         |    |: 10110001100001011101100001

|     |         |    |: 10110001100001011101100001

FLAG{REE_LECTURES_WERE_FUN}: 10110001100001011101100001

|     |         |    |: 10110001100001011101100001

|     |         |    |: 10110001100001011101100001

|     |_________|    |: 10110001100001011101100001

|___________________|: 10110001100001011101100001

File decrypted successfully. Extracted information: CONFIDENTIAL.: 10110001100001011101100001
```

