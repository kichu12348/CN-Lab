
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 3000;

void main()
{
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    s_addr.sin_port = htons(3000);

    socklen_t len = sizeof(s_addr);

    int n, fact;

    while (1)
    {

        printf("Enter a number: ");
        scanf("%d", &n);

        sendto(sock, &n, sizeof(int), 0, (struct sockaddr *)&s_addr, len);

        recvfrom(sock, &fact, sizeof(int), 0, (struct sockaddr *)&s_addr, &len);

        printf("Received from server: %d\n", fact);
    }

    close(sock);
}