
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int BUFFER_SIZE = 1024;
const int PORT = 3000;

int is_palindrome(char buffer[])
{
    int left = 0;
    int right = strlen(buffer) - 1;

    while (left < right)
    {
        if (buffer[left] != buffer[right])
        {
            return 0; // Not a palindrome
        }
        left++;
        right--;
    }
    return 1; // Is a palindrome
}

void main()
{

    char buffer[BUFFER_SIZE];

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
        memset(buffer, 0, BUFFER_SIZE); // clear the buffer

        // read the message recived from client and put it in buffer
        recvfrom(s_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&c_addr, &len);

        int is_pali = is_palindrome(buffer);

        memset(buffer, 0, BUFFER_SIZE); // CLEAR THE buffer

        if (is_pali)
        {
            printf("the word is a palindrome\n");
            // write to buffer
            strcpy(buffer, "is a palindrome");
        }
        else
        {
            printf("the word is not a palindrome\n");
            // write to buffer
            strcpy(buffer, "is not a palindrome");
        }

        sendto(s_fd, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&c_addr, len); // echo the data back to the client
    }

    close(s_fd);
}