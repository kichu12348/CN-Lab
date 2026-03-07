#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

void main()
{
    int sock_fd;
    struct sockaddr_in server_addr;

    char buffer[BUFFER_SIZE];
    sock_fd = socket(AF_INET, SOCK_STREAM, 0);
    // NO ERROR CHECKING FOR SIMPLICITY
    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = inet_addr("127.0.0.1"); // connect to localhost
    /*
    inet_addr() function converts the IPv4 address from the dotted-decimal string format (e.g., "192.168.1.1")
    to a 32-bit binary representation in network byte order. This is necessary because
    the socket functions expect the IP address to be in this format when establishing
     a connection. By using inet_addr("127.0.0.1"), we specify that the client should connect to
     the server running on the same machine (localhost).
     inet_addr is read as

    */
    server_addr.sin_port = htons(PORT);
    connect(sock_fd, (struct sockaddr *)&server_addr, sizeof(server_addr)); // connect to the server
    printf("Connected to server on port %d\n", PORT);
    while (1)
    {
        printf("Enter a message to send to the server (or 'exit' to quit): ");
        fgets(buffer, BUFFER_SIZE, stdin); // read a message from the user
        /*
        fgets instead of scanf is used to read a line of input from the user, including spaces.
        This allows the user to enter messages that
        contain spaces without prematurely terminating the input.
        The fgets function reads up to BUFFER_SIZE - 1 characters from stdin and stores them in the buffer,
        ensuring that there is room for the null terminator. It also includes the newline character
        if the user presses Enter, which is why we check for "exit\n" when determining if the user wants to quit.
        */
        send(sock_fd, buffer, strlen(buffer), 0); // send the message to the server
        if (strcmp(buffer, "exit\n") == 0)
        {
            printf("Exiting...\n");
            break; // exit the loop if the user wants to quit
        }
        memset(buffer, 0, BUFFER_SIZE);                         // clear the buffer
        int bytes_read = recv(sock_fd, buffer, BUFFER_SIZE, 0); // read the response from the server
        printf("Received from server: %s\n", buffer);
    }
    close(sock_fd); // close the socket
}