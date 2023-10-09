 #include <stdio.h>
 #include <math.h>
 #include <stdint.h>

uint64_t a = 0;
unsigned char num_sequence[6];
int aHintIsNear = 111;


//Die Funktion liest zum einen 12 bit aus der license.key Datei ein,
//welche die letzten 3 Byte der Adresse der win() Funktion sind.
//Zusätzlich wird eine Zahlenfolge eingelesen, welche hinter der Adresse steht.
uint64_t readFile(){
    int c;
    uint64_t addr = 0;
    unsigned int counter = 0;


    FILE *fp = fopen("./license.key", "r");
    //Datei Byte für Byte einlesen und in die Adressen- und Zahlenfolgenvariable schreiben.
    while ( ( (c = fgetc(fp)) != EOF )) {
        //adresse
        if(counter < 2){
         addr <<= 8;
         addr +=  (unsigned) c;
         }

        //zahlenfolgensigned hexadecimal integer (capital letters)
        if(counter >= 3){
            num_sequence[counter-3] = (unsigned) c;
        }
        counter++;
    }

    fclose(fp);
    a = addr;
    return addr+62;
}

//Funktion deren Adresseende (letze 3 Byte) standardmäßig in der license.key Datei hinterlegt ist.
void lose(){
    printf("So wird das nix!\n");
    printf("Denk ausserhalb der Kiste!\n");
}


//Flag mit Key Byte für Byte XOREN
void decrypt_xor(unsigned char x, unsigned char  f[24]){
    unsigned char de[24];
    for(int i = 0; i < sizeof(de)/sizeof(de[0]);i++){
        de[i] = f[i] ^ x;
    }
    //Ist die fünfte Stelle {, wird die Flag ausgegeben - wurde richtig entschlüsselt
    if(de[4] == 0x7b){
        printf("\n%s",de);
    }
}

//Key errechnen und Variable mit verschlüsselter Flag initialisieren.
void gg(unsigned int x){
    //Übergebene Zahl verändern.
        x = x ^ 37;
        x = x ^ 12;
        x = x ^ 198;
        x = x ^ 52;
        x = x ^ 47;
        x = x ^ 16;
        x = x ^ 250;
        x = x ^ 119;
        x = x ^ 198;
    unsigned char s = (unsigned char) x;

    //Verschlüsselte Flag
    unsigned char f[24] = {0xC6,0xCC,0xC1,0xC7,0xFB,0xEC,0xE9,0xE3,0xE5,0xEE,0xF3,0xE5,0xDF,0xF4,0xEF,0xDF,0xF2,0xE5,0xF6,0xE5,0xF2,0xF3,0xE5,0xFD};

    decrypt_xor(s,f);

}

//Funktion, deren Adresse in die license.key Datei eingetragen werden muss, um die Flag auszugeben.
void win(){
    printf("Kiste verlassen aber du schaust noch in den Teller!\n");
    if(a == 0){
        return;
    }
    //In readFile() eingelesene Zahlenreihenfolge verrechnen und bei richtigem Ergebnis gg() aufrufen.
    int sum = 0;
    sum += num_sequence[0];
    sum -= num_sequence[1];
    sum += num_sequence[2];
    sum -= num_sequence[3];
    sum += num_sequence[4];
    sum -= num_sequence[5];
    if(sum == 0x2A){
        if(aHintIsNear == 0){
        printf("[*] gg oder decrypt_xor analysieren fuehrt nicht zur loesung");
        }
        //Mehrere Aufrufe, von denen nur einer funktioniert um das entschlüsselt bzw auslesen der Flag zu erschweren.
        gg(sum+7);
        gg(sum-20);
        gg(sum+14);
        gg(sum+5);
        gg(sum-30);
    }
}


void giveMeYourAdressSpace(){
    //Hinweis welcher niemals geprintet wird, aber in gdb eingesehen werden kann
    if(aHintIsNear == 1){
        printf("%s","Schönheit kommt von den vorderen Werten!");
    }
};


int main(int argc, char *argv[])
{
    //license.key Datei einlesen und Inhalt in entsprechende Variablen schreiben
    uint64_t x = readFile();

    uint64_t zz = (uint64_t) &giveMeYourAdressSpace;
    //Individuellen Adressteil der giveMeYourAdressSpace Funktion aus der Adresse löschen,
    //um allgemeinen Funktions Adressspace zu bekommen.
    zz = zz &  0xfffffffffffff000;
    //Individuellen Adressteil, welcher aus der license.key ausgelesen wurde, an den Adressspace anhängen.
    zz += ((a>>4) & 0x0000000000000fff);
    //Funktionspointer aus der zusammengefügten Adresse erzeugen.
    void (*addrCall)();
    addrCall = zz;
    
    addrCall();
}
