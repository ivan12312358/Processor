#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <string.h>

typedef struct {
	char elem[20];
	int inx = 0;
}labels;

int compare(const void* elem_1, const void* elem_2);

char* read(char** f_asm, int* str_cnt, int* sym_cnt);

void split(char** string, char* symbols, int sym_cnt);

int lbl_pos(int str_cnt, labels* lbl, char** string);

void assemble(char** string, int sym_cnt);