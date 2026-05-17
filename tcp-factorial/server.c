#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 3000;

int factorial(int n)
{
    int fact = 1;
    for (int i = 1; i <= n; i++)
    {
        fact *= i;
    }
    return fact;
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

    client_fd = accept(server_fd, NULL, NULL);

    printf("Client connected.\n");

    int n;

    while (1)
    {
        recv(client_fd, &n, sizeof(int), 0);

        int fact = factorial(n);

        printf("Received %d, sending factorial %d\n", n, fact);

        send(client_fd, &fact, sizeof(int), 0);
    }

    close(client_fd);
    close(server_fd);
}