// Server side implementation of UDP client-server model
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
	// char *hello = "Hello from server";
	struct sockaddr_in servaddr, cliaddr;

	// Creating socket file descriptor
	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
	{
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
	if (bind(sockfd, (const struct sockaddr *)&servaddr, sizeof(servaddr)) < 0)
	{
		perror("bind failed");
		exit(EXIT_FAILURE);
	}

	int len, n;

	len = sizeof(cliaddr); // len is value/result

	n = recvfrom(sockfd, &filename, MAXLINE, MSG_WAITALL, (struct sockaddr *)&cliaddr, &len);
	printf("Client : %s\n", filename);
	FILE *ptr;
	char ch;

	// Opening file in reading mode
	ptr = fopen(filename, "r");

	if (NULL == ptr)
	{
		printf("file can't be opened \n");
	}
	else
	{
		printf("content of this file are \n");
		int k = 0;
		do
		{
			ch = fgetc(ptr);
			printf("%c", ch);
			ans[k++] = ch;

			// Checking if character is not EOF.
			// If it is EOF stop reading.
		} while (ch != EOF);
		ans[k] = '\0';

		// Closing the file
		fclose(ptr);
	}

	sendto(sockfd, &ans, sizeof(ans), MSG_CONFIRM, (const struct sockaddr *)&cliaddr, len);
	printf("Hello message sent.\n");

	return 0;
}
