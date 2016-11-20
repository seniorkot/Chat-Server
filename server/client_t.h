#pragma once
#define MAX_CLIENTS 50 /* Change if necessary */
#define BUFFER_SIZE 512 /* Change if necessary */

/* Client's settings on server */
typedef struct {
	struct sockaddr_in addr;	/* Client's remote address */
	int clientfd;				/* Client's connection fd */
	int uid;					/* Client's User ID */
	char name[24];				/* Client's nickname */
} client_t;

client_t* clients[MAX_CLIENTS];