// Server side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>
#include <time.h>
	
#define PORT	 8080
#define MAXLINE 1024
	
// Driver code
int main() {
	int sockfd;
	char buffer[MAXLINE];
	char *hello = "Hello from server";

    time_t T = time(NULL);
    struct tm tm = *localtime(&T);

    int day = tm.tm_mday, month = tm.tm_mon, year = tm.tm_year;
    printf("%02d",day);
    char d = day+'0',m = month+'0' , y = year+'0';

	struct sockaddr_in servaddr, cliaddr;
		
	// Creating socket file descriptor
	if ( (sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0 ) {
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}
		
	memset(&servaddr, 0, sizeof(servaddr));
	memset(&cliaddr, 0, sizeof(cliaddr));
		
	// Filling server information
	servaddr.sin_family = AF_INET; // IPv4
	servaddr.sin_addr.s_addr = INADDR_ANY;
	servaddr.sin_port = htons(PORT);
		
	// Bind the socket with the server address
	if ( bind(sockfd, (const struct sockaddr *)&servaddr,sizeof(servaddr)) < 0 )
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}
		
	int len, n;
	
	len = sizeof(cliaddr); //len is value/result
	
	n = recvfrom(sockfd, (char *)buffer, MAXLINE,MSG_WAITALL, ( struct sockaddr *) &cliaddr,&len);
	buffer[n] = '\0';
	printf("\nClient : %s\n", buffer);

	sendto(sockfd, &day, sizeof(day),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
	sendto(sockfd, &month, sizeof(month),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);
	sendto(sockfd, &year, sizeof(year),MSG_CONFIRM, (const struct sockaddr *) &cliaddr,len);

	printf("Hello message sent.\n");
		
	return 0;
}
