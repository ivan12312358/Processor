#include "../Libraries/asm.h"
#include "../Libraries/Onegin.h"


int main(int argc, char* argv[]){

	int str_cnt = 0, sym_cnt = 0;

	char* symbols = f_open(argv + 1, &sym_cnt, &str_cnt);

	char **string = (char**)calloc(str_cnt, sizeof(char*));

	split(string, symbols, sym_cnt);

/*
	for(int i = 0; i < str_cnt; i++){
		
		if(!strcmp(string[i], "\0")){
			continue;
		}

		printf("%d\t%s\n", i + 1, string[i]);
	}
*/

	assemble(string, str_cnt);

	free(symbols);
	free(string);

	return 0;
}


///This function sblit symbols into strings///

void split(char** string, char* symbols, int sym_cnt){

	int str_cnt = 0;
	char* endf_str = NULL;

	string[str_cnt++] = symbols;

	for(int i = 0; i < sym_cnt; ){

		endf_str = strchr(symbols + i, '\0');
		i += strlen(symbols + i) + 1;

		if(i < sym_cnt){
			string[str_cnt++] = endf_str + 1;
		} else break;
	}
}

///Reading positions of labels///

int lbl_pos(int str_cnt, labels* lbl, char** string){

	int lbl_inx = 0, lbl_cnt = 0;

	for(int i = 0; i < str_cnt; i++){
		#define COMMANDS(name, num, cmd) if(!strcmp(string[i], #name)) lbl_inx++; else
		#include "../Libraries/commands.h"
		#undef COMMANDS
		{
			if(!strcmp(string[i], "\0") || !strcmp(string[i], "+")){
				continue;
			} else if(string[i][strlen(string[i]) - 1] == ':'){

				lbl[lbl_cnt].elem[0] = ':';

				for(size_t j = 1; j < strlen(string[i]); j++){
					lbl[lbl_cnt].elem[j] = string[i][j - 1];
				}

				lbl[lbl_cnt++].inx = lbl_inx;
			
			} else {
				lbl_inx++;
			}
		}
	}

	return lbl_cnt;
}

///This function assembles commands and write it in file///

void assemble(char** string, int str_cnt){

	FILE* bin_file = fopen("bin.out", "w");

	labels* lbl = (labels*)calloc(str_cnt, sizeof(labels));

	int* cmds = (int*)calloc(str_cnt*2, sizeof(int));

	int cnt = 0, lbl_cnt = 0;

	lbl_cnt = lbl_pos(str_cnt, lbl, string);

	///Assembling///

	for(int i = 0; i < str_cnt; i++){
		#define COMMANDS(name, num, cmd) if(!strcmp(string[i], #name)){    		\
										 	*((char*)(cmds + cnt)) = num;		\
											cnt++;								\
										 } else 
		#include "../Libraries/commands.h"
		#undef COMMANDS
		{
			
			cnt--;
			if(string[i][0] == '['){
				if(string[i][1] == 'r'){
					if(i < str_cnt - 1 && string[i + 1][0] == '+'){
						*((char*)(cmds + cnt) + 1) = -4;
					} else {
						*((char*)(cmds + cnt) + 1) = -3;
	 	 			}
		 		} else {
	 	 			*((char*)(cmds + cnt) + 1) = -2;
	 	 		}
			} else if(string[i][0] == 'r' && string[i][2] == 'x'){
	 	 		*((char*)(cmds + cnt) + 1) = -1;
			}
			cnt++;
			
			if(string[i][strlen(string[i]) - 1] == ':' || string[i][0] == '+'){
				continue;
			} else if(!strcmp(string[i], "\0")){
				continue;
			} else if(string[i][0] == ':'){				
				for(int j = 0; j < lbl_cnt; j++){
					if(!strcmp(string[i], lbl[j].elem)){
						cmds[cnt++] = lbl[j].inx;
					}
				}

			} else 

			#define REGISTERS(reg, inx) if(!strncmp(string[i] + 1, #reg, sizeof(#reg) - 1)		\
																|| !strcmp(string[i], #reg)){	\
											cmds[cnt++] = inx;									\
										} else													\
										
			REGISTERS (rax, 0)
			REGISTERS (rbx, 1)
			REGISTERS (rcx, 2)
			REGISTERS (rdx, 3)
			#undef REGISTERS

			if(string[i][0] == '['){				
				cmds[cnt++] = atoi(string[i] + 1);
			} else if(strlen(string[i]) > 1){
				cmds[cnt++] = atoi(string[i]);
			} else if(string[i][0] < '0' || string[i][0] > '9'){
				cmds[cnt++] = string[i][0];
			} else {
				cmds[cnt++] = string[i][0] - '0';						
			}
		}
	}
	
	fwrite(cmds, sizeof(int), cnt, bin_file);

	fclose(bin_file);
	free(cmds);
}