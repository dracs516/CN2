#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1024

int main(int argc, char *argv[])
{
       int sockfd;
       int n;

       socklen_t len;
       char sendline[1024], recvline[1024];
       struct sockaddr_in servaddr;

       sockfd = socket(AF_INET, SOCK_DGRAM, 0);

       bzero(&servaddr, sizeof(servaddr));

       servaddr.sin_family = AF_INET;
       servaddr.sin_addr.s_addr = inet_addr("127.0.0.1");
       servaddr.sin_port = htons(5034);

       connect(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

       len = sizeof(servaddr);
       sendto(sockfd, sendline, MAXLINE, 0, (struct sockaddr *)&servaddr, len);

       n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
       printf("\nTime from server = %s\n\n", recvline);

       close(sockfd);

       return 0;
}