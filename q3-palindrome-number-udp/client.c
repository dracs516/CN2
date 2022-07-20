// // Client side implementation of UDP client-server model
// #include <stdio.h>
// #include <stdlib.h>
// #include <unistd.h>
// #include <string.h>
// #include <sys/types.h>
// #include <sys/socket.h>
// #include <arpa/inet.h>
// #include <netinet/in.h>

// #define PORT 8080
// #define MAXLINE 1024

// // Driver code
// int main()
// {
// 	int sockfd;
// 	char *buffer;
// 	int num = 121;
// 	struct sockaddr_in servaddr;

// 	// Creating socket file descriptor
// 	if ((sockfd = socket(AF_INET, SOCK_DGRAM, 0)) < 0)
// 	{
// 		perror("socket creation failed");
// 		exit(EXIT_FAILURE);
// 	}

// 	memset(&servaddr, 0, sizeof(servaddr));

// 	// Filling server information
// 	servaddr.sin_family = AF_INET;
// 	servaddr.sin_port = htons(PORT);
// 	servaddr.sin_addr.s_addr = INADDR_ANY;

// 	int n, len;

// 	sendto(sockfd, &num, sizeof(num), MSG_CONFIRM, (const struct sockaddr *)&servaddr, sizeof(servaddr));
// 	printf("number sent.\n");

// 	n = recvfrom(sockfd, (char *)buffer, MAXLINE, MSG_WAITALL, (struct sockaddr *)&servaddr, &len);
// 	buffer[n] = '\0';
// 	printf("Server : %s\n", buffer);

// 	close(sockfd);
// 	return 0;
// }

#include <stdio.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>

#define MAXLINE 1024

int main(int argc, char *argv[])
{
	int sockfd;
	int num = 121;

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
	sendto(sockfd, &num, sizeof(num), 0, (struct sockaddr *)&servaddr, len);
	printf("number sent.\n");

	n = recvfrom(sockfd, recvline, MAXLINE, 0, NULL, NULL);
	printf("\nTime from server = %s\n\n", recvline);

	close(sockfd);

	return 0;
}