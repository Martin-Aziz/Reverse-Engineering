#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Hauptfunktion mit dem Fakeflag. Password-Check wird hier durchgeführt, der theoretisch nie erreichbar sein sollte. 0x13371337 == 0xbadface. Das "Fake-Ziel" ist es den Wert von password zu überschreiben. Die einzige Methode Methode ist es, einen Buffer Overflow zu erzeugen und den Stack zu überschreiben. Schafft man das, gelangt man zu der win() Funktion.
void passwordCheck(){
    int password = 0x13371337;
    char buffer1[76];
    printf("Log dich ein mit deinem Password: \n");
    //erste Schwachstelle für das Fakeflag! vulnerability 1
    gets(buffer1);
    if(password == 0xbadface){
        win();
    }
    else{ 
    	//Der User muss also zuerst die erste Schwachstelle ignorieren und zu der Nächsten gehen. Hier wird der Buffer wieder overflowt, um danach zu der Funktion "_dl_relocate_static()" zu gelangen. Hier erhalten wir die echte Flag.
        printf("Kannst du dein Passwort nicht schreiben? Es ist: %04x\n", password);
        char buffer2[67];
        printf("Wie viele Versuche hast du gebraucht?\n");
        //zweite Schwachstelle für die richtige Lösung! vulnerability 2
    	gets(buffer2);
    	printf("Stundenzahl verschwendet: %s\n", buffer2 );
    }
}

int main(){

    passwordCheck();
    return 0;
}

// Die win() Funktion ist nur eine Ablenkung von der richtigen Funktion, die auch das richtige Flag ausgibt. Die Funktion liest einfach das char Array und schreibt abwechselnd von vorne und hinten den String aus.
void win(){
char andererbuffer[64];
    char buffer[] = "\x46\x34\x5b\x69\x65\x49\x65\x41\x74\x21\x5d\x45\x53\x77\x4d\x54\x43\x4e\x47\x4c"; //F4[ieIeAt!]ESwMTCNGL and FL4G[NiCeTIMewAStE!]
    int size = sizeof(buffer) / sizeof(buffer[0]) - 1; 
    for (int i = 0; i < size / 2; i++) {
        printf("%c%c", buffer[i], buffer[size - i - 1]);
    }

    
 }
// Verstecke Funktion. Name ist umgeändert, damit man es nicht sofort erkennt. Ist sonst genauso wie die win() Funktion, nur mit dem richtigen Flag.
void _dl_relocate_static(){
char andererbuffer[64];
    char buffer[] = "\x46\x41\x7b\x65\x35\x78\x31\x67\x6f\x6f\x7d\x30\x47\x6e\x6b\x46\x54\x4c\x47\x4c"; //FLAG{LeT5Fxk1ngGo0o} and FA{e5x1goo}0GnkFTLGL
    int size = sizeof(buffer) / sizeof(buffer[0]) - 1; 
    for (int i = 0; i < size / 2; i++) {
        printf("%c%c", buffer[i], buffer[size - i - 1]);
    }
}
