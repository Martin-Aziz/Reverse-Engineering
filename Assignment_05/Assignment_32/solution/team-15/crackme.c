#include <stdio.h> 
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Verschlüsselte Flag
#define FLAG "\x19\x13\x32\x33\x1a\x0a\x05\x2b\x50\x0f\x19\x00\x56\x17\x5a\x1e\x39\x33\x43\x03\x1c"

// Globale Variable für die Magic Number
int magic_number;

// Fake win-Funktion, um Verwirrung zu stiften
void win() {
    printf("It's not THAT easy dummy!\n");
}

// Funktion zur XOR-Entschlüsselung der Flag
void xor_crypt(char* buffer, char* flag, size_t flag_len, char* key, size_t key_len) {
    for (int i = 0; i < flag_len; i++) {
        buffer[i] = flag[i] ^ key[i % key_len];
    }
}

// "Geheime" Funktion, welche die Flag ausgibt
void __magic() {
    char *buf = (char*)malloc(22);
    xor_crypt(buf, FLAG, 21, "__stack_chk_fail", 16);
    buf[21] = '\x00';
    puts(buf);
    free(buf);
}

// Eigene read-Funktion zum Verschleiern
ssize_t read(int fd, char *buf, size_t count) {
    char *buf2 = NULL;

    // Zeile von der Standardeingabe einlesen
    ssize_t size = getline(&buf2, &count, stdin);

    // Zeile in den usrprünglichen Puffer kopieren, damit sie in main verfügbar ist
    strcpy(buf, buf2);

    // Zeile in long konvertieren
    char *ptr;
    long number = strtol(buf, &ptr, 10);

    // User auf Overflow hinweisen
    if (number == (long)magic_number) {
        puts("Think bigger ＼（〇_ｏ）／");
        return size;
    }

    // Überprüfen, ob nach Overflow die Zahl der magic number entspricht
    if ((unsigned int)number == magic_number) {
        // 4294967295 + magic_number + 1
        __magic();
    }

    return size;
}

int main() {

    // Magic Number zwischen 10000 und 60000 generieren
    srand(time(NULL));
    magic_number = (rand() % 50000) + 10000;

    printf("Your magic number is %d\n", magic_number);
    puts("Please enter the passphrase: ");

    char buf[255];
    ssize_t len = read(1, buf, 255);

    // Vergleichen der eingelesene Zeile mit der Passphrase
    int cmp = strcmp(buf, "15islucky\n");
    if (cmp == 0) {
        // Wenn die Zeile der Passphrase entspricht, wird die (fake) win-Funktion aufgerufen
        win();
    }

    return 0;
}