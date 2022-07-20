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
    char msg[max], ans[max];

    struct sockaddr_in serveraddr;
    // struct sockaddr_in clientaddr; // not needed

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_addr);
    serveraddr.sin_port = htons(port);

    printf("Client up and running: \n");
    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    while (1)
    {
        printf("\nEnter string to reverse: ");
        gets(msg);
        // write msg to server
        write(sockfd, &msg, sizeof(msg));
        // read ans from server
        read(sockfd, &ans, sizeof(ans));
        printf("\nServer computed : %s", ans);
    }

    return 0;
}