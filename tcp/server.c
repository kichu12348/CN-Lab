#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <arpa/inet.h>

const int PORT = 8080;
const int BUFFER_SIZE = 1024;

void main()
{
    int server_fd, client_fd;
    struct sockaddr_in server_addr;

    char buffer[BUFFER_SIZE];

    server_fd = socket(AF_INET, SOCK_STREAM, 0);
    /*
    AF_INET means we are using the IPv4 protocol,
    SOCK_STREAM means we want a TCP socket,
     and 0 means we are using the
     default protocol for this type of socket (which is TCP for SOCK_STREAM).
     The socket() function creates a new socket and returns a file descriptor
     that can be used to refer to that socket in subsequent operations.
     If the socket creation fails, it returns -1.
    */
    // NO ERROR CHECKING FOR SIMPLICITY

    server_addr.sin_family = AF_INET; // sin_family means the address family i.e the network protocol. AF_INET means IPv4
    server_addr.sin_addr.s_addr = INADDR_ANY;
    /*
    sin_addr is a structure that contains a single field s_addr which is an unsigned long (32 bits) that represents the IP address in network byte order. INADDR_ANY is a constant that means "any IP address". It allows the server to accept connections on any of the host's IP addresses. This is useful when the server has multiple network interfaces or when you want to allow connections from any IP address.
    sin_addr is read as socket internet address, and s_addr is read as socket address. The s_addr field is used to store the IP address in a format that can be easily used by the socket functions. When you set sin_addr.s_addr to INADDR_ANY, it tells the server to listen for incoming connections on all available network interfaces, rather than just a specific IP address. This is a common practice for servers that want to be accessible from any network interface on the host machine.
    */
    server_addr.sin_port = htons(PORT);
    /*
    The htons() function converts the port number from host byte order to network byte order(bigendian). This is necessary because different computer architectures may use different byte orders (endianness), and network protocols typically use big-endian byte order. By using htons(), you ensure that the port number is correctly interpreted by the network stack regardless of the underlying architecture of the host machine.
    */

    // Bind the socket to the specified address and port
    bind(server_fd, (struct sockaddr *)&server_addr, sizeof(server_addr));
    /*
    sockaddr rather than sockaddr_in is used because the bind function expects a pointer
     to a struct sockaddr, which is a generic socket address structure that can represent
     different types of addresses (e.g., IPv4, IPv6). The sockaddr_in structure is specifically
     designed for IPv4 addresses and includes fields for the address family, IP address, and port number.
     By casting the pointer to (struct sockaddr *), we can pass the sockaddr_in structure to the
     bind function without any issues. This allows us to use the more specific sockaddr_in structure
      while still satisfying the requirements of the bind function.
    */

    // Listen for incoming connections
    listen(server_fd, 1); // only one connection at a time for simplicity
    printf("Server is listening on port %d\n", PORT);

    client_fd = accept(server_fd, NULL, NULL); // accept a connection from a client the args are (server_fd, struct sockaddr *client_addr, socklen_t *addrlen) but we don't care about the client's address for this simple example so we pass NULL
    printf("Client connected\n");
    while (1)
    {
        memset(buffer, 0, BUFFER_SIZE);          // clear the buffer
        recv(client_fd, buffer, BUFFER_SIZE, 0); // read data from the client
        if (strcmp(buffer, "exit\n") == 0)
        {
            printf("Client disconnected\n");
            break; // client disconnected
        }
        printf("Received from client: %s\n", buffer);
        printf("Enter a message to send back to the client (or 'exit' to disconnect): ");
        memset(buffer, 0, BUFFER_SIZE);         // clear the buffer before reading input
        fgets(buffer, BUFFER_SIZE, stdin);      // read a message from the user
        send(client_fd, buffer, BUFFER_SIZE, 0); // echo the data back to the client
    }

    close(client_fd); // close the client socket
    close(server_fd); // close the server socket
    /*
    always close connections and free resources
    always disconnect the client then only close the server
    */
}