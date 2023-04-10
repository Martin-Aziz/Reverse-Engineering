#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int main() {
    char password[5];
    char correct_password[5];
    printf("Enter the password: ");
    scanf("%s", password);

    set_and_obfuscate_password(correct_password);

//Flag wird auch obfuscated gespeichert
    char flag[] = {70, 76, 65, 71, 123, 95, 105, 115, 95, 116, 104, 101, 95, 119, 48, 114, 100, 125};
    
//Password check
    if (strcmp(password, correct_password) == 0) {
        //wenn richtig, wird die Flagge geprinted
        printf("%s\n", flag);
    } else {
        printf("Incorrect password.\n");
    }

    return 0;
}

void set_and_obfuscate_password(char* correct_password) {

//Password wird hier erstmal eingetragen
    correct_password[0] = 'b';
    correct_password[1] = 'h';
    correct_password[2] = 'p';
    correct_password[3] = 'a';
    correct_password[4] = '\0';

//Danach wird das Password durch eine Schleife verschoben (erster char um 0, zweiter char um 1, dritter char um 2,...) bis am Endeffekt correct_password="bird" 
    for (int i = 0; i < strlen(correct_password); i++) {
        correct_password[i] = correct_password[i] + i;
    }
}