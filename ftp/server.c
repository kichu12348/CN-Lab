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

    bind(sockfd, (struct sockaddr *)&server_addr, sizeof(server_addr));

    char buffer[BUF_SIZE];
    char filename[100];

    while (1)
    {
        socklen_t len = sizeof(client_addr);
        recvfrom(sockfd, filename, 100, 0, (struct sockaddr *)&client_addr, &len);
        printf("Receiving file: %s\n", filename);
        FILE *file = fopen(filename, "wb");
        memset(buffer, 0, BUF_SIZE);
        while (1)
        {
            int bytes = recvfrom(sockfd, buffer, BUF_SIZE, 0, (struct sockaddr *)&client_addr, &len);
            if (strcmp(buffer, "ENDBRO") == 0)
            {
                printf("File received successfully.\n");
                break;
            }
            fwrite(buffer, 1, bytes, file);
        }
        fclose(file);
        memset(filename, 0, 100);
    }
    close(sockfd);
}