#include <stdlib.h>

int main(){

	system("gcc ./Assembler/asm.cpp -o asm");
	system("./asm ./Projects/Square_equation.asm");
	system("gcc ./Processor/proc.cpp -o proc -lm");
	system("./proc bin.out");
	system("gcc ./~Assembler/dasm.cpp -o dasm");
	system("./dasm bin.out");
	
	return 0;
}