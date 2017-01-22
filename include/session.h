#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <pthread.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "client_t.h"

void* session(void*);
void add_user(client_t*, client_t**);
void delete_user(int, client_t**);
size_t get_client_count(void);

/* Arguments for session */
typedef struct session_args{
	client_t* client;
	client_t** clients;
} session_args_t;