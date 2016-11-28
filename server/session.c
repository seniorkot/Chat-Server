#include "session.h"

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
	
	sprintf(buff_out, "[SERVER_MSG]: %s has joined the server.\n", client->name);
	send_msg(buff_out, client->uid, clients);
	
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
		/* If command was typed */
		else if(buff_in[0]=='\\')
		{
			char* command, *param;
			command = strtok(buff_in, " \0");
			if(!strcmp(command,"\\quit"))
			{
				sprintf(buff_out, "[SERVER_MSG]: %s has left the server.\n", client->name);
				send_msg(buff_out, client->uid, clients);
				break;
			}
			else if(!strcmp(command,"\\name"))
			{
				param = strtok(NULL, " \0");
				if(param){
					char old_name[24];
					strcpy(old_name, client->name);
					strcpy(client->name, param);
					sprintf(buff_out, "[SERVER_MSG]: %s is now %s.\n", old_name, client->name);
					send_msg_all(buff_out, clients);
				}else{
					send_private_msg("[SERVER_MSG]: Incorrect name! Please, try again!\n", client->uid, clients);
				}
			}
			else if(!strcmp(command,"\\help"))
			{
				strcat(buff_out, "[SERVER_MSG]: \\name \tChange nickname;\n");
				strcat(buff_out, "[SERVER_MSG]: \\help \tShow this help;\n");
				strcat(buff_out, "[SERVER_MSG]: \\quit \tLeave chat;\n");
				send_private_msg(buff_out, client->uid, clients);
			}
			else
			{
				sprintf(buff_out, "[SERVER_MSG]: %s is unknown command! Type \\help for help.\n", command);
				send_private_msg(buff_out, client->uid, clients);
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
	
	/* Close connection and delete user*/
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