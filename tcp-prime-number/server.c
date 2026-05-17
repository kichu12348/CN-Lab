
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 3000;

int isPrimeNumber(int n)
{
    if (n <= 1)
        return 0;
    for (int i = 2; i <= n / 2; i++)
    {
        if (n % i == 0)
            return 0;
    }
    return 1;
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

    client_fd = accept(server_fd, (struct sockaddr *)&server_addr, &len);

    printf("Client connected.\n");

    int n;

    while (1)
    {
        recv(client_fd, &n, sizeof(int), 0);

        int isPrime = isPrimeNumber(n);

        printf("Received %d, sending prime check %d\n", n, isPrime);

        send(client_fd, &isPrime, sizeof(int), 0);
    }

    close(client_fd);
    close(server_fd);
}