
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
// Definition eines Schlüssels und einer verschlüsselten Zeichenkette
#define KEY "\x77\x94\x31\x2E"
#define ENCRYPTED "\x31\xD8\x70\x69\x0C\xC6\x74\x6B\x28\xD8\x74\x6D\x23\xC1\x63\x6B\x24\xCB\x66\x6B\x25\xD1\x6E\x68\x22\xDA\x4C"
// Statische Funktion zur Behandlung des Alarmsignals
static void alarmHandler(int signal) {
    exit(1);
}
//Einrichtung von Sicherheitsmaßnahmenum ,den Prozess nach 60 Sekunden zu beenden und die Eingabepufferung auszuschalten
void setup(void) {
    setvbuf(stdout, (char*)0, _IONBF, 0);// Deaktiviert die Pufferung für die Standardausgabe
    setvbuf(stdin,  (char*)0, _IONBF, 0);
    signal(0xe, alarmHandler);// Weist dem Signal 0xe (SIGALRM) die Behandlungsfunktion alarmHandler zu
    alarm(0x3c);// Stellt einen Alarm nach 60 Sekunden ein
}
// Funktion zur Umwandlung einer binären Zeichenkette in eine ganze Zahl
int binary_to_int(char *binary) {
    int len = strlen(binary);
    int result = 0;
    for (int i = 0; i < len; i++) {
        if (binary[i] == '1') {
            result += pow(2, len - i - 1);
        }
    }
    return result;
}
// Funktion zum Entschlüsseln der verschlüsselten Zeichenkette
void unlockFile() {
    int j = 0;
    while (j < 27) {
        printf("%c", ENCRYPTED[j] ^ KEY[j % 4]);// Entschlüsselt und gibt jedes Zeichen der verschlüsselten Zeichenkette aus
        j = j + 1;
    }
    printf("%s", "\n");// Gibt eine neue Zeile aus, um die Entschlüsselung zu vervollständigen
}

int main() {
    setup();// Einstellung der Sicherheitsmechanismen
    printf("Welcome, Agent. Enter the passcode to access the secure file: "); // Benutzer wird zur Passcode-Eingabe aufgefordert

    int input;
    scanf("%d", &input);

    int *ptr = malloc(input * sizeof(int));
    // Fehlermeldung und Protokoll bei fehlgeschlagener Speicherzuweisung
    if (ptr == NULL) {
        printf("Access denied. Security breach detected. Initiating lockdown protocol.\n");
        printf("       /\\     /\\\n");
        printf("      /  \\___/  \\\n");
        printf("     /    | |    \\\n");
        printf("    /     | |     \\\n");
        printf("   /______________\\\n");
        printf("  / |          |   \\\n");
        printf(" /  |   FALSE  |    \\\n");
        printf("|   |   FALG{  |    |\n");
        printf("|   |   Malloc |    |\n");
        printf("|   |   never  |    |\n");
        printf("|   |   fail,  |    |\n");
        printf("|   |   16D61, |    |\n");
        printf("|   |     378, |    |\n");
        printf("|   |   2C6176 |    |\n");
        printf("|   |   1,025D |    |\n");
        printf("|   |   BF5B,   |    |\n");
        printf("|___|__________|____|\n");
        exit(0);
    }

    if (input == 98080897556)  {// Überprüfung des eingegebenen Passcodes
        printf("Secure code verification required. Enter binary access code: ");
        char binaryInput[100];
        scanf("%s", binaryInput);
        if (binary_to_int(binaryInput) == 46536545) {// Zugriff gewährt für Agenten
            printf("Access granted. Decrypting secure file...\n");
            printf("  .-----------------.\n");
            printf(" /                 /\\\n");
            printf("/                 /  \\\n");
            printf("|      _________|    |\n");
            printf("|     |         |    |\n");
            printf("|     |         |    |\n");
            unlockFile();
            printf("|     |         |    |\n");
            printf("|     |         |    |\n");
            printf("|     |_________|    |\n");
            printf("|___________________|\n");
            printf("File decrypted successfully. Extracted information: CONFIDENTIAL.\n");
            exit(0);
        } else {
            printf("Access denied. Intruder alert! Initiating security protocols...\n");
            exit(0);
        }
    }
    // Persönliche Identifikationsnummer wird abgefragt
    printf("Accessing personal identification required: ");
    int personalID =1393983983;
    scanf("%d", &personalID);
    if(personalID==1393983983)
    {
        printf("Verifying... Access granted. Welcome, Agent. Proceed with caution.\n");
    }
else
{
    printf("Spy Alert !!!!!!!!!!!!!!!!!!!\n"); // Warnung bei falscher ID-Eingabe
}

    return 1;
}
