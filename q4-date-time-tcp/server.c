/*
1. John has a problem of finding the square of a number.
He contacts the server and sends thenumber.
Server computes the result and returns back to the client.Implement this scenario using
a connection oriented approach.
*/
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <time.h>

#define max 100
#define port 8080

int main()
{
    int n1, ans;

    struct sockaddr_in serveraddress;
    struct sockaddr_in clientaddress;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddress, 0, sizeof(serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *)&serveraddress, sizeof(serveraddress));

    listen(sockfd, 5);
    printf("Server up and running.\n");
    while (1)
    {

        int clientAddressLength = sizeof(clientaddress);
        int newsockfd = accept(sockfd, (struct sockaddr *)&clientaddress, &clientAddressLength);
        printf("\nConnected to client %s : ", inet_ntoa(clientaddress.sin_addr));
        int pid = fork();
        if (pid == 0)
        {
            while (1)
            {
                read(newsockfd, &n1, sizeof(n1));

                char text[100];
                time_t now = time(NULL);
                struct tm *t = localtime(&now);
                strftime(text, sizeof(text) - 1, "%d/%m/%Y %H:%M:%S", t);

                write(newsockfd, &text, sizeof(text));
                printf("\nSent date : %s\n\n", text);
            }
            exit(0);
        }
        else
            close(newsockfd);
    }
    return 0;
}