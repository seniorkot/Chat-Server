#include "authorization.h"

/*
Log in on server
Returns: 0 when succeeded
		-1 when user not found (or cannot open file)
		 1 when incorrect password was entered
		 2 when user already online
*/
int sign_in(const char* login, const char* password, client_t* const client, client_t** clients){
	FILE* file;
	char filepath[BUFFER_SIZE];
	char buff[BUFFER_SIZE];
	memset(filepath, 0, BUFFER_SIZE);
	memset(buff, 0, BUFFER_SIZE);
	strcat(filepath, ".profile/");
	strcat(filepath, login);
	strcat(filepath, "/password");
	file = fopen(filepath, "rb");
	if (file==NULL){
		return -1;
	}
	fgets(buff, BUFFER_SIZE-1, file);
	fclose(file);
	if(!strcmp(buff,password)){
		if(get_user_id(login, clients)){
			return 2;
		}
		strcpy(client->name, login);
		client->authorized=1;
		return 0;
	}
	return 1;
}

/*
Register on server
Returns: 0 when succeeded
		-1 when cannot open file
		 1 when profile exists
*/
int sign_up(const char* login, const char* password, client_t* const client){
	FILE* file;
	char filepath[BUFFER_SIZE];
	memset(filepath, 0, BUFFER_SIZE);
	strcat(filepath, ".profile/");
	strcat(filepath, login);
	strcat(filepath, "/password");
	file = fopen(filepath, "rb");
	if (file==NULL){
		char newfilepath[BUFFER_SIZE];
		memset(newfilepath, 0, BUFFER_SIZE);
		strcat(newfilepath, ".profile/");
		strcat(newfilepath, login);
		mkdir(newfilepath, 0700);
		strcat(newfilepath, "/password");
		file = fopen(newfilepath, "wb");
		if (file==NULL){
			return -1;
		}
		fputs(password, file);
		fclose(file);
		strcpy(client->name, login);
		client->authorized=1;
		return 0;
	}
	fclose(file);
	return 1;
}

/*
Returns: 0 if user offline
		id if user online
*/
int get_user_id(const char* name, client_t** clients){
	size_t i;
	for (i=0; i<MAX_CLIENTS; i++){
		if(clients[i] != NULL && !strcmp(name, clients[i]->name)){
			return clients[i]->uid;
		}
	}
	return 0;
}