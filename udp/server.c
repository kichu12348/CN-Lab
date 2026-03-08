#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int BUF_SIZE = 1024;
const int PORT = 8080;

// simple UDP server implementation

void main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr, client_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    socklen_t addr_len = sizeof(server_addr);
    socklen_t len = sizeof(client_addr);

    bind(sockfd, (struct sockaddr *)&server_addr, addr_len);

    char buffer[BUF_SIZE];

    while (1)
    {
        memset(buffer, 0, BUF_SIZE);
        recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &len);
        printf("Received message: %s\n", buffer);
        if (strcmp(buffer, "exit") == 0)
        {
            printf("Exiting server.\n");
            break;
        }
        printf("Entering response: ");
        memset(buffer, 0, BUF_SIZE);
        fgets(buffer, BUF_SIZE, stdin);
        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&client_addr, len);
    }
    close(sockfd);
}