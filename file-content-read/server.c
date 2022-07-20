#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>

#define port 8080
#define max 1024

int main()
{
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    char ans[max],filename[max];
    int pid,sockfd,newsockfd;

    sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&serveraddr,0,sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY); // This is an IP address that is used when we don't want to bind a socket to any specific IP
    serveraddr.sin_port = htons(port);

    bind(sockfd,(struct sockaddr *)&serveraddr,sizeof(serveraddr));

    listen(sockfd,5);

    while(1)
    {
        int clientLen = sizeof(clientaddr);
        newsockfd = accept(sockfd,(struct sockaddr *)&clientaddr,&clientLen);
        printf("\nConnected to client ip : %s",inet_ntoa(clientaddr.sin_addr));
        pid = fork();
        if(pid == 0)
        {
            while(1)
            {
                read(newsockfd,&filename,sizeof(filename));
                FILE* ptr;
                char ch;

                // Opening file in reading mode
                ptr = fopen(filename, "r");
            
                if (NULL == ptr) {
                    printf("file can't be opened \n");
                }
                else{
                    printf("content of this file are \n");
                    int k=0;
                    do {
                        ch = fgetc(ptr);
                        printf("%c", ch);
                        ans[k++] = ch;
                
                        // Checking if character is not EOF.
                        // If it is EOF stop eading.
                    } while (ch != EOF);
                    // ans[k] = '\0';
                
                    // Closing the file
                    fclose(ptr);
                    write(newsockfd,&ans,sizeof(ans));
                    printf("\nServer has read file content\n");
                }
            }
            exit(0);
        }
        else
            close(newsockfd);
    }
    return 0;
}

