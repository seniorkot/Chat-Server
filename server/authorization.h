#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>

#include "client_t.h"

int sign_in(const char*, const char*, client_t* const, client_t**);
int sign_up(const char*, const char*, client_t* const);
int get_user_id(const char*, client_t**);