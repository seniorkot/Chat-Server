#include "../includes/message.h"

/* Send message to all users except 1 user */
void send_msg(char* msg, int uid, client_t** clients)
{
	size_t i;
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(clients[i] != NULL && clients[i]->uid != uid)
		{
			write(clients[i]->clientfd, msg, strlen(msg));
		}
	}
}

/* Send message to all users */
void send_msg_all(char* msg, client_t** clients)
{
	size_t i;
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(clients[i]!=NULL)
		{
			write(clients[i]->clientfd, msg, strlen(msg));
		}
	}
}

/* Send private message */
void send_private_msg(char* msg, int uid, client_t** clients)
{
	size_t i;
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(clients[i]->uid == uid)
		{
			write(clients[i]->clientfd, msg, strlen(msg));
			break;
		}
	}
}