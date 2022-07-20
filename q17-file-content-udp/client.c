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
	char filename[MAXLINE], ans[MAXLINE];
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

	int n, len;
	printf("\nEnter file name :");
	scanf("%s", &filename);
	sendto(sockfd, &filename, sizeof(filename), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
	printf("filename sent.\n");

	n = recvfrom(sockfd, &ans, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
	printf("Server : %s\n", ans);

	close(sockfd);
	return 0;
}
