#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>

#include "client_t.h"
#include "message.h"

void* session(void*);
void add_user(client_t*);
void delete_user(int);
size_t get_clients_num();