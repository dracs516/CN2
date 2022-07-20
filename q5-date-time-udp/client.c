// Client side implementation of UDP client-server model
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <netinet/in.h>

#define PORT 8080
#define MAXLINE 1024

// Driver code
int main()
{
	int sockfd;
	char buffer[MAXLINE];
	int day = 0, month = 0, year;
	char *hello = "Hello from client";
	struct sockaddr_in servaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
		perror("socket creation failed");
		exit(EXIT_FAILURE);
	}

	memset(&servaddr, 0, sizeof(servaddr));

	// Filling server information
	servaddr.sin_family = AF_INET;
	servaddr.sin_port = htons(PORT);
	servaddr.sin_addr.s_addr = INADDR_ANY;

	int n, x, y, len;

	sendto(sockfd, (const char *)hello, strlen(hello), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("Hello message sent.\n");

	n = recvfrom(sockfd, &day, sizeof(day), MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
	x = recvfrom(sockfd, &month, sizeof(month), MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
	y = recvfrom(sockfd, &year, sizeof(year), MSG_WAITALL, (struct sockaddr *)&servaddr, &len);

	// buffer[n] = '\0';
	printf("Server : Date is %02d/%02d/%04d\n", day, month + 1, year + 1900);

	close(sockfd);
	return 0;
}
