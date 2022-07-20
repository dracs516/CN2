#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1024

int main(int argc, char **argv)
{
       int sockfd;
       int n;

       socklen_t len;
       char msg[1024], buffer[1024];
       struct sockaddr_in servaddr, cliaddr;

       sockfd = socket(AF_INET, SOCK_DGRAM, 0);
       bzero(&servaddr, sizeof(servaddr));

       servaddr.sin_family = AF_INET;
       servaddr.sin_addr.s_addr = INADDR_ANY;
       servaddr.sin_port = htons(5034);

       printf("\n\n Binded");
       bind(sockfd, (struct sockaddr *)&servaddr, sizeof(servaddr));

       printf("\n\n Listening...\n\n");

       len = sizeof(cliaddr);
       n = recvfrom(sockfd, msg, MAXLINE, 0, (struct sockaddr *)&cliaddr, &len);

       char text[100];
       time_t now = time(NULL);
       struct tm *t = localtime(&now);

       strftime(text, sizeof(text)-1, "%d/%m/%Y %H:%M:%S", t);
       sendto(sockfd, text, n, 0, (struct sockaddr *)&cliaddr, len);

       printf(" Sent date : %s\n\n", text);
       sendto(sockfd, text, n, 0, (struct sockaddr *)&cliaddr, len);

       close(sockfd);

       return 0;
}