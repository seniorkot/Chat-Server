#define h_addr h_addr_list[0] /* for backward compatibility */

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <strings.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h> 
#include <malloc.h>
#include <pthread.h>

#define BUFFER_SIZE 512

typedef struct {
	int serverfd;				/* Server file discriptor */
} server_t;

void* session(void*);

int main(int argc, char *argv[])
{
	int sockfd, port;
    struct sockaddr_in serv_addr;
    struct hostent *server;
	char buff[BUFFER_SIZE];
	pthread_t thread; /* Thread for output */
	server_t* serverfd;
	
	if (argc != 3) {
       fprintf(stderr,"usage %s hostname port\n", argv[0]);
       return 0;
    }
	
	port = atoi(argv[2]);
	sockfd = socket(AF_INET, SOCK_STREAM, 0);
	if (sockfd < 0)
	{
		perror("ERROR opening socket.");
		return 1;
	}
	server = gethostbyname(argv[1]);
	if (server == NULL)
	{
		fprintf(stderr,"ERROR, no such host: %s\n", argv[1]);
		return 1;
	}
	bzero((char *) &serv_addr, sizeof(serv_addr));
	serv_addr.sin_family = AF_INET;
	bcopy((char *)server->h_addr, (char *)&serv_addr.sin_addr.s_addr, server->h_length);
	serv_addr.sin_port = htons(port);
	if(connect(sockfd,(struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0)
	{
		perror("ERROR connecting");
		return 1;
	}
	serverfd = malloc(sizeof(server_t));
	serverfd->serverfd = sockfd;
	if(pthread_create(&thread, NULL, &session, (void*) serverfd))
	{
		close(sockfd);
	}
	bzero(buff, BUFFER_SIZE);
	while((read(sockfd, buff, BUFFER_SIZE))>0)
	{
		printf("%s", buff);
		bzero(buff, BUFFER_SIZE);
	}
	close(sockfd);
	return 0;
}

void* session(void *args)
{
	char buff[BUFFER_SIZE];
	server_t* tmp;
	int sockfd;
	tmp = (server_t*) args;
	sockfd = tmp->serverfd;
	bzero(buff, BUFFER_SIZE);
	while(strcmp(buff,"\\quit"))
	{
		fgets(buff, sizeof(buff), stdin);
		write(sockfd, buff, BUFFER_SIZE);
		bzero(buff, BUFFER_SIZE);
	}
	pthread_detach(pthread_self());
	return NULL;
}