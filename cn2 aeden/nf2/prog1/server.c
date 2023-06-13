#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>

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
                ans = n1 * n1;
                write(newsockfd, &ans, sizeof(ans));
                printf("\nServer computed the result\n");
            }
            exit(0);
        }
        else
            close(newsockfd);
    }
    return 0;
}
