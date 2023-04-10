#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<ctype.h>

void xor_strings(char *s1, char *s2, char *result) {
    int len1 = strlen(s1);
    int len2 = strlen(s2);
    for (int i = 0; i < len1; i++)
        result[i] = s1[i] ^ s2[i % len2];  // use len1 -> repeat s2 from beginning
    
    result[len1] = '\0';
}

void read_passwd(char *buffer) {
    write(1, "Enter password: ", 17);
    read(0, buffer, 128);
}

void decrypt_caesar(char* ciphertext) {
    int key = 20;
    int len = strlen(ciphertext);

    for (int i = 0; i < len; i++)
        if (isalpha(ciphertext[i]))
            ciphertext[i] = (ciphertext[i] - 'a' - key + 26) % 26 + 'a';  // shift down the alphabet
}


int main() {
    char encrypted_flag[] = { 71, 92, 80, 70, 104, 92, 96, 114, 117, 103, 126, 98, 123, 98, 41, 97, 104, 114, 101, 114, 51, 90, 104, 116, 117, 127, 119, 103, 118, 125, 103, 123, 0x0 };
    char key[] = { 0x1, 0x10, 0x11, 0x1, 0x13, 0x11, 0x9, 0x6, 0x0 };
    char input[128];

    read_passwd(input);  // read encrypted string for printf at the end
    decrypt_caesar(input);  // decrypt to prevent solving crackme without looking at the code

    char* decrypted_flag[128];
    char *l = &decrypted_flag;  // To be able to print the flag with %s
    xor_strings(encrypted_flag, key, decrypted_flag);  // decrypt flag in memory to have access in printf
    printf(input);

    return 0;
}