#include "../Libraries/dasm.h"

int main(int argc, char* argv[]){

	int* cmd = NULL;

	int cmd_size = read(&cmd, argv + 1);

	dasm(cmd, cmd_size);

	free(cmd);

	return 0;
}

///This function reads from file///

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

///This function makes disassembling///

void dasm(int* cmd, int cmd_size){

	FILE* asm_f = fopen("dcmd.asm", "w");

	int mode = 0, waitf_arg = 0, cmd_cnt = 0;

	const char* registers[4] = {"rax", "rbx", "rcx", "rdx"};

	fprintf(asm_f, "Addr\tNumber cmd\t  Code\t\t  Text\n");

	for(int i = 0; i < cmd_size; i++){

		mode = *((char*)(cmd + i) + 1);

		#define COMMANDS(name, num, cmmds)  if(cmd[i] == num && waitf_arg == 0){			\
												fprintf(asm_f, "0x%.2x\t\t%.2d\t\t",		\
																	i, ++cmd_cnt);			\
																							\
												fprintf(asm_f, "%.2d ", num);				\
																							\
												if(cmd[i] > 0 && cmd[i] < 11){				\
													fprintf(asm_f, "%d\t\t", cmd[i + 1]);	\
													fprintf(asm_f, #name"\t");				\
													waitf_arg = 1;							\
												} else {									\
																							\
													fprintf(asm_f, "\t\t\t"#name"\n");		\
												}											\
																							\
											} else 
		#include "../Libraries/commands.h"
		#undef COMMANDS
		if(waitf_arg == 0){

			fprintf(asm_f, "0x%.2x\t\t%.2d\t\t", i, ++cmd_cnt);

			if(mode != -4)
				fprintf(asm_f, "%.2d%.2d %.2d \t", *((char*)(cmd + i)), -mode, cmd[i + 1]);

			if(mode == -1){
				fprintf(asm_f, "%s \t%s\n", print_mode(*((char*)(cmd + i))), registers[cmd[i + 1]]);
			} else if(mode == -2){
				fprintf(asm_f, "%s\t[%d]\n", print_mode(*((char*)(cmd + i))), cmd[i + 1]);
			} else if(mode == -3){
				fprintf(asm_f, "%s\t[%s]\n", print_mode(*((char*)(cmd + i))), registers[cmd[i + 1]]);
			} else if(mode == -4){
				fprintf(asm_f, "%.2d%.2d %.2d %.2d\t", *((char*)(cmd + i)), -mode, cmd[i + 1], cmd[i + 2]);
				fprintf(asm_f, "%s\t[%s + %d]\n", print_mode(*((char*)(cmd + i))), registers[cmd[i + 1]], cmd[i + 2]);
				i++;
			}
			i++;

		} else if(waitf_arg == 1){
			waitf_arg = 0;

			if(cmd[i - 1] < 10 && cmd[i - 1] > 1)
				fprintf(asm_f, "\t%d\n", cmd[i]);
			else
				fprintf(asm_f, "%d\n", cmd[i]);
		}
	}

	fclose(asm_f);
}

const char* print_mode(int mode){

	if(mode == 1){
		return "push";
	} else if(mode == 2){
		return "pop";
	}

	return "Wrong symbol";
}
