#include <arpa/inet.h>
#include <stdio.h>
#include <sys/types.h>  //socket
#include <sys/socket.h> //socket
#include <string.h>     //memset
#include <stdlib.h>     //sizeof
#include <netinet/in.h> //INADDR_ANY //what does this mean? //I think it means INADDR_ANY is the IP address of the host machine.

#define PORT 8080 // port number of server
#define MAXSZ 100 // max size of message
int main()
{
    int sockfd;    // to create socket
    int newsockfd; // to accept connection

    struct sockaddr_in serverAddress; // server receive on this address // client will connect on this address
    struct sockaddr_in clientAddress; // server sends to client on this address // client receives from server on this address

    int n;           // number of bytes received
    char msg[MAXSZ]; // message received from client
    int clientAddressLength;
    int pid; // to store the process id of the child process
    int n1, n2, ans, choice;
    char op;

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0); // AF_INET is the address family of the socket. SOCK_STREAM is the type of socket. 0 is the protocol.
    // initialize the socket addresses
    memset(&serverAddress, 0, sizeof(serverAddress));  // clear the address
    serverAddress.sin_family = AF_INET;                // IPv4
    serverAddress.sin_addr.s_addr = htonl(INADDR_ANY); // This is an IP address that is used when we don't want to bind a socket to any specific IP
    serverAddress.sin_port = htons(PORT);
    // hton is host to network byte order conversion
    // hton is used to convert the port number from host to network byte order (16 bits)
    // htonl is used to convert the IP address from host to network byte order (32 bits)

    // bind the socket with the server address and port
    bind(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress)); // bind the socket to the address and port number

    // listen for connection from client
    listen(sockfd, 5); // 5 is the number of clients that can connect to the server at the same time

    while (1)
    {
        // parent process waiting to accept a new connection
        printf("\n*****server waiting for new client connection:*****\n");
        clientAddressLength = sizeof(clientAddress); // initialize the client address length
        newsockfd = accept(sockfd, (struct sockaddr *)&clientAddress, &clientAddressLength);
        printf("connected to client: %s\n", inet_ntoa(clientAddress.sin_addr)); // inet_ntoa converts the IP address to a string
        printf("connected to client port: %d\n", (int)ntohs(clientAddress.sin_port));
        // child process is created for serving each new clients
        pid = fork();
        if (pid == 0) // child process rec and send
        {
            // rceive from client
            while (1)
            {
                read(newsockfd, &op, 10);
                read(newsockfd, &n1, sizeof(n1));
                read(newsockfd, &n2, sizeof(n2));

                printf("%d\t%d\t%c\n", n1, n2, op);
                switch (op)
                {
                case '+':
                    ans = n1 + n2;
                    break;
                case '-':
                    ans = n1 - n2;
                    break;
                case '*':
                    ans = n1 * n2;
                    break;
                case '/':
                    ans = n1 / n2;
                    break;
                default:
                    break;
                }
                write(newsockfd, &ans, sizeof(ans)); // send to client
                printf("Received and set:%d\n", ans);
            }
            exit(0); // child process exits // if child process exits, parent process will continue to accept new connection
        }
        else
        {
            close(newsockfd); // sock is closed BY PARENT // close the socket
        }
    } // close exterior while

    return 0;
}
