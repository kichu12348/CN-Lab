
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

    int s_fd;

    s_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in s_addr, c_addr;

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_port = htons(PORT);

    socklen_t len = sizeof(c_addr);

    bind(s_fd, (struct sockaddr *)&s_addr, len);

    int n;

    while (1)
    {
        recvfrom(s_fd, &n, sizeof(int), 0, (struct sockaddr *)&c_addr, &len);

        int isPrime = isPrimeNumber(n);

        printf("Received %d, sending prime check %d\n", n, isPrime);

        sendto(s_fd, &isPrime, sizeof(int), 0, (struct sockaddr *)&c_addr, len);
    }

    close(s_fd);
}
