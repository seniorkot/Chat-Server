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
#include "message.h"

void* session(void*);
void add_user(client_t*);
void delete_user(int);
size_t get_client_count(void);