#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 1024;
const int PORT = 3000;

void main()
{
    int client_fd;
    struct sockaddr_in server_addr;

    client_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    socklen_t len = sizeof(server_addr);

    connect(client_fd, (struct sockaddr *)&server_addr, len);

    char buffer[BUFFER_SIZE];

    while (1)
    {
        printf("Enter a word: ");
        scanf("%s", buffer);

        send(client_fd, buffer, BUFFER_SIZE, 0);

        memset(buffer, 0, BUFFER_SIZE);

        recv(client_fd, buffer, BUFFER_SIZE, 0);

        printf("reversed string: %s\n", buffer);
    }
    close(client_fd);
}