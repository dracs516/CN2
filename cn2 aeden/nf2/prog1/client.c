#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <unistd.h>

#define port 8080
#define server_addr "127.0.0.1"
#define max 100

int main()
{

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    int n1, ans;

    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_addr);
    serveraddr.sin_port = htons(port);

    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    while (1)
    {
        printf("\nEnter the number to be squared : ");
        scanf("%d", &n1);

        write(sockfd, &n1, sizeof(n1));

        read(sockfd, &ans, sizeof(ans));
        printf("\nServer computed : %d", ans);
    }

    return 0;
}
