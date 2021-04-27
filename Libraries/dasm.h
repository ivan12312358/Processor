#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int read(int** cmd, char** bin_file);

void dasm(int* cmd, int cmd_size);

const char* print_mode(int mode);