#include<stdlib.h>
#include<stdio.h>
#include<string.h>
#include<netinet/in.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>

#define max 100
#define port 8080

int main()
{
    char msg[max] = "you are connected to the server";
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int sockfd,newsockfd,pid;
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    listen(sockfd,1);

    while(1)
    {
        int clientLen = sizeof(clientaddr);
        newsockfd = accept(sockfd,(struct sockaddr *)&clientaddr,&clientLen);
        printf("\nConnected to client : %s",inet_ntoa(clientaddr.sin_addr));
        pid = fork();

        if(pid == 0)
        {
            while(1)
            {
                write(newsockfd,&msg,sizeof(msg));
                exit(0);
            }
            exit(0);
        }
        else
            close(newsockfd);
    }

    return 0;
}


