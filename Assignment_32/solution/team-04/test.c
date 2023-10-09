#include <stdio.h>
#include <string.h>

void encryptDecrypt(char *input, char *output, char *key) {
	//char key[] = {'K', 'C', 'Q'}; //Can be any chars, and any size array
	
	int i;
	for(i = 0; i < strlen(input); i++) {
		output[i] = input[i] ^ key[i % (sizeof(key)/sizeof(char))];
	}
}

int main (int argc, char *argv[]) {
    char key[12] = "hnuldwhaupi";
	char baseStr[] = "FLAG{LuLGotEm}";
	
    printf("Key:");
    int k;
    for (k = 0; k< 12; k++ ) {
        printf("0x%x, ", key[k]);
    }
    printf("\n");

	char encrypted[strlen(baseStr)];
	encryptDecrypt(baseStr, encrypted, key);
	printf("Encrypted:");
    int i;
    for (i = 0; i< sizeof(encrypted); i++ ) {
        printf("0x%x, ", encrypted[i]);
    }
    printf("\n");
	
	char decrypted[strlen(baseStr)];
	encryptDecrypt(encrypted, decrypted, key);
	printf("Decrypted:%s\n", decrypted);
}