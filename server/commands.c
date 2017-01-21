#include "commands.h"
#include "authorization.h"

void cmd_login(client_t* client, client_t** clients)
{
	char* login;
	char* passwd;
	int result;
	login = strtok(NULL, " \0");
	passwd = strtok(NULL, " \0");
	if (login && passwd){
		if(!(result = sign_in(login, passwd, client))){
			char buff_out[BUFFER_SIZE];
			sprintf(buff_out, "[SERVER_MSG]: %s has logged in.\n", client->name);
			send_msg(buff_out, client->uid, clients);
		}
		else if(result==1){
			send_private_msg("[SERVER_MSG]: Incorrect password! Please, try again!\n", client->uid, clients);
		}
		else{
			send_private_msg("[SERVER_MSG]: User not found! Please, try again!\n", client->uid, clients);
		}
	}
	else{
		send_private_msg("[SERVER_MSG]: Use \\login [login] [passwd]\n", client->uid, clients);
	}
}

void cmd_register(client_t* client, client_t** clients)
{
	char* login;
	char* passwd;
	int result;
	login = strtok(NULL, " \0");
	passwd = strtok(NULL, " \0");
	if (login && passwd){
		if(!(result = sign_up(login, passwd, client))){
			char buff_out[BUFFER_SIZE];
			sprintf(buff_out, "[SERVER_MSG]: %s has registered.\n", client->name);
			send_msg(buff_out, client->uid, clients);
		}
		else if(result==1){
			send_private_msg("[SERVER_MSG]: User already exists! Please, try again!\n", client->uid, clients);
		}
	}
	else{
		send_private_msg("[SERVER_MSG]: Use \\register [login] [passwd]\n", client->uid, clients);
	}
}

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
		char filepath[64];
		char newfilepath[64];
		strcpy(old_name, client->name);
		memset(filepath, 0, 64);
		memset(newfilepath, 0, 64);
		strcat(filepath, ".profile/");
		strcat(filepath, old_name);
		strcat(newfilepath, ".profile/");
		strcat(newfilepath, param);
		if(!rename(filepath, newfilepath)){
			strcpy(client->name, param);
			sprintf(buff_out, "[SERVER_MSG]: %s is now %s.\n", old_name, client->name);
			send_msg_all(buff_out, clients);
		}
		else{
			send_private_msg("[SERVER_MSG]: Can't rename!\n", client->uid, clients);
		}
	}else{
		send_private_msg("[SERVER_MSG]: Incorrect name! Please, try again!\n", client->uid, clients);
	}
}

void cmd_help(client_t* client, client_t** clients)
{
	char buff_out[BUFFER_SIZE];
	memset(buff_out, 0, BUFFER_SIZE);
	strcat(buff_out, "[SERVER_MSG]: \\name \tChange nickname;\n");
	strcat(buff_out, "[SERVER_MSG]: \\help \tShow this help;\n");
	strcat(buff_out, "[SERVER_MSG]: \\quit \tLeave chat;\n");
	send_private_msg(buff_out, client->uid, clients);
}

void cmd_unknown(client_t* client, client_t** clients, char* command)
{
	char buff_out[BUFFER_SIZE];
	sprintf(buff_out, "[SERVER_MSG]: %s is unknown command! Type \\help for help.\n", command);
	send_private_msg(buff_out, client->uid, clients);
}