#include "../Libraries/asm.h"

int main(int argc, char* argv[]){

	int str_cnt = 0, sym_cnt = 0;

	char* symbols = read(argv + 1, &str_cnt, &sym_cnt);

	char **string = (char**)calloc(str_cnt, sizeof(char*));

	split(string, symbols, sym_cnt);

/*
	for(int i = 0; i < str_cnt; i++){
		printf("%d\t%s\n", i + 1, string[i]);
	}

	printf("\n\n\n");
*/
	write(string, str_cnt);

	free(symbols);
	free(string);

	return 0;
}

char* read(char** f_asm, int* str_cnt, int* sym_cnt){

	FILE* asm_file = fopen(*f_asm, "r+");

	assert(asm_file);

	fseek(asm_file, 0, SEEK_END);
	*sym_cnt = ftell(asm_file);
	rewind(asm_file);
	
	char *symbols = (char*)calloc(*sym_cnt, sizeof(char));

	fread(symbols, sizeof(char), *sym_cnt, asm_file);

	for(int i = 0; i < *sym_cnt; i++){
		if(symbols[i] == ' ' ||  symbols[i] == '\n'){
			symbols[i] = '\0';
			(*str_cnt)++;
		}
	}

	fclose(asm_file);

	return symbols;
}


void split(char** string, char* symbols, int sym_cnt){

	int len_str = 0, j = 0;

	for(int i = 0; i < sym_cnt; i++){
		if(symbols[i] == '\0'){
			string[j++] = symbols + len_str;
			len_str = i + 1;
		}
	}
}


void write(char** string, int str_cnt){

	FILE* bin_file = fopen("bin.out", "w");

	labels* lbl = (labels*)calloc(str_cnt, sizeof(labels));

	int* cmds = (int*)calloc(str_cnt*2, sizeof(int));

	int cnt = 0, lbl_inx = 0, lbl_cnt = 0;

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

	for(int i = 0; i < str_cnt; i++){
		#define COMMANDS(name, num, cmd) if(!strcmp(string[i], #name)){    										\
										 	*((char*)(cmds + cnt)) = num;										\
											cnt++;																\
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

/*
	for(int j = 0; j < cnt; j++){
			printf("%d\n", cmds[j]);
	}
*/
	
	fwrite(cmds, sizeof(int), cnt, bin_file);

	fclose(bin_file);
	free(cmds);
}