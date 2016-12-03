#include "authorization.h"

/*
Log in on server
Returns: 0 when succeeded
		-1 when user not found (or cannot open file)
		 1 when incorrect password was entered
*/
int sign_in(const char* login, const char* password, client_t* const client){
	FILE* file;
	char* filepath;
	strcat(filepath, ".profile/");
	strcat(filepath, login);
	strcat(filepath, "password",);
	file = fopen(filepath, "rb");
	if (file==NULL){
		return -1;
	}
	char buff[BUFFER_SIZE];
	fgets(buff, BUFFER_SIZE-1, file);
	fclose(file);
	if(!strcmp(command,password)){
		client->name = login;
		return 0
	}
	return 1;
	}
}

/*
Register on server
Returns: 0 when succeeded
		-1 when cannot open file
		 1 when profile exists
*/
int sign_up(const char* login, const char* password, client_t* const client){
	FILE* file;
	char* filepath;
	strcat(filepath, ".profile/");
	strcat(filepath, login);
	strcat(filepath, "password",);
	file = fopen(filepath, "rb");
	if (file==NULL){
		char* newfilepath;
		strcat(newfilepath, ".profile/");
		strcat(newfilepath, login);
		mkdir(newfilepath, 0700);
		strcat(newfilepath, "password",);
		file = fopen(newfilepath, "wb");
		if (file==NULL){
			return -1;
		}
		fputs(password, file);
		fclose(file);
		client->name = login;
		return 0;
	}
	fclose(file);
	return 1;
		fclose(file);
		return 1;
	}
}