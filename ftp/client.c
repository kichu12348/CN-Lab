#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

void main()
{
    int sockfd = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in server_addr;

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    server_addr.sin_port = htons(PORT);

    char buffer[BUFFER_SIZE];
    char filename[100];

    socklen_t len = sizeof(server_addr);

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        printf("enter filename: ");
        scanf("%s", filename);

        FILE *file = fopen(filename, "rb");

        sendto(sockfd, filename, 100, 0, (struct sockaddr *)&server_addr, len);

        while (1)
        {
            int bytes = fread(buffer, 1, BUFFER_SIZE, file);
            if (bytes == 0)
                break;
            sendto(sockfd, buffer, bytes, 0, (struct sockaddr *)&server_addr, len);
        }
        memset(buffer, 0, BUFFER_SIZE);
        strcpy(buffer, "END");
        sendto(sockfd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&server_addr, len);
        fclose(file);
    }
}
