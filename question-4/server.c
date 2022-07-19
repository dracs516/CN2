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

    int pid, sockfd, newsockfd;
    char msg[max];
    int day, month, year;
    struct sockaddr_in serveraddress;
    struct sockaddr_in clientaddress;

    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddress, 0, sizeof(serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *)&serveraddress, sizeof(serveraddress));

    listen(sockfd, 5);
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
                read(newsockfd, &msg, sizeof(msg));
                printf('%s ', msg);
                time_t now;
                time(&now);
                ctime(&now) struct tm *local = localtime(&now);
                day = local->tm_mday;      // get day of month (1 to 31)
                month = local->tm_mon + 1; // get month of year (0 to 11)
                year = local->tm_year + 1900;

                write(newsockfd, &day, sizeof(day));
                write(newsockfd, &month, sizeof(month));
                write(newsockfd, &year, sizeof(year));
            }
            exit(0);
        }
        else
            close(newsockfd);
    }
    return 0;
}
