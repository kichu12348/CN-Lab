#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int BUF_SIZE = 1024;
const int PORT = 8080;

void main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    char buffer[BUF_SIZE];

    while (1)
    {
        memset(buffer, 0, BUF_SIZE);
        printf("Enter message to send: ");
        fgets(buffer, BUF_SIZE, stdin);

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        if (strcmp(buffer, "exit") == 0)
        {
            printf("Exiting client.\n");
            break;
        }
        socklen_t len = sizeof(server_addr);
        recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&server_addr, &len);
        printf("Received response: %s\n", buffer);
    }
    close(sockfd);
}