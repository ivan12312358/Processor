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
	
	Stack stack(cmd_pnt);

	int registers[4] = {};
	int ram[r_size] = {};

	int tmp = 0, mode = 0;

	for(int start = 0, end = stack.get_cap(); start < end; start++){
		stack.dump();
		#define COMMANDS(name, num, cmds) if(*(char*)(cmd + start) == num){			\
											mode = *((char*)(cmd + start) + 1);		\
											cmds 									\
										  } else 								
		#include "../Libraries/commands.h"
		{
			printf("Unexpected case\n");
		}
		stack.dump();
	}

	return 0;
}