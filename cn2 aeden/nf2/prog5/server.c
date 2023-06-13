#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <unistd.h>

#define max 100
#define port 8080

int main()
{
    char string[max], newString[max];
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int sockfd, newsockfd, pid;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(sockfd, 5);

    while (1)
    {
        int clientLen = sizeof(clientaddr);
        newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &clientLen);
        printf("\nConnected to client : %s", inet_ntoa(clientaddr.sin_addr));
        pid = fork();

        if (pid == 0)
        {
            while (1)
            {
                read(newsockfd, &string, sizeof(string));
                int c = 0;
                while (string[c] != '\0')
                {
                    if (string[c] >= 'a' && string[c] <= 'z')
                    {
                        string[c] = string[c] - 32;
                    }

                    else if (string[c] >= 'A' && string[c] <= 'Z')
                    {
                        string[c] = string[c] + 32;
                    }
                    c++;
                }
                write(newsockfd, &string, sizeof(string));
                printf("\nServer computed result\n");
            }
            exit(0);
        }
        else
            close(newsockfd);
    }

    return 0;
}