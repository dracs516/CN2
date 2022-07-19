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
    int jack,diff,david=0;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int sockfd,newsockfd,pid;
    sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    listen(sockfd,5);

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
                read(newsockfd,&jack,sizeof(jack));
                read(newsockfd,&diff,sizeof(diff));
                david = jack+diff;
                write(newsockfd,&david,sizeof(david));
                printf("\nServer computed result\n");
            }
            exit(0);
        }
        else
            close(newsockfd);
    }

    return 0;
}


