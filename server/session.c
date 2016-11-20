#include "session.h"

size_t client_count = 0; /* Number of clients */

/* User session */
void* session(void *args) 
{
    char buff_in[BUFFER_SIZE];
	char buff_out[BUFFER_SIZE];
	client_t* client = (client_t*) args;
	
	sprintf(buff_out, "[SERVER_MSG]: %s has joined the server.\n", client->name);
	send_msg(buff_out, client->uid);
	
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
				send_msg(buff_out, client->uid);
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
					send_msg_all(buff_out);
				}else{
					send_private_msg("[SERVER_MSG]: Incorrect name! Please, try again!\n", client->uid);
				}
			}
			else if(!strcmp(command,"\\help"))
			{
				strcat(buff_out, "[SERVER_MSG]: \\name \tChange nickname;\n");
				strcat(buff_out, "[SERVER_MSG]: \\help \tShow this help;\n");
				strcat(buff_out, "[SERVER_MSG]: \\quit \tLeave chat;\n");
				send_private_msg(buff_out, client->uid);
			}
			else
			{
				sprintf(buff_out, "[SERVER_MSG]: %s is unknown command! Type \\help for help.\n", command);
				send_private_msg(buff_out, client->uid);
			}
		}
		/* Print message to others */
		else
		{
			sprintf(buff_out, "[%s]: %s\n", client->name, buff_in);
			send_msg(buff_out, client->uid);
		}
	memset(buff_in, 0, BUFFER_SIZE);
	memset(buff_out, 0, BUFFER_SIZE);
	}
	
	/* Close connection and delete user*/
	close(client->clientfd);
	delete_user(client->uid);
	free(client);
	pthread_detach(pthread_self());
    return NULL;
}

/* Add client to UserList */
void add_user(client_t* client)
{
	size_t i;
	for (i=0; i<MAX_CLIENTS; i++)
	{
		if(clients[i]==NULL)
		{
			clients[i]=client;
			break;
		}
	}
	client_count++;
}

/* Delete client from UserList */
void delete_user(int uid)
{
	size_t i;
	for (i=0; i<MAX_CLIENTS; i++)
	{
		if(clients[i]->uid == uid)
		{
			clients[i]=NULL;
			break;
		}
	}
	client_count--;
}

size_t get_clients_num()
{
	return client_count;
}