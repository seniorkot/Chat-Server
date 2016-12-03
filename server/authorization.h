#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "client_t.h"

int sign_in(const char*, const char*, client_t* const);
int sign_up(const char*, const char*, client_t* const);