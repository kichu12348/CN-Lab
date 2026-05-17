#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 1024;

const int PORT = 8080;

void reverseString(char buff1[], char buff2[])
{
    int len = strlen(buff1) - 1;
    int left = 0;
    for (int i = len; i >= 0; i--)
    {
        buff2[left] = buff1[i];
        left++;
    }
}

void main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    socklen_t len = sizeof(server_addr);

    bind(server_fd, (struct sockaddr *)&server_addr, len);

    listen(server_fd, 1);

    printf("Server is listening on port %d...\n", PORT);

    char buffer[BUFFER_SIZE];
    char buff2[BUFFER_SIZE];

    client_fd = accept(server_fd, NULL, NULL);

    printf("Client connected.\n");

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        memset(buff2, 0, BUFFER_SIZE);
        recv(client_fd, buffer, BUFFER_SIZE, 0);

        reverseString(buffer, buff2);

        printf("%s reversed is: %s\n", buffer, buff2);

        send(client_fd, buff2, BUFFER_SIZE, 0);

        memset(buffer, 0, BUFFER_SIZE);
        memset(buff2, 0, BUFFER_SIZE);
    }

    close(client_fd);
    close(server_fd);
}