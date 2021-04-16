COMMANDS (end,   0, {
						break;
					})

COMMANDS (push,  1, {
						if(mode == 0){
							stack.push(cmd[++start]);
						} else if(mode == -1){
							stack.push(registers[cmd[++start]]);	
						} else if(mode == -2){
							stack.push(ram[cmd[++start]]);
						} else if(mode == -3){
							stack.push(ram[registers[cmd[++start]]]);
						} else if(mode == -4){
							stack.push(ram[registers[cmd[start + 1]] + cmd[start + 2]]);
							start += 2;
						}
					})

COMMANDS (pop,   2, {
						if(mode == 0){
							stack.pop();
						} else if(mode == -1){
							registers[cmd[++start]] = stack.pop();
						} else if(mode == -2){
							ram[cmd[++start]] = stack.pop();
						} else if(mode == -3){
							ram[registers[cmd[++start]]] = stack.pop();
						} else if(mode == -4){
							ram[registers[cmd[start + 1]] + cmd[start + 2]] = stack.pop();
							start += 2;
						}
					})

COMMANDS (jmp,   3, {
						start = cmd[start + 1] - 1;
					})

COMMANDS (jb,    4, {
						if(stack.pop() < stack.pop())
							start = cmd[start + 1] - 1;
						else start++;
					})

COMMANDS (jbe, 	 5, {
						if(stack.pop() <= stack.pop())
							start = cmd[start + 1] - 1;
						else start++;
					})

COMMANDS (ja, 	 6, {				
						if(stack.pop() > stack.pop())
							start = cmd[start + 1] - 1;
						else start++;
					})

COMMANDS (jae,   7, {
						if(stack.pop() >= stack.pop())
							start = cmd[start + 1] - 1;
						else start++;
					})

COMMANDS (je,    8, {
						if(stack.pop() == stack.pop())
							start = cmd[start + 1] - 1;				
						else start++;
					})

COMMANDS (jne,   9, {
						if(stack.pop() != stack.pop())
							start = cmd[start + 1] - 1;
						else start++;
						})

COMMANDS (call,  10,{
						stack.push(start + 2);
						start = cmd[start + 1] - 1;
					})


COMMANDS (add,   11,{
						stack.push(stack.pop() + stack.pop());
					})

COMMANDS (sub,   12,{
						stack.push(stack.pop() - stack.pop());
					})

COMMANDS (div,   13,{
						stack.push(stack.pop() / stack.pop());
					})

COMMANDS (mul, 	 14,{
						stack.push(stack.pop() * stack.pop());
					})

COMMANDS (fsqrt, 15,{
						stack.push(sqrt(stack.pop()));
					})

COMMANDS (in,    16,{
						scanf("%d", &tmp);
						stack.push(tmp);
					})


COMMANDS (ret,   17,{
						start  = stack.pop() - 1;
					})

COMMANDS (out,   18,{
						printf("%d\n", stack.pop());
					})

COMMANDS (print, 19,{
						for(int start = r_size - v_size; start < r_size; start++){
							printf("%c", ram[start]);
						}
					})