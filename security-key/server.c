#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define max 100
#define port 8080

int security_key(int n)
{
    int arr[10] = {-1,0,0,0,0,0,0,0,0,0};
    int key=0;
    while(n) {

        int rem = n%10; 
        switch(rem)
        {
            case 1:arr[1]++;break;
            case 2:arr[2]++;break;
            case 3:arr[3]++;break;
            case 4:arr[4]++;break;
            case 5:arr[5]++;break;
            case 6:arr[6]++;break;
            case 7:arr[7]++;break;
            case 8:arr[8]++;break;
            case 9:arr[9]++;break;
        }
        n=n/10; 
    }
    for (int i = 1; i < 10; ++i) {
        if (arr[0] < arr[i]) {
            arr[0] = arr[i];
            key = i;
        }
    }
    return key;
}

int main()
{
    int data,key;

    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddr.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));
    listen(sockfd, 4);
    while (1)
    {
        int clientLen = sizeof(clientaddr);
        int newsockfd = accept(sockfd, (struct sockaddr *)&clientaddr, &clientLen);
        printf("\nconnected to ip adddress: %s", inet_ntoa(clientaddr.sin_addr));

        int pid = fork();

        if (pid == 0)
        {
            while (1)
            {
                read(newsockfd, &data, sizeof(data));
                key = security_key(data);

                write(newsockfd, &key, sizeof(key));
                printf("\nServer computed secure key \n");
            }
            exit(0);
        }
        else
            close(newsockfd);
    }

    return 0;
}
