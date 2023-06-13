#include <stdio.h>
#include <time.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>
#include <strings.h>
#include <unistd.h>

#define MAXLINE 1024

int palindrome(int n)
{
    int reversed = 0, remainder, original;
    original = n;

    // reversed integer is stored in reversed variable
    while (n != 0)
    {
        remainder = n % 10;
        reversed = reversed * 10 + remainder;
        n /= 10;
    }

    // palindrome if orignal and reversed are equal
    if (original == reversed)
        return 1;
    else
        return 0;
}

int main(int argc, char **argv)
{
    int sockfd;
    int n;
    // char *buffer;

    socklen_t len;
    char msg[1024];
    char buffer[1024];
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

    // char text[100] = "yoooooo";

    int flag = palindrome(n);
    printf("%d", flag);
    if (flag)
    {
        char buffer[100] = "palindrome";
    }
    else
    {
        char buffer[100] = "not palindrome";
    }

    sendto(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, len);

    printf(" Sent date : %s\n\n", buffer);
    sendto(sockfd, (char *)buffer, sizeof(buffer), 0, (struct sockaddr *)&cliaddr, len);

    close(sockfd);

    return 0;
}