/**
 * Check a license protected by a CRC32
 *
 * Program checks for the CRC32 of a file and its contents.
 * To print the flag, a specific contents and the CRC32 of the file
 * must fit.
 *
 * To solve the exercise, the file must be patched and the CRC32 must
 * be restored by adding some bytes to the file.
 *
 * The flag is encrypted.
 *
 * (c) 2022 Thomas Smits
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <inttypes.h>
#include <fcntl.h>
#include <unistd.h>

#include "util/xor_crypt.h"
#include "util/crc32.h"

#define CHECKSUM    0xd55c8f7fu
#define LICENSE_KEY 0xababbabeu

#define LICENSE_FILE     "license_file.key"
#define FILE_BUFFER_SIZE     255

/* FLAG{crc32_is_still_not_secure} */
char FLAG[] = { 0x2a, 0x25, 0x22, 0x22, 0x15, 0x10, 0x17, 0x3c, 0x55, 0x5b, 0x33, 0x0c,
                0x5d, 0x34, 0x16, 0x0d, 0x05, 0x05, 0x0f, 0x3a, 0x00, 0x1c, 0x11, 0x00,
                0x15, 0x0c, 0x0f, 0x10, 0x5c, 0x0e, 0x18 };

/**
 * Print the flag.
 */
void win() {
    char* flag = (char*) malloc(sizeof(FLAG) + 1);
    xor_crypt(flag, FLAG, sizeof(FLAG), LICENSE_FILE, strlen(LICENSE_FILE));
    flag[sizeof(FLAG)] = '\0';
    printf("%s\n", flag);
    free(flag);
}

int main(int argc, char** argv) {

    uint8_t file_buffer[FILE_BUFFER_SIZE];
    int fh;
    ssize_t size;

    if ((fh = open(LICENSE_FILE, O_RDONLY)) < 0) {
        fprintf(stderr, "File %s not found\n", LICENSE_FILE);
        exit(1);
    }

    if ((size = read(fh, file_buffer, FILE_BUFFER_SIZE)) < 0) {
        fprintf(stderr, "Cannot read file %s\n", LICENSE_FILE);
        exit(1);
    }

    close(fh);

    // first byte is number of licenses
    int num_licenses = (int) file_buffer[0];

    // next long is the key
    int key = (int) *((int*) (file_buffer + 1));

    // Get checksum of file contents
    uint32_t crc32_value = crc32(file_buffer, size);

    // Give a hint
    printf("You have %d license(s). Key: %x\n", num_licenses, key);

    if (key != LICENSE_KEY) {
        puts("License key not correct");
        exit(1);
    }

    if (num_licenses < 1) {
        puts("You need at least 1 license to win");
        exit(1);
    }

    if (crc32_value != CHECKSUM) {
        puts("Checksum of license file not correct. You cheated!");
        exit(1);
    }

    win();
}
