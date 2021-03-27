#include <stdio.h>
#include <stdlib.h>
#include "../Stack/stack.cpp"
#include <math.h>

const int OPEN_ERR = 1;
const int CMD_ERROR = 2;
#define r_size 8192
#define v_size 2048

int* file(char** bin_file, int* cmd_pnt);
int proc(int* cmd, int cmd_pnt);

int main(int argc, char* argv[]){

	int cmd_pnt = 0;

	int* cmd = file(argv + 1, &cmd_pnt);

	proc(cmd, cmd_pnt);

	free(cmd);

	return 0;
}

int* file(char** bin_file, int* cmd_pnt){

	FILE* f = fopen(*(bin_file), "rb");

	fseek(f, 0, SEEK_END);
	*cmd_pnt = ftell(f)/sizeof(int);
	rewind(f);

	int* cmd = (int*)calloc(*cmd_pnt, sizeof(int));

	fread(cmd, sizeof(int), *cmd_pnt, f);

	return cmd;
}

int proc(int* cmd, int cmd_pnt){
	
	Stack stack;
	constructor(&stack, cmd_pnt);

	int registers[4] = {};
	int ram[r_size] = {};

	int tmp = 0, mode = 0;

	for(int i = 0; i < stack.capacity; i++){
		stack_dump(&stack);
		#define COMMANDS(name, num, cmds) if(*(char*)(cmd + i) == num){			\
											mode = *((char*)(cmd + i) + 1);		\
											cmds 								\
										  } else 								
		#include "../Libraries/commands.h"
		{
			printf("Unexpected case\n");
		}
		stack_dump(&stack);
	}


	destructor(&stack);

	return 0;
}