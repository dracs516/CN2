#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>

#define max 100
#define port 8080
#define server_ip "127.0.0.1"

int main()
{
    double salary = 0.0, total_salary = 0.0;
    struct sockaddr_in serveraddr;
    struct sockaddr_in clientaddr;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddr, 0, sizeof(serveraddr));
    serveraddr.sin_family = AF_INET;
    serveraddr.sin_addr.s_addr = inet_addr(server_ip);
    serveraddr.sin_port = htons(port);

    connect(sockfd, (struct sockaddr *)&serveraddr, sizeof(serveraddr));

    while (1)
    {
        printf("\nEnter the salary : ");
        scanf("%f", &salary);
        write(sockfd, &salary, sizeof(salary));
        read(sockfd, &total_salary, sizeof(total_salary));
        printf("\nTotal Compensation Package : %f", total_salary);
    }
    return 0;
}