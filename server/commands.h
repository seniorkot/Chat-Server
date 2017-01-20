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

void cmd_login(client_t*, client_t**);
void cmd_register(client_t*, client_t**);
void cmd_quit(client_t*, client_t**);
void cmd_name(client_t*, client_t**);
void cmd_help(client_t*, client_t**);
void cmd_unknown(client_t*, client_t**, char*);