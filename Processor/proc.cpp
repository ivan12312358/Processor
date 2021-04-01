#include "../Libraries/proc.h"
#include "../Libraries/stack.h"


int main(int argc, char* argv[]){

	int cmd_pnt = 0;

	int* cmd = file(argv + 1, &cmd_pnt);

	proc(cmd, cmd_pnt);

	free(cmd);

	return 0;
}

///This function reads from file///

int* file(char** bin_file, int* cmd_pnt){

	FILE* f = fopen(*(bin_file), "rb");

	assert(f);

	fseek(f, 0, SEEK_END);
	*cmd_pnt = ftell(f)/sizeof(int);
	rewind(f);

	int* cmd = (int*)calloc(*cmd_pnt, sizeof(int));

	fread(cmd, sizeof(int), *cmd_pnt, f);

	return cmd;
}

///This function executes commands///

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