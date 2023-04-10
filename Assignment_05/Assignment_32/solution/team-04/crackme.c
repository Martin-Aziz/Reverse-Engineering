#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// variables containing a key and the encrypted flag
static char local_3[] = {0x68, 0x6e, 0x75, 0x6c, 0x64, 0x77, 0x68, 0x61, 0x75, 0x70, 0x69, 0x0};
static char local_28[] = {0x2e, 0x22, 0x34, 0x2b, 0x1f, 0x3b, 0x1d, 0x2d, 0x2f, 0x1, 0x1, 0x29, 0x9, 0xa};

// function for decrypting the flag. uses simple xor enryption
void encryptDecrypt(char *input, char *output, char *key) {
	int i;
	for(i = 0; i < strlen(input); i++) {
		output[i] = input[i] ^ key[i % (sizeof(key)/sizeof(char))];
	}
}

// functiion for printing out the flag
void printflag() {
    // create buffer for decrypted flag
    char flag[256];
    // decrypt flag
    encryptDecrypt(local_28, flag, local_3);
    // print flag buffer content
    printf("%s\n", flag);
}

int main()
{
    // declare variable and create a pointer to it's address on the stack
    long a = 0x1;
    long *p = &a;
    
    // create input buffer and retrieve user input
    char input[254];
    printf("Please enter your name: ");
    fgets(input, sizeof(input), stdin);

    // print the user input using printf without providing further parameters
    printf("Hello ");
    printf(input);
    // check if the variable's value has been changed
    // if so, the flag is printed
    if (a != 0x1){
        // Example Input: %39$n
        printflag();
        exit(0);
    }
    // otherwise the program exits with code 1
    exit(1);
}
