#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>  //socket
#include <sys/socket.h> //socket
#include <string.h>     //memset
#include <stdlib.h>     //sizeof
#include <netinet/in.h> //INADDR_ANY // INADDR_ANY is the IP address of the host machine.
#define PORT 8080
#define SERVER_IP "127.0.0.1"
#define MAXSZ 100 // max size of message
int main()
{
    int sockfd; // to create socket

    struct sockaddr_in serverAddress; // client will connect on this

    // int n, n1, n2, choice, ans, i = 0, j = 0;
    int n1, n2, ans;
    char op;
    char msg1[MAXSZ];
    char msg2[MAXSZ];

    // create socket
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    // initialize the socket addresses
    // memset is used to set the memory area pointed to by ptr to the value of val.
    memset(&serverAddress, 0, sizeof(serverAddress));
    serverAddress.sin_family = AF_INET;
    serverAddress.sin_addr.s_addr = inet_addr(SERVER_IP); // inet_addr converts the IP address to a 32-bit number.
    serverAddress.sin_port = htons(PORT);                 // htons makes sure its in big endian

    // client  connect to server on port
    connect(sockfd, (struct sockaddr *)&serverAddress, sizeof(serverAddress));
    // send to server and receive from server
    while (1)
    {
        // printf("1:Addition\n2:Subtraction\n3:Multiplication\n4:Division\n");
        // printf("\nEnter your option:\n");
        // scanf("%d",&choice);
        // printf("\nEnter 2 Numbers:\n");
        printf("\nEnter the expression:\n");
        gets(msg1);
        n1 = msg1[0] - '0';
        n2 = msg1[2] - '0';
        op = msg1[1];
        printf("%d\t%c\t%d\n", n1, op, n2);
        write(sockfd, &op, 10);
        write(sockfd, &n1, sizeof(n1));
        write(sockfd, &n2, sizeof(n2));

        read(sockfd, &ans, sizeof(ans));
        printf("Received message from  server::%d\n", ans);
    }
    return 0;
}
