#pragma once
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_CLIENTS 50 /* Change if necessary */
#define BUFFER_SIZE 512 /* Change if necessary */

/* Client's settings on server */
typedef struct {
	struct sockaddr_in addr;	/* Client's remote address */
	int clientfd;				/* Client's connection fd */
	int uid;					/* Client's User ID */
	char name[24];				/* Client's nickname */
	int privilege;				/* -1 - banned; 0 - guest 
									1 - user; 2 - admin */
} client_t;