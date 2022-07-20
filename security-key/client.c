#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define max 100
#define port 8080
#define server_ip "127.0.0.1"

int main()
{
    int num,key;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_ip);
    serveraddr.sin_port = htons(port);

    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    while (1)
    {
        printf("\nEnter the data: ");
        scanf("%d", &num);
        write(sockfd, &num, sizeof(num));
        read(sockfd, &key, sizeof(key));
        printf("\nSecurity key is : %d", key);
    }
    return 0;
}