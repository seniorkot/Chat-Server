#include "session.h"
#include "commands.h"
#include "message.h"

static size_t client_count = 0; /* Number of clients */

/* User session */
void* session(void *args) 
{
    char buff_in[BUFFER_SIZE];
	char buff_out[BUFFER_SIZE];
	client_t* client;
	client_t** clients;
	session_args_t* sargs = (session_args_t*) args;
	client = sargs->client;
	clients = sargs->clients;
	
	memset(buff_in, 0, BUFFER_SIZE);
	memset(buff_out, 0, BUFFER_SIZE);
	/* Active when client is connected */
	while((read(client->clientfd,buff_in,BUFFER_SIZE-1))>0)
	{
		buff_in[strlen(buff_in)-1] = '\0';
		/* If string is empty */
		if(!strlen(buff_in))
		{
			continue;
		}
		else if(!client->authorized){
			char* command;
			command = strtok(buff_in, " \0");
			if(!strcmp(command,"\\login"))
			{
				cmd_login(client, clients);
			}
			else if(!strcmp(command,"\\register"))
			{
				cmd_register(client, clients);
			}
			else{
				send_private_msg("[SERVER_MSG]: You are not authorized! (type \\login or \\register)\n", client->uid, clients);
			}
		}
		/* If command was typed */
		else if(buff_in[0]=='\\')
		{
			char* command;
			command = strtok(buff_in, " \0");
			if(cmd_exec(command, client, clients)){
				break;
			}
		}
		/* Print message to others */
		else
		{
			sprintf(buff_out, "[%s]: %s\n", client->name, buff_in);
			send_msg(buff_out, client->uid, clients);
		}
	memset(buff_in, 0, BUFFER_SIZE);
	memset(buff_out, 0, BUFFER_SIZE);
	}
	
	/* Close connection and delete user */
	close(client->clientfd);
	delete_user(client->uid, clients);
	free(client);
	pthread_detach(pthread_self());
    return NULL;
}

/* Add client to UserList */
void add_user(client_t* client, client_t** clients)
{
	size_t i;
	for (i=0; i<MAX_CLIENTS; i++)
	{
		if(clients[i]==NULL)
		{
			clients[i]=client;
			printf("[SYSTEM_MSG]: %s (%s) has joined the server.\n", client->name, inet_ntoa(client->addr.sin_addr));
			client_count++;
			break;
		}
	}
}

/* Delete client from UserList */
void delete_user(int uid, client_t** clients)
{
	size_t i;
	for (i=0; i<MAX_CLIENTS; i++)
	{
		if(clients[i] != NULL && clients[i]->uid == uid)
		{
			printf("[SYSTEM_MSG]: %s (%s) has left the server.\n", clients[i]->name, inet_ntoa(clients[i]->addr.sin_addr));
			clients[i]=NULL;
			client_count--;
			break;
		}
	}
}

size_t get_client_count(void)
{
	return client_count;
}