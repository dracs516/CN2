#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>


#define max 100
#define port 8080
#define server_ip "127.0.0.1"

int main()
{
    char msg[max];
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int sockfd,newsockfd,pid;
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_ip);
    serveraddr.sin_port = htons(port);

    connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

    while(1)
    {
        read(sockfd,&msg,sizeof(msg));
        printf("\nServer said : %s",msg);
        exit(0);
    }
    return 0;
}