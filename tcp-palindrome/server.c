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
    int server_fd, client_fd;
    struct sockaddr_in server_addr;

    server_fd = socket(AF_INET, SOCK_STREAM, 0);

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = INADDR_ANY;
    server_addr.sin_port = htons(PORT);

    socklen_t len = sizeof(server_addr);

    bind(server_fd, (struct sockaddr *)&server_addr, len);

    listen(server_fd, 1);

    printf("Server is listening on port %d...\n", PORT);

    char buffer[BUFFER_SIZE];

    client_fd = accept(server_fd, (struct sockaddr *)&server_addr, &len);

    printf("Client connected.\n");

    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);
        recv(client_fd, buffer, BUFFER_SIZE, 0);
        int is_pali = is_palindrome(buffer);

        memset(buffer, 0, BUFFER_SIZE);

        if (is_pali)
        {
            strcpy(buffer, "Palindrome");
            printf("The word is a palindrome.\n");
        }
        else
        {
            strcpy(buffer, "Not a Palindrome");
            printf("The word is not a palindrome.\n");
        }
        send(client_fd, buffer, BUFFER_SIZE, 0);
    }

    close(client_fd);
    close(server_fd);
}