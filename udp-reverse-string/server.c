
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 1024;
const int PORT = 3000;

void reverseString(char buff1[], char buff2[])
{
    int len = strlen(buff1) - 1;
    int left = 0;
    for (int i = len; i >= 0; i--)
    {
        buff2[left] = buff1[i];
        left++;
    }
}

void main()
{

    char buffer[BUFFER_SIZE];
    char reversed[BUFFER_SIZE];

    int s_fd;

    s_fd = socket(AF_INET, SOCK_DGRAM, 0);
    struct sockaddr_in s_addr, c_addr;

    s_addr.sin_family = AF_INET;
    s_addr.sin_addr.s_addr = INADDR_ANY;
    s_addr.sin_port = htons(PORT);

    socklen_t len = sizeof(c_addr);

    bind(s_fd, (struct sockaddr *)&s_addr, len);

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);   // clear the buffer
        memset(reversed, 0, BUFFER_SIZE); // clear the reversed buffer

        // read the message recived from client and put it in buffer
        recvfrom(s_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&c_addr, &len);

        reverseString(buffer, reversed);

        printf("%s reversed to %s\n", buffer, reversed);

        sendto(s_fd, reversed, BUFFER_SIZE, 0, (struct sockaddr *)&c_addr, len);

        memset(buffer, 0, BUFFER_SIZE);   // CLEAR THE buffer
        memset(reversed, 0, BUFFER_SIZE); // CLEAR THE reversed buffer
    }

    close(s_fd);
}
