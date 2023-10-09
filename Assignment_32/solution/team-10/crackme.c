#include <stdlib.h>
#include <stdio.h>
#include <string.h>

// FLAG{Greetings_from_Team_10}
char FLAG[] = { 0x25, 0x3e, 0x75, 0x3d, 0x02, 0x18, 0x0a, 0x55, 0x17, 0x2b, 0x02, 0x0b,
                0x1e, 0x10, 0x2d, 0x52, 0x08, 0x16, 0x32, 0x27, 0x64, 0x17, 0x3e, 0x06,
                0x3a, 0x48, 0x53, 0x0f };
// XOR-Key: cr4zy_x0r_key
char KEY[] = { 0x63, 0x72, 0x34, 0x7A, 0x79, 0x5F, 0x78, 0x30, 0x72, 0x5F, 0x6B, 0x65, 0x79};

// Hashed password: Cr4zy_s3cr3t_p4ssword!!!
unsigned long password = 6488353955584119754;

// returns a hash of the input string
unsigned long hash(unsigned char *str) {
    unsigned long hash = 5381;
    int c;

    while (c = *str++) {
      hash = ((hash << 5) + hash) + c;
    }

    return hash;
}


// Uses XOR-decryption to decrypt the FLAG and print it
void print_flag() {
    char output[sizeof(FLAG) + 1];

    size_t len = strlen(FLAG);
    for(size_t i = 0; i < len; i++) {
        output[i] = FLAG[i] ^ KEY[i % (sizeof(KEY)/sizeof(char))];
    }
    output[len] = '\0';

    printf("%s\n", output);
}

int check_password() {
    int magic_number = 0;
    char input[32];

    printf("%s", "Bitte geben Sie das Passwort ein: ");
    /* gets is unsafe and allows buffer overflows.
       If more than 32 characters are used as an input then the input char array will overflow
       and it is possible to change the value of 'magic_number' with the overflow */
    gets(input);

    /* Instead of decrypting the password and comparing the strings in plain text
       the hashes are compared so that the password cannot be found in plain text during runtime */
    if (hash(input) == password) {
        magic_number = 1095586632;
    };

    /* Here the magic_number should always be 0 if the hashed input does not match the hashed password.
       But if we use a buffer overflow with gets() we can change the value of magic_number.
       That number will then be returned even if the input was not the correct password. */
    return magic_number;
}

int main() {
    /* only if check_password returns the correct magic number the flag will be decrypted and printed.
       1095586632 is 0x414D5348 in Hex. These hex-bytes correspond to the ASCII characters 'AMSH'.
       Due to little-endian you have to use 'HSMA' in the input string when causing the overflow to get this number */
    if (check_password() == 1095586632) {
        print_flag();
    } else {
        printf("%s\n", "Falsches Passwort :(");
    }

    return 0;
}
