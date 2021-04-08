CC = gcc
CFLAGS = -g -Wall -O3

all: myproject

myproject: proc.o stack.o asm.o dasm.o
	$(CC) $(CFLAGS) proc.o stack.o -o proc -lm		
	$(CC) $(CFLAGS) asm.o Onegin.o -o asm					
	$(CC) $(CFLAGS)	dasm.o -o dasm

asm.o: ./Assembler/asm.cpp
	$(CC) $(CFLAGS) -c	./Assembler/asm.cpp
	$(CC) $(CFLAGS) -c	./Onegin/Onegin.cpp

dasm.o: ./~Assembler/dasm.cpp
	$(CC) $(CFLAGS) -c	./~Assembler/dasm.cpp

proc.o: ./Processor/proc.cpp
	$(CC) $(CFLAGS) -c ./Processor/proc.cpp

stack.o: ./Stack/stack.cpp
	$(CC) $(CFLAGS) -c ./Stack/stack.cpp

clean:
	rm -rf *.o asm dasm proc bin.out STACK_DUMP.log all