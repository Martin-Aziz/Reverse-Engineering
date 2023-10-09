#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/time.h>
#include <netdb.h>
#include <math.h>

#define CHUNK_SIZE 512

struct hostent *server;


int tcp_socket;

// Our encrypted flag
char flag[32] = {
    0x1e,
    0x34,
    0x19,
    0x76,
    0x2b,
    0x21,
    0x3b,
    0x07,
    0x50,
    0x38,
    0x2c,
    0x57,
    0x27,
    0x32,
    0x1f,
    0x55,
    0x27,
    0x6a,
    0x50,
    0x21,
    0x11,
    0x1b,
    0x55,
    0x1d,
    0x30,
    0x6f,
    0x01,
    0x1c,
    0x5e,
    0x3a,
    0x0b,
    0x25,
};


typedef struct
{
    char *buffer;
    int buffer_size;
} SocketBuffer;

SocketBuffer response;


    /// @brief Reads chunked data from Socket
    /// @param s File descriptor of Socket
    /// @param timeout Time that chunks should be received in seconds
    /// @return result SocketBuffer Buffer of Bytes read and length
SocketBuffer read_socket_chunked(int s, int timeout)
{
    int size_recv, total_received = 0;
    int buffer_size = CHUNK_SIZE;
    char chunk[CHUNK_SIZE];
    char *buffer = malloc(sizeof(char) * buffer_size);
    struct timeval begin, now;
    double timediff;

    fcntl(s, F_SETFL, O_NONBLOCK);

    gettimeofday(&begin, NULL);

    while (1)
    {
        gettimeofday(&now, NULL);

        timediff = (now.tv_sec - begin.tv_sec) + 1e-6 * (now.tv_usec - begin.tv_usec);

        if (buffer_size > 0 && timediff > timeout)
        {
            break;
        }
        else if (timediff > timeout * 2)
        {
            break;
        }
        memset(chunk, 0, (size_t)CHUNK_SIZE);
        size_recv = recv(s, chunk, CHUNK_SIZE, 0);
        if (size_recv < 0)
        {
            usleep(100000);
        }
        else
        {
            total_received += size_recv;
            size_recv = 0;
            if (total_received > buffer_size)
            {
                buffer_size += CHUNK_SIZE;
                buffer = (char *)realloc(buffer, buffer_size);
            }
            memcpy((buffer + buffer_size - CHUNK_SIZE), chunk, CHUNK_SIZE);
            gettimeofday(&begin, NULL);
        }
    }
    SocketBuffer result;
    result.buffer = buffer;
    result.buffer_size = buffer_size;
    return result;
}

// basic xor for flag decryption
void xor (char flag[], char *b, int len) {
    for (int i = 0; i < len; i++)
    {
        flag[i] ^= b[i];
    }
}

// Parses an int from a string using radix magic
int parse_str(char *s, int len, int radix)
{
    int sum = 0;
    for (int i = 0; i < len; i++)
    {
        int c = s[i] - 48;
        if (0 > c > 9)
        {
            printf("Error parsing string to int!\n");
            exit(1);
        }
        c *= pow(radix, (len - i - 1));
        sum += c;
    }
    return sum;
}

// Converts an array of byte-values into an string of hexadecimal representation
// Used for sending bytes over network
char *arr_to_string(int *byte_array, unsigned int n_bytes)
{
    char *buffer = malloc(sizeof(char) * n_bytes * 1000);
    char *bp = buffer;
    *bp = 0;
    for (int i = 0; i < n_bytes; i++)
    {
        if (i > 0)
        {
            *bp = ',';
            bp++;
        }
        bp += sprintf(bp, "%d", byte_array[i]);
    }
    return buffer;
}

// Connects s to server with name server_name and returns host data of server
struct hostent *connect_socket_to_server(int s, char *server_name)
{
    struct hostent *server;

    struct sockaddr_in serveraddr;

    if (s < 0)
    {
        printf("Error opening Socket\n");
        exit(1);
    }

    server = gethostbyname(server_name);

    if (server == NULL)
    {
        printf("Failed to connect to server make sure you have a working internet connection\n");
        exit(1);
    }

    bzero((char *)&serveraddr, sizeof(serveraddr));

    serveraddr.sin_family = AF_INET;

    bcopy((char *)server->h_addr, (char *)&serveraddr.sin_addr.s_addr, server->h_length);

    serveraddr.sin_port = htons(80);

    if (connect(s, (struct sockaddr *)&serveraddr, sizeof(serveraddr)) < 0)
    {
        printf("Error connecting\n");
        exit(1);
    }
    else
    {
        printf("Successfully connected\n");
    }

    return server;
}

// Function for manually parsing our servers response in an extremely ugly way
// Probably breaks for any HTTP-Implementation other than our specific server
// but it works
char* parse_server_response() {
    // printf("%s\n",response.buffer);

    int http_response_code;

    for (int i = 0; i < response.buffer_size; i++)
    {
        if (response.buffer[i] == ' ')
        {
            http_response_code = i + 1;
            break;
        }
    }

    // Read HTTP Response Code
    int response_code = parse_str(response.buffer + http_response_code, 3, 10);

    int content_length_offset;

    for (int i = http_response_code; i < response.buffer_size; i++)
    {
        if (response.buffer[i] == ':')
        {
            content_length_offset = i + 2;
            break;
        }
    }

    int len;

    // calculate content length length
    for (len = 0; (response.buffer + content_length_offset)[len] != '\r'; len++);

    // parse content length
    int content_length = parse_str(response.buffer + content_length_offset, len, 10);

    int body_start_offset;

    // find double line break to calculate body offset
    for (int i = content_length_offset + len; i < response.buffer_size; i++)
    {
        if (response.buffer[i] == '\r' && response.buffer[i + 1] == '\n' && response.buffer[i + 2] == '\r' && response.buffer[i + 3] == '\n')
        {
            body_start_offset = i + 4;
            break;
        }
    }

    // Load body content, in this case the encryption key or an error message
    char* key = response.buffer + body_start_offset;

    // check for error
    if (response_code != 302)
    {
        printf("%s\n", key);
        exit(1);
    }

    return key;
}

// unencrypts the key and prints it to stdout
void win()
{
    char* key = parse_server_response();

    xor(flag, key, 32);

    printf("%s\n", flag);
}

// Read User Input, overflows
int read_password() {
    char input[10];

    printf("Enter password: \n");

    scanf("%[^\n]", input);

    return 0;
}

int main() {
    FILE *self;

    // Open this file
    self = fopen("./crack", "r");

    if (self == NULL)
    {
        printf("Make sure the binary is called crack!\n");
        exit(1);
    }

    // Read the file content of the executable

    int byte;

    fseek(self, 0, SEEK_END);        // seek to end of file
    unsigned int size = ftell(self); // get current file pointer
    fseek(self, 0, SEEK_SET);        // seek back to beginning of file
    // proceed with allocating memory and reading the file

    int *file_content = malloc(sizeof(int) * size);

    int zaehler = 0;

    while ((byte = fgetc(self)) != EOF)
    {
        file_content[zaehler] = byte;
        zaehler++;
    }

    fclose(self);

    // Connect to our server and make a request checking the integrity of the
    // file

    char* data = arr_to_string(file_content, size);

    tcp_socket = socket(AF_INET, SOCK_STREAM, 0);

    server = connect_socket_to_server(tcp_socket, "blubi.codes");

    int i;

    for (i = 0; data[i] != '\0'; ++i);

    char *request = malloc(sizeof(char) * (i + 200));

    sprintf(request, "POST /check_data_integrity HTTP/1.1\r\nHost: %s\r\nContent-Type: application/json\r\nContent-Length: %d\r\n\r\n{\"bytes\": [%s]}", server->h_name, 14 + i - 1, data);

    if (send(tcp_socket, request, strlen(request), 0) < 0)
    {
        printf("Could not send request!\n");
    }

    free(request);

    response = read_socket_chunked(tcp_socket, 2);

    // let user give input
    int has_won = read_password();

    // has_won is always false
    if (has_won) {
        win();
    }

    free(file_content);
    free(data);
    free(response.buffer);

    return 0;
}
