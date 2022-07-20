#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

#define port 8080
#define server_addr "127.0.0.1"
#define max 100

int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int n1, n2, ans;
    char string[max];

    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_addr);
    serveraddr.sin_port = htons(port);

    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    while (1)
    {
        printf("\nEnter expression to be executed : ");
        gets(string);

        write(sockfd, &string, sizeof(string));

        read(sockfd, &string, sizeof(string));
        printf("\nServer computed : %s", string);
    }

    return 0;
}