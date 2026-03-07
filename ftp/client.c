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
    char filename[100];

    while (1)
    {
        printf("Enter file to send: ");
        scanf("%s", filename);
        FILE *file = fopen(filename, "rb");
        memset(buffer, 0, BUF_SIZE);
        sendto(sockfd, filename, strlen(filename), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        int bytesRead;
        while ((bytesRead = fread(buffer, 1, BUF_SIZE, file)) > 0)
        {
            sendto(sockfd, buffer, bytesRead, 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        }
        memset(buffer, 0, BUF_SIZE);
        strcpy(buffer, "ENDBRO");

        sendto(sockfd, buffer, strlen(buffer), 0, (struct sockaddr *)&server_addr, sizeof(server_addr));
        printf("File sent successfully.\n");
        fclose(file);
    }
    close(sockfd);
}