
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

        int fact = factorial(n);

        printf("Received %d, sending factorial %d\n", n, fact);

        sendto(s_fd, &fact, sizeof(int), 0, (struct sockaddr *)&c_addr, len);
    }

    close(s_fd);
}
