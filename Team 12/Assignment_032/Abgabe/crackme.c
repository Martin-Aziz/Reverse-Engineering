
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>
#include <signal.h>
#define KEY "\x77\x94\x31\x2E"
#define ENCRYPTED "\x31\xD8\x70\x69\x0C\xC6\x74\x6B\x28\xD8\x74\x6D\x23\xC1\x63\x6B\x24\xCB\x66\x6B\x25\xD1\x6E\x68\x22\xDA\x4C"
static void alarmHandler(int signal) {
    exit(1);
}
void setup(void) {
    setvbuf(stdout, (char*)0, _IONBF, 0);
    setvbuf(stdin,  (char*)0, _IONBF, 0);
    signal(0xe, alarmHandler);
    alarm(0x3c);
}

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

void unlockFile() {
    int j = 0;
    while (j < 27) {
        printf("%c", ENCRYPTED[j] ^ KEY[j % 4]);
        j = j + 1;
    }
    printf("%s", "\n");
}

int main() {
    setup();
    printf("Welcome, Agent. Enter the passcode to access the secure file: ");

    int input;
    scanf("%d", &input);

    int *ptr = malloc(input * sizeof(int));
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

    if (input ==888)  {
        printf("Secure code verification required. Enter binary access code: ");
        char binaryInput[1000];
        scanf("%s", binaryInput);
        if (binary_to_int(binaryInput) == 46536545) {
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
    
    printf("Accessing personal identification required: ");
    int personalID =1393983983;
    scanf("%d", &personalID);
    if(personalID==1393983983)
    {
        printf("Verifying... Access granted. Welcome, Agent. Proceed with caution.\n");
    }
else
{
    printf("Spy Alert !!!!!!!!!!!!!!!!!!!\n"); 
}

    return 1;
}
