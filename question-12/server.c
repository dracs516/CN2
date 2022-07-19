#include<stdlib.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdio.h>

#define max 100
#define port 8080

int main()
{
    double HRA = 300000.0 , PF = 65000 , ben = 1250000;
    double salary = 0.0;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int sockfd = socket(AF_INET,SOCK_STREAM,0);
    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));
    listen(sockfd,4);
    while(1)
    {
        int clientLen = sizeof(clientaddr);
        int newsockfd = accept(sockfd,(struct sockaddr *)&clientaddr,&clientLen);
        printf("\nconnected to ip adddress: %s",inet_ntoa(clientaddr.sin_addr));
        int pid = fork();
        if(pid == 0)
        {
            while(1)
            {
                read(newsockfd,&salary,sizeof(salary));
                double total_salary = salary + HRA + PF + ben;
                write(newsockfd,&total_salary,sizeof(total_salary));
                printf("\nServer computation finished \n");
            }
            exit(0);
        }
        else
            close(newsockfd);
    }

    return 0;
}

