#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#define max 100
#define port 8080

int main()
{
    int arr[10], n;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;
    int sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(sockfd, 4);

    printf("Server up and running: \n");
        int clientLen = sizeof(clientaddr);
        int newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &clientLen);
        printf("\nconnected to ip adddress: %s", inet_ntoa(clientaddr.sin_addr));

                read(newsockfd, &arr, 10 * sizeof(int));
                for (int i = 0; i < 10; i++)
                {
                    for (int j = i + 1; j < 10; j++)
                    {
                        if (arr[i] > arr[j])
                        {
                            int temp = arr[i];
                            arr[i] = arr[j];
                            arr[j] = temp;
                        }
                    }
                }

                printf("\nSorted Array in server:");

                for (int i = 0; i < 10; i++)
                {
                    printf("%d ", arr[i]);
                }

                write(newsockfd, &arr, 10 * sizeof(int));
            close(sockfd);
    return 0;
}
