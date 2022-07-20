#include<stdio.h>
#include<string.h>
#include<arpa/inet.h>
#include<sys/types.h>
#include<sys/socket.h>
#include<netinet/in.h>
#include<stdlib.h>


#define max 100
#define port 8080

int palindrome(int n)
{
    int reversed = 0, remainder, original;
    original = n;

    // reversed integer is stored in reversed variable
    while (n != 0) {
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

int main(){
    int num;
    char * ans;
    struct sockaddr_in serveraddress;
    struct sockaddr_in clientaddress;

    int sockfd = socket(AF_INET,SOCK_STREAM,0);

    memset(&serveraddress,0,sizeof(serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(port);

    bind(sockfd,(struct sockaddr *)&serveraddress,sizeof(serveraddress));

    listen(sockfd,5);
    while(1){

        int clientAddressLength = sizeof(clientaddress);
        int newsockfd = accept(sockfd,(struct sockaddr *)&clientaddress,&clientAddressLength);
        printf("\nConnected to client : %s ",inet_ntoa(clientaddress.sin_addr));
        int pid = fork();
        if(pid == 0)
        {
            while(1)
            {
                read(newsockfd,&num,sizeof(num));
                int palCheck = palindrome(num);
                if(palCheck)
                    ans = "palindrome";
                else
                    ans = "not palindrome";
                
                write(newsockfd,&ans,sizeof(ans));
                printf("\nServer computed the result\n");
                printf("%s",ans);
            }
            exit(0);
        }
        else
            close(newsockfd);
    }
    return 0;
}