#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

int read(int** cmd, char** bin_file);
void dasm(int* cmd, int cmd_size);


int main(int argc, char* argv[]){

	int* cmd = NULL;

	int cmd_size = read(&cmd, argv + 1);

	dasm(cmd, cmd_size);

	free(cmd);

	return 0;
}

int read(int** cmd, char** bin_file){

	FILE* bin_f = fopen(*bin_file, "rb");

	assert(bin_f);

	fseek(bin_f, 0, SEEK_END);
	int cmd_size = ftell(bin_f)/sizeof(int);
	rewind(bin_f);

	*cmd = (int*)calloc(cmd_size, sizeof(int));

	fread(*cmd, sizeof(int), cmd_size, bin_f);

/*
	for(int i = 0; i < cmd_size; i++){
		for(int j = 0; j < 4; j++){
			printf("%d", *((char*)(*cmd + i) + j));
		}
		printf("\n");
	}
*/

	return cmd_size;
}


const char* print_mode(int mode){
	if(mode == 1){
		return "push";
	} else if(mode == 2){
		return "pop";
	}

	return "Wrong symbol";
}

void dasm(int* cmd, int cmd_size){

	FILE* asm_f = fopen("dcmd.asm", "w");

	int mode = 0, waitf_arg = 0;

	const char* registers[4] = {"rax", "rbx", "rcx", "rdx"};

	for(int i = 0; i < cmd_size; i++){

		mode = *((char*)(cmd + i) + 1);

		#define COMMANDS(name, num, cmmds)	if(cmd[i] == num && waitf_arg == 0){		\
												fprintf(asm_f, #name"\n");				\
												if(cmd[i] > 0 && cmd[i] < 11){			\
													waitf_arg = 1;						\
												}										\
											} else 
		#include "../Libraries/commands.h"
		#undef COMMANDS
		if(waitf_arg == 0){
				
			if(mode == -1){
				fprintf(asm_f, "%s\n%s\n", print_mode(*((char*)(cmd + i))), registers[cmd[i + 1]]);
			} else if(mode == -2){
				fprintf(asm_f, "%s\n[%d]\n", print_mode(*((char*)(cmd + i))), cmd[i + 1]);
			} else if(mode == -3){
				fprintf(asm_f, "%s\n[%s]\n", print_mode(*((char*)(cmd + i))), registers[cmd[i + 1]]);
			} else if(mode == -4){
				fprintf(asm_f, "%s\n[%s +\n%d]\n", print_mode(*((char*)(cmd + i))), registers[cmd[i + 1]], cmd[i + 2]);
				i++;
			}
			i++;

		} else if(waitf_arg == 1){

			fprintf(asm_f, "%d\n", cmd[i]);
			waitf_arg = 0;
		}
	}

	fclose(asm_f);
}