Assignment 4)
handelt sich vermutlich um einen Keylogger
Indizien:

Vorgehensweite: 

````sh
rabin2 -i payload_1

[Imports]
nth vaddr      bind   type   lib name
―――――――――――――――――――――――――――――――――――――
1   0x00000000 WEAK   NOTYPE     _ITM_deregisterTMCloneTable
2   0x00000890 GLOBAL FUNC       setsockopt
3   0x000008a0 GLOBAL FUNC       write
4   0x000008b0 GLOBAL FUNC       __stack_chk_fail
5   0x000008c0 GLOBAL FUNC       system
6   0x000008d0 GLOBAL FUNC       htons
7   0x000008e0 GLOBAL FUNC       dup
8   0x000008f0 GLOBAL FUNC       memset
9   0x00000900 GLOBAL FUNC       close
10  0x00000910 GLOBAL FUNC       read
11  0x00000000 GLOBAL FUNC       __libc_start_main
12  0x00000000 WEAK   NOTYPE     __gmon_start__
13  0x00000920 GLOBAL FUNC       listen
14  0x00000930 GLOBAL FUNC       bind
15  0x00000940 GLOBAL FUNC       perror
16  0x00000950 GLOBAL FUNC       accept
17  0x00000960 GLOBAL FUNC       exit
18  0x00000000 WEAK   NOTYPE     _ITM_registerTMCloneTable
19  0x00000990 WEAK   FUNC       __cxa_finalize
20  0x00000970 GLOBAL FUNC       fork
21` 0x00000980 GLOBAL FUNC       socket

man setsockopt
        getsockopt, setsockopt - get and set options on sockets

man write 
        send a message to another user

man system
        execute shell command

man htons
        convert values between host and network byte order

man read
        read from a file descriptor

man listen
        listen for connections on a socket

man accept
        accept a connection on a socket

man bind
        bind a name to a socket

man fork
    create a child process

DESCRIPTION
       fork() creates a new process by duplicating the calling process.  The new process is
       referred to as the child process.  The calling process is referred to as the  parent
       process.

man exit

```

Vermutung: 

Vermutlich handelt es sich um einen Keylogger der einen ShadowUser anlegt und über einen Socket für eine mögloche Verbindung öffnet.

Es werden Prozesse geforket. Vermutlich um die Netzverbindung oder die Usergenerierung zu verstecken.

Die eingegebenen Befehle werden ausgeführt sodass es für den eigentlichen Nutzer nicht erkennbar ist.
----

Assignment 5)

Vermutlich eine Ransomware die die Daten verschlüsselt

rabin2 -s payload_2.so 

nth paddr      vaddr      bind   type   size lib name
―――――――――――――――――――――――――――――――――――――――――――――――――――――
23  0x00000e49 0x00000e49 GLOBAL FUNC   247      encrypt_files
24  0x00002590 0x00002590 GLOBAL FUNC   0        _fini
25  0x00002463 0x00002463 GLOBAL FUNC   300      AES_CTR_xcrypt_buffer
26  0x00000b70 0x00000b70 GLOBAL FUNC   0        _init
27  0x00000e12 0x00000e12 GLOBAL FUNC   55       generate_system_id
28  0x000022b1 0x000022b1 GLOBAL FUNC   38       AES_ECB_decrypt
29  0x000013d4 0x000013d4 GLOBAL FUNC   38       AES_init_ctx
30  ---------- 0x002030b8 GLOBAL NOTYPE 0        __bss_start
31  0x000013fa 0x000013fa GLOBAL FUNC   71       AES_init_ctx_iv
32  ---------- 0x002030c0 GLOBAL NOTYPE 0        _end
33  ---------- 0x002030b8 GLOBAL NOTYPE 0        _edata
34  0x00001441 0x00001441 GLOBAL FUNC   44       AES_ctx_set_iv
35  0x00000fdc 0x00000fdc GLOBAL FUNC   307      send_home
36  0x0000228b 0x0000228b GLOBAL FUNC   38       AES_ECB_encrypt
37  0x00000dba 0x00000dba GLOBAL FUNC   88       generate_key
38  0x000023b1 0x000023b1 GLOBAL FUNC   178      AES_CBC_decrypt_buffer
39  0x00002323 0x00002323 GLOBAL FUNC   142      AES_CBC_encrypt_buffer
40  0x00000f40 0x00000f40 GLOBAL FUNC   156      hostname_to_ip
1   0x000001c8 0x000001c8 LOCAL  SECT   0        .note.gnu.build-id
2   0x000001f0 0x000001f0 LOCAL  SECT   0        .gnu.hash
3   0x000002a0 0x000002a0 LOCAL  SECT   0        .dynsym
4   0x00000678 0x00000678 LOCAL  SECT   0        .dynstr
5   0x00000878 0x00000878 LOCAL  SECT   0        .gnu.version
6   0x000008d0 0x000008d0 LOCAL  SECT   0        .gnu.version_r
7   0x00000900 0x00000900 LOCAL  SECT   0        .rela.dyn
8   0x000009a8 0x000009a8 LOCAL  SECT   0        .rela.plt
9   0x00000b70 0x00000b70 LOCAL  SECT   0        .init
10  0x00000b90 0x00000b90 LOCAL  SECT   0        .plt
11  0x00000cd0 0x00000cd0 LOCAL  SECT   0        .plt.got
12  0x00000ce0 0x00000ce0 LOCAL  SECT   0        .text
13  0x00002590 0x00002590 LOCAL  SECT   0        .fini
14  0x000025a0 0x000025a0 LOCAL  SECT   0        .rodata
15  0x000027cc 0x000027cc LOCAL  SECT   0        .eh_frame_hdr
16  0x000028b0 0x000028b0 LOCAL  SECT   0        .eh_frame
17  0x00002e10 0x00202e10 LOCAL  SECT   0        .init_array
18  0x00002e18 0x00202e18 LOCAL  SECT   0        .fini_array
19  0x00002e20 0x00202e20 LOCAL  SECT   0        .dynamic
20  0x00002fe0 0x00202fe0 LOCAL  SECT   0        .got
21  0x00003000 0x00203000 LOCAL  SECT   0        .got.plt
22  0x000030b0 0x002030b0 LOCAL  SECT   0        .data
23  ---------- 0x002030b8 LOCAL  SECT   0        .bss
24  0x00000000 0x00000000 LOCAL  SECT   0        .comment
25  0x00000000 0x00000000 LOCAL  FILE   0        crtstuff.c
26  0x00000ce0 0x00000ce0 LOCAL  FUNC   0        deregister_tm_clones
27  0x00000d20 0x00000d20 LOCAL  FUNC   0        register_tm_clones
28  0x00000d70 0x00000d70 LOCAL  FUNC   0        __do_global_dtors_aux
29  ---------- 0x002030b8 LOCAL  OBJ    1        completed.7698
30  0x00002e18 0x00202e18 LOCAL  OBJ    0        __do_global_dtors_aux_fini_array_entry
31  0x00000db0 0x00000db0 LOCAL  FUNC   0        frame_dummy
32  0x00002e10 0x00202e10 LOCAL  OBJ    0        __frame_dummy_init_array_entry
33  0x00000000 0x00000000 LOCAL  FILE   0        payload_2.c
34  0x00000000 0x00000000 LOCAL  FILE   0        aes.c
35  0x000025c0 0x000025c0 LOCAL  OBJ    256      sbox
36  0x000026c0 0x000026c0 LOCAL  OBJ    256      rsbox
37  0x000027c0 0x000027c0 LOCAL  OBJ    11       Rcon
38  0x0000110f 0x0000110f LOCAL  FUNC   709      KeyExpansion
39  0x0000146d 0x0000146d LOCAL  FUNC   161      AddRoundKey
40  0x0000150e 0x0000150e LOCAL  FUNC   120      SubBytes
41  0x00001586 0x00001586 LOCAL  FUNC   219      ShiftRows
42  0x00001661 0x00001661 LOCAL  FUNC   45       xtime
43  0x0000168e 0x0000168e LOCAL  FUNC   474      MixColumns
44  0x00001868 0x00001868 LOCAL  FUNC   1997     InvMixColumns
45  0x00002035 0x00002035 LOCAL  FUNC   120      InvSubBytes
46  0x000020ad 0x000020ad LOCAL  FUNC   219      InvShiftRows
47  0x00002188 0x00002188 LOCAL  FUNC   140      Cipher
48  0x00002214 0x00002214 LOCAL  FUNC   119      InvCipher
49  0x000022d7 0x000022d7 LOCAL  FUNC   76       XorWithIv
50  0x00000000 0x00000000 LOCAL  FILE   0        crtstuff.c
51  0x00002c2c 0x00002c2c LOCAL  OBJ    0        __FRAME_END__
52  0x00000000 0x00000000 LOCAL  FILE   0        
53  0x000030b0 0x002030b0 LOCAL  OBJ    0        __dso_handle
54  0x00002e20 0x00202e20 LOCAL  OBJ    0        _DYNAMIC
55  0x000027cc 0x000027cc LOCAL  NOTYPE 0        __GNU_EH_FRAME_HDR
56  ---------- 0x002030b8 LOCAL  OBJ    0        __TMC_END__
57  0x00003000 0x00203000 LOCAL  OBJ    0        _GLOBAL_OFFSET_TABLE_
1   0x00000000 0x00000000 WEAK   NOTYPE 16       imp._ITM_deregisterTMCloneTable
2   0x00000ba0 0x00000ba0 GLOBAL FUNC   16       imp.strcpy
3   0x00000bb0 0x00000bb0 GLOBAL FUNC   16       imp.inet_ntoa
4   0x00000bc0 0x00000bc0 GLOBAL FUNC   16       imp.opendir
5   0x00000bd0 0x00000bd0 GLOBAL FUNC   16       imp.__stack_chk_fail
6   0x00000be0 0x00000be0 GLOBAL FUNC   16       imp.htons
7   0x00000bf0 0x00000bf0 GLOBAL FUNC   16       imp.send
8   0x00000c00 0x00000c00 GLOBAL FUNC   16       imp.memset
9   0x00000c10 0x00000c10 GLOBAL FUNC   16       imp.close
10  0x00000c20 0x00000c20 GLOBAL FUNC   16       imp.closedir
11  0x00000c30 0x00000c30 GLOBAL FUNC   16       imp.read
12  0x00000c40 0x00000c40 GLOBAL FUNC   16       imp.gethostbyname
13  0x00000000 0x00000000 WEAK   NOTYPE 16       imp.__gmon_start__
14  0x00000c50 0x00000c50 GLOBAL FUNC   16       imp.inet_pton
15  0x00000c60 0x00000c60 GLOBAL FUNC   16       imp.readdir
16  0x00000c80 0x00000c80 GLOBAL FUNC   16       imp.open
17  0x00000c90 0x00000c90 GLOBAL FUNC   16       imp.strcat
18  0x00000ca0 0x00000ca0 GLOBAL FUNC   16       imp.exit
19  0x00000cb0 0x00000cb0 GLOBAL FUNC   16       imp.connect
20  0x00000000 0x00000000 WEAK   NOTYPE 16       imp._ITM_registerTMCloneTable
21  0x00000cd0 0x00000cd0 WEAK   FUNC   16       imp.__cxa_finalize
22  0x00000cc0 0x00000cc0 GLOBAL FUNC   16       imp.socket



Indizien:   AES (andvanced encryption standart)
            generate key (Schlüsselgenerierung)
            Cipher
            
            send_home

Vermutung:
        Es handelt sich wahrscheinlich um Werschlüsselungssoftware, welche die Festplatte verschlüsselt und ein Lösegeld fordert.

                
