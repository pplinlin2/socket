#include "socket.h"
#define MAX_LISTEN_QUEUE 5

/*
socket -> bind -> listen -> accept -> read/write -> close
*/
int main()
{
	int listenfd, sockfd;
	struct sockaddr_in server, client;
	socklen_t len;
	time_t timep;
	char buf[100];
	int ret, opt = 1;

	listenfd = socket(AF_INET, SOCK_STREAM, 0);
	if(listenfd < 0){
		perror("Create socket fail.");
		return -1;
	}

	if((ret = setsockopt(listenfd, SOL_SOCKET, SO_REUSEADDR, &opt, sizeof(opt))) < 0){
		perror("Set socket reuse fail.");
		return -1;
	}

	bzero(&server, sizeof(server));
	server.sin_family = AF_INET;
	server.sin_port   = htons(8888);
	server.sin_addr.s_addr = htonl(INADDR_ANY);

	len = sizeof(struct sockaddr);
	if(bind(listenfd, (struct sockaddr *)&server, len) < 0){
		perror("Bind error.");
		return -1;
	}

	listen(listenfd, MAX_LISTEN_QUEUE);

	while(1){
		sockfd = accept(listenfd, (struct sockaddr *)&client, &len);
		if(sockfd < 0){
			perror("Accept error.\n");
			return -1;
		}

		timep = time(NULL);
		snprintf(buf, sizeof(buf), "%s", ctime(&timep));

		write(sockfd, buf, strlen(buf));
		printf("Bytes: %d\n", strlen(buf));
		printf("sockfd: %d\n", sockfd);

		close(sockfd);
	}

	return 0;
}
