/*
1. John has a problem of finding the square of a number.
He contacts the server and sends thenumber.
Server computes the result and returns back to the client.Implement this scenario using
a connection oriented approach.
*/
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
    char string[max],revString[max];

    struct sockaddr_in serveraddress;
    struct sockaddr_in clientaddress;

    int sockfd = socket(AF_INET, SOCK_STREAM, 0);

    memset(&serveraddress, 0, sizeof(serveraddress));
    serveraddress.sin_family = AF_INET;
    serveraddress.sin_addr.s_addr = htonl(INADDR_ANY);
    serveraddress.sin_port = htons(port);

    bind(sockfd, (struct sockaddr *)&serveraddress, sizeof(serveraddress));

    listen(sockfd, 5);
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
                read(newsockfd, &string, sizeof(string));
                int i, len, temp;  
                len = strlen(string); // use strlen() to get the length of str string  
                
                // use for loop to iterate the string   
                for (i = 0; i < len/2; i++)  
                {  
                    // temp variable use to temporary hold the string  
                    temp = string[i];  
                    string[i] = string[len - i - 1];  
                    string[len - i - 1] = temp;  
                }  
                write(newsockfd, &string, sizeof(string));
                printf("\nServer computed the result\n");
            }
            exit(0);
        }
        else
            close(newsockfd);
    }
    return 0;
}