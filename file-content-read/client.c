#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define port 8080
#define max 1024
#define server_ip "127.0.0.1"
int main()
{
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    char ans[max],filename[max];
    int pid,sockfd,newsockfd;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_ip);
    serveraddr.sin_port = htons(port);

    connect(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

    while(1)
    {
        printf("\nEnter file name :");
        gets(filename);

        write(sockfd,&filename,sizeof(filename));
        read(sockfd,&ans,sizeof(ans));
        printf("%s",ans);
    }

    return 0;
}