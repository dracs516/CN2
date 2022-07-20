#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>

#define port 8080
#define server_addr "127.0.0.1"
#define max 100

int main()
{
    char msg[max];
    time_t t;
    int day, month, year;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_addr);
    serveraddr.sin_port = htons(port);

    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    while (1)
    {
        // get some random message/request from user
        gets(msg);

        write(sockfd, &msg, sizeof(msg));

        read(sockfd, &day, sizeof(day));
        read(sockfd, &month, sizeof(month));
        read(sockfd, &year, sizeof(year));
        printf("\nServer computed : %d//%d//%d", day, month, year);
        // printf("\nServer computed : %d",day);
    }

    return 0;
}