#include <commands.h>
#include <authorization.h>

int cmd_exec(char* command, client_t* client, client_t** clients)
{
	if(!strcmp(command,"\\q") || !strcmp(command,"\\quit"))
	{
		cmd_quit(client, clients);
		return 1;
	}
	else if(!strcmp(command,"\\pm"))
	{
		cmd_pm(client, clients);
	}
	else if(!strcmp(command,"\\online"))
	{
		cmd_online(client, clients);
	}
	else if(!strcmp(command,"\\name"))
	{
		cmd_name(client, clients);
	}
	else if(!strcmp(command,"\\passwd"))
	{
		cmd_passwd(client, clients);
	}
	else if(!strcmp(command,"\\h") || !strcmp(command,"\\help"))
	{
		cmd_help(client, clients);
	}
	else
	{
		cmd_unknown(client, clients, command);
	}
	return 0;
}

void cmd_login(client_t* client, client_t** clients)
{
	char* login;
	char* passwd;
	int result;
	login = strtok(NULL, " \0");
	passwd = strtok(NULL, " \0");
	if (login && passwd){
		if(!(result = sign_in(login, passwd, client, clients))){
			char buff_out[BUFFER_SIZE];
			sprintf(buff_out, "[SERVER_MSG]: %s has logged in.\n", client->name);
			send_msg(buff_out, client->uid, clients);
		}
		else if(result==1){
			send_private_msg("[SERVER_MSG]: Incorrect password. Please, try again.\n", client->uid, clients);
		}
		else if(result==2){
			send_private_msg("[SERVER_MSG]: User is already online.\n", client->uid, clients);
		}
		else{
			send_private_msg("[SERVER_MSG]: User not found. Please, try again.\n", client->uid, clients);
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
			send_private_msg("[SERVER_MSG]: User already exists. Please, try again!\n", client->uid, clients);
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

void cmd_pm(client_t* client, client_t** clients)
{
	char buff_out[BUFFER_SIZE];
	char* buff;
	char* name;
	int uid;
	name = strtok(NULL, " \0");
	if (!name || !(buff=strtok(NULL, "\0"))){
		send_private_msg("[SERVER_MSG]: Use \\pm [user] [msg]\n", client->uid, clients);
	}
	else{
		if((uid = get_user_id(name, clients))){
			sprintf(buff_out, "[%s](pm): ", client->name);
			strcat(buff_out, buff);
			strcat(buff_out, "\n");
			send_private_msg(buff_out, uid, clients);
		}
		else{
			sprintf(buff_out, "[SERVER_MSG]: %s is offline.\n", name);
			send_private_msg(buff_out, client->uid, clients);
		}
	}
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
		sprintf(filepath, ".profile/%s", old_name);
		sprintf(newfilepath, ".profile/%s", param);
		if(!rename(filepath, newfilepath)){
			chmod(newfilepath, 0700);
			strcpy(client->name, param);
			sprintf(buff_out, "[SERVER_MSG]: %s is now %s.\n", old_name, client->name);
			send_msg_all(buff_out, clients);
		}
		else{
			send_private_msg("[SERVER_MSG]: Can't rename.\n", client->uid, clients);
		}
	}else{
		send_private_msg("[SERVER_MSG]: Incorrect name. Please, try again.\n", client->uid, clients);
	}
}

void cmd_passwd(client_t* client, client_t** clients)
{
	FILE* file;
	char buff[BUFFER_SIZE];
	char *old_passwd;
	char *new_passwd;
	old_passwd = strtok(NULL, " \0");
	new_passwd = strtok(NULL, " \0");
	if(old_passwd && new_passwd){
		char filepath[64];
		sprintf(filepath, ".profile/%s/password", client->name);
		file = fopen(filepath, "rb");
		if (file==NULL){
			send_private_msg("[SERVER_MSG]: Can't change password.\n", client->uid, clients);
		}
		else{
			fgets(buff, BUFFER_SIZE-1, file);
			if(!strcmp(buff,old_passwd)){
				fclose(file);
				file = fopen(filepath, "wb");
				fputs(new_passwd, file);
				send_private_msg("[SERVER_MSG]: Password changed.\n", client->uid, clients);
			}
			else{
				send_private_msg("[SERVER_MSG]: Incorrect password. Please, try again.\n", client->uid, clients);
			}
			fclose(file);
		}
	}else{
		send_private_msg("[SERVER_MSG]: Use \\passwd [old] [new]\n", client->uid, clients);
	}
}

void cmd_help(client_t* client, client_t** clients)
{
	char buff_out[BUFFER_SIZE];
	memset(buff_out, 0, BUFFER_SIZE);
	strcat(buff_out, "---------Available commands:---------\n");
	strcat(buff_out, "\\online \tPrint users online;\n");
	strcat(buff_out, "\\pm \tSend private message;\n");
	strcat(buff_out, "\\name \tChange nickname;\n");
	strcat(buff_out, "\\passwd \tChange password;\n");
	strcat(buff_out, "\\h(elp) \tPrint this help;\n");
	strcat(buff_out, "\\q(uit) \tLeave chat;\n");
	strcat(buff_out, "-------------------------------------\n");
	send_private_msg(buff_out, client->uid, clients);
}

void cmd_online(client_t* client, client_t** clients)
{
	char buff_out[BUFFER_SIZE];
	size_t i;
	sprintf(buff_out, "------Users online:------\n");
	for(i=0;i<MAX_CLIENTS;i++)
	{
		if(clients[i] != NULL)
		{
			strcat(buff_out, clients[i]->name);
			strcat(buff_out, "\n");
		}
	}
	strcat(buff_out, "-------------------------\n");
	send_private_msg(buff_out, client->uid, clients);
}

void cmd_unknown(client_t* client, client_t** clients, char* command)
{
	char buff_out[BUFFER_SIZE];
	sprintf(buff_out, "[SERVER_MSG]: %s is unknown command. Type \\help for help.\n", command);
	send_private_msg(buff_out, client->uid, clients);
}