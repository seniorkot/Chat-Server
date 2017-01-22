#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <pthread.h>
#include <netinet/in.h>

#include "client_t.h"

void send_msg(char*, int, client_t**);
void send_msg_all(char*, client_t**);
void send_private_msg(char*, int, client_t**);