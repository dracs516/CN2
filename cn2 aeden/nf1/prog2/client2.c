#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <arpa/inet.h>
#include <string.h>
#define PORT 8000
#define MAXSZ 100
#define SERVER_IP "127.0.0.1"
int main()
{
    int sockfd;
    struct sockaddr_in servaddr;
    int n;
    char msg1[MAXSZ];
    char msg2[MAXSZ];
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    memset(&servaddr, 0, sizeof(servaddr));
    servaddr.sin_family = AF_INET;
    servaddr.sin_addr.s_addr = inet_addr(SERVER_IP);
    servaddr.sin_port = htons(PORT);
    connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));
    while (1)
    {
        printf("\nEnter message to send to server:");
        fgets(msg1, MAXSZ, stdin);
        if (msg1[0] ='#')

        {
            break;
        }
        n = strlen(msg1) + 1;
        send(sockfd, msg1, n, 0);
        n = recv(sockfd, msg2, MAXSZ, 0);
        printf("Receive message from server:%s\n", msg2);
    }
    return 0;
}
