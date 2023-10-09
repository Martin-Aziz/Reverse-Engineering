#include <stdio.h>
#include <string.h>

void xor(char*, char*, char*);

int checkPassword(char *c) {

    char output[30];
    char key[] = "AAAAABBBBBCCCCCDDDDDEEEEEFFFFF";
    xor(c, output, key);
}

void xor(char *input, char *output, char *key)
{
    for (int i = 0; i < strlen(input); ++i)
        output[i] = input [i] ^ key [i % strlen(key)];
}

void win() {
    printf("FLAG{mom_i_got.it} \n");
}

int main() {
    // ensures the function is on top of the stack
    volatile int (*cmp)();
    // sets the buffer to char size 30
    char input[30];
    // dummy var
    char password[16];

    cmp = 0;

    printf("Enter Password: \n");
    // vulnerability to cause buffer overflow
    gets(input);
    // dummy function
    checkPassword(password);
    // checks if the pointer changed from 0 
    if(cmp) {
        cmp();
 }
}