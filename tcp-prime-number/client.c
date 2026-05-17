#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

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

    int n, isPrime;

    while (1)
    {
        printf("Enter a number: ");
        scanf("%d", &n);

        send(client_fd, &n, sizeof(int), 0);

        recv(client_fd, &isPrime, sizeof(int), 0);

        if (isPrime)
        {
            printf("%d is a prime number.\n", n);
        }
        else
        {
            printf("%d is not a prime number.\n", n);
        }
    }
    close(client_fd);
}