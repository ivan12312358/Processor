COMMANDS (end,   0, {
						break;
					})

COMMANDS (push,  1, {
						if(mode == 0){
							push(&stack, cmd[++i]);
						} else if(mode == -1){
							push(&stack, registers[cmd[++i]]);	
						} else if(mode == -2){
							push(&stack, ram[cmd[++i]]);
						} else if(mode == -3){
							push(&stack, ram[registers[cmd[++i]]]);
						} else if(mode == -4){
							push(&stack, ram[registers[cmd[i + 1]] + cmd[i + 2]]);
							i += 2;
						}
					})

COMMANDS (pop,   2, {
						if(mode == 0){
							pop(&stack);
						} else if(mode == -1){
							registers[cmd[++i]] = pop(&stack);
						} else if(mode == -2){
							ram[cmd[++i]] = pop(&stack);
						} else if(mode == -3){
							ram[registers[cmd[++i]]] = pop(&stack);
						} else if(mode == -4){
							ram[registers[cmd[i + 1]] + cmd[i + 2]] = pop(&stack);
							i += 2;
						}
					})

COMMANDS (jmp,   3, {
						i = cmd[i + 1] - 1;
					})

COMMANDS (jb,    4, {
						if(pop(&stack) < pop(&stack))
							i = cmd[i + 1] - 1;
						else i++;
					})

COMMANDS (jbe, 	 5, {
						if(pop(&stack) <= pop(&stack))
							i = cmd[i + 1] - 1;
						else i++;
					})

COMMANDS (ja, 	 6, {				
						if(pop(&stack) > pop(&stack))
							i = cmd[i + 1] - 1;
						else i++;
					})

COMMANDS (jae,   7, {
						if(pop(&stack) >= pop(&stack))
							i = cmd[i + 1] - 1;
						else i++;
					})

COMMANDS (je,    8, {
						if(pop(&stack) == pop(&stack))
							i = cmd[i + 1] - 1;				
						else i++;
					})

COMMANDS (jne,   9, {
						if(pop(&stack) != pop(&stack))
							i = cmd[i + 1] - 1;
						else i++;
						})

COMMANDS (call,  10,{
						push(&stack, i + 2);
						i = cmd[i + 1] - 1;
					})


COMMANDS (add,   11,{
						push(&stack, pop(&stack) + pop(&stack));
					})

COMMANDS (sub,   12,{
						push(&stack, pop(&stack) - pop(&stack));
					})

COMMANDS (div,   13,{
						push(&stack, pop(&stack) / pop(&stack));
					})

COMMANDS (mul, 	 14,{
						push(&stack, pop(&stack) * pop(&stack));
					})

COMMANDS (fsqrt, 15,{
						push(&stack, sqrt(pop(&stack)));
					})

COMMANDS (in,    16,{
						scanf("%d", &tmp);
						push(&stack, tmp);
					})


COMMANDS (ret,   17,{
						i  = pop(&stack) - 1;
					})

COMMANDS (out,   18,{
						printf("%d\n", pop(&stack));
					})

COMMANDS (print, 19,{
						for(int i = r_size - v_size; i < r_size; i++){
							printf("%c", ram[i]);
						}
					  })