#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <string.h>

#define max 100
#define port 8080
#define server_ip "127.0.0.1"

int main()
{
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_ip);
    serveraddr.sin_port = htons(port);

    int arr[10] = {5, 4, 3, 8, 9, 1, 2, 0, 6, 7};
    int arr1[10];

    printf("Client up and running: \n");
    int n = 10;
    printf("\nArray before sorting in client: ");
    for (int i = 0; i < n; i++)
    {
        printf("%d ", arr[i]);
    }
    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
        printf("\nArray elements sent to server\n");
        write(sockfd, &arr, 10 * sizeof(int));
        read(sockfd, &arr, 10 * sizeof(int));

        printf("\nArray after sorting in client: ");
        for (int i = 0; i < n; i++)
        {
            printf("%d ", arr[i]);
        }
    return 0;
}
