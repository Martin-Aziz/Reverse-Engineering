#include <stdio.h>
#include <stdlib.h>
#include <sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <string.h>
// array for the encrypted program which is created and inserted in the build process from payload.c
const char encrypted_program[] = {105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117,102,102,108,101,105,110,100,101,120,95,115,104,117};

void xor_decrypt(char *buffer, size_t size, const char *key)
{
	size_t key_length = strlen(key);
	for (size_t i = 0; i < size; i++)
		buffer[i] ^= key[i % key_length];
}

// takes a password shuffled with a pseudorandom algorithm and reverses the shuffle.
void reconstruct_password(char* password)
{
	int length = strlen(password);
	for (int i = 0; i < length; i++)
	{
		int j = ((i ^ (i << 1)) * 29) % length; // calculate pseudorandom index to swap the character at the current index with
		char temp = password[i];
		password[i] = password[j];
		password[j] = temp;
	}
}

void win(char* password)
{
	// allocate read, write and executable memory for the encrypted program to be copied to, decrypted and executed.
	void *execution_buffer = mmap(NULL, sizeof(encrypted_program), PROT_READ | PROT_WRITE | PROT_EXEC, MAP_PRIVATE | MAP_ANONYMOUS, 0, 0);
	memcpy(execution_buffer, encrypted_program, sizeof(encrypted_program));
	xor_decrypt(execution_buffer, sizeof(encrypted_program), password);
	void (*func)(int (*rand)(), int (*print)(char *, ...), int (*scanf)(char *, ...), int (*memset)(void *, int, int), void*(*malloc)(int size)) = execution_buffer;
	func(rand, printf, scanf, memset, malloc); // passing the function pointers because the encrypted program is not linked and cannot access any library functions.
}

int main(int argc, char const *argv[])
{
	srand(time(NULL));
	printf("password: ");
	char input[21] = {0};
	scanf("%20s", input);
	reconstruct_password(input);
	win(input);
	return 0;
}
