#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>
#include <sys/types.h> 
#include <sys/stat.h>

#include "client_t.h"
#include "message.h"

int cmd_exec(char*, client_t*, client_t**);
void cmd_login(client_t*, client_t**);
void cmd_register(client_t*, client_t**);
void cmd_quit(client_t*, client_t**);
void cmd_pm(client_t*, client_t**);
void cmd_name(client_t*, client_t**);
void cmd_passwd(client_t*, client_t**);
void cmd_help(client_t*, client_t**);
void cmd_online(client_t*, client_t**);
void cmd_unknown(client_t*, client_t**, char*);