
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

        int len_of_str = strlen(buffer);

        int i = 0, j = len_of_str - 1;

        int is_pali = 1;

        while (j >= i)
        {
            // i and j are pointers on either ends of the word
            // i starts from the left and moves right and j starts from right and moves left
            // compare each character on the pointers if they are not equal that means the word
            // is not a palindrome

            if (buffer[i] != buffer[j])
            {
                is_pali = 0;
                break;
            }

            // move i to right by 1 i.e i = i + 1;
            i++;

            // move j to left by 1 i.e j = j - 1;
            j--;
        }

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