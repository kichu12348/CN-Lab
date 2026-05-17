
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

        // in both sendto and recvfrom from you pass socket then buffer then the size of the buffer and the 0 is for flags
        // in exam you dont need to be bothered about what the 0 does just put it there
        // in tcp its send and recv in both of them you just need up to flags
        // for example send(sock,buffer,BUFFER_SIZE,0);
        // in udp you also need to pass in the address of the server as
        // well and the size of the server address i.e the variable len
        // example sendto(sock,buffer,BUFFER_SIZE,0,(struct sockaddr*)&s_addr,len)
        // we do (struct sockaddr*) to say that the s_addr is an instance of sockaddr and not sockaddr_in
        // sockaddr_in is for ipv4
        // the os will figure that out but do not forget (struct sockaddr*)&s_addr
        // in recvfrom its the same except instead of passing the value of len we pass a pointer so it can
        // be modified by the os

        printf("Enter a word to send back to the server: ");
        memset(buffer, 0, BUFFER_SIZE); // clear the buffer before reading input
        // i.e it sets every value in the buffer to 0, essentially clearing the buffer

        // read word from user.
        scanf("%s", buffer);

        // in sendto you just pass the length/size len as is so directly
        sendto(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&s_addr, len); // echo the data back to the client

        // in recvfrom you pass the address or pointer so hence &len because the value might be manipulated by the os
        recvfrom(sock, buffer, BUFFER_SIZE, 0, (struct sockaddr *)&s_addr, &len);

        printf("Received from server: %s\n", buffer);
    }

    close(sock);
}