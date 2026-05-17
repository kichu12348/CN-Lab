
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 1024;
const int PORT = 3000;

void main()
{

    char buffer[BUFFER_SIZE];
    int sock = socket(AF_INET, SOCK_DGRAM, 0);

    struct sockaddr_in s_addr;
    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = inet_addr("127.0.0.1");
    s_addr.sin_port = htons(3000);

    socklen_t len = sizeof(s_addr);

    while (1)
    {
        printf("Enter a word: ");
        memset(buffer, 0, BUFFER_SIZE); // clear the buffer before reading input
        // i.e it sets every value in the buffer to 0, essentially clearing the buffer

        // read word from user.
        scanf("%s", buffer);

        // in sendto you just pass the length/size len as is so directly
        sendto(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&s_addr, len); // echo the data back to the client

        // in recvfrom you pass the address or pointer so hence &len because the value might be manipulated by the os
        recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&s_addr, &len);

        printf("reversed string is: %s\n", buffer);
    }

    close(sock);
}