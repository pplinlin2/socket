#include "socket.h"

/*
socket -> connect -> read/write -> close
*/
int main()
{
	int sockfd;
	struct sockaddr_in server;
	char buf[100];
	int bytes;

	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if(sockfd < 0){
		perror("Socket error.");
		return -1;
	}

	bzero(buf, 100);
	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port   = htons(8888);
	server.sin_addr.s_addr = inet_addr("127.0.0.1");

	if(connect(sockfd, (struct sockaddr *)&server, sizeof(server)) < 0){
		perror("Connect error");
		return -1;
	}

	bytes = read(sockfd, buf, 100);
	if(bytes < 0){
		perror("Error, read failed.");
		return -1;
	}else if(bytes == 0){
		printf("Server close connection.\n");
		return 0;
	}

	printf("Read bytes: %d\n", bytes);
	printf("Time: %s", buf);

	close(sockfd);

	return 0;
}
