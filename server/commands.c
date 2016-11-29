#include "commands.h"


void cmd_quit(client_t* client, client_t** clients)
{
	char buff_out[BUFFER_SIZE];
	sprintf(buff_out, "[SERVER_MSG]: %s has left the server.\n", client->name);
	send_msg(buff_out, client->uid, clients);
}

void cmd_name(client_t* client, client_t** clients)
{
	char buff_out[BUFFER_SIZE];
	char *param;
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

void cmd_help(client_t* client, client_t** clients)
{
	char buff_out[BUFFER_SIZE];
	strcat(buff_out, "[SERVER_MSG]: \\name \tChange nickname;\n");
	strcat(buff_out, "[SERVER_MSG]: \\help \tShow this help;\n");
	strcat(buff_out, "[SERVER_MSG]: \\quit \tLeave chat;\n");
	send_private_msg(buff_out, client->uid, clients);
}

void cmd_unknown(client_t* client, client_t** clients)
{
	char buff_out[BUFFER_SIZE];
	sprintf(buff_out, "[SERVER_MSG]: %s is unknown command! Type \\help for help.\n", command);
	send_private_msg(buff_out, client->uid, clients);
}