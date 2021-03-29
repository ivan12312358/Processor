push 6143
pop rcx
push 0
pop rax

call :str
call :str

print
end


str:
    
    loop_1:

        push 5
        push rax

        je :last_str

        push -
        pop [rcx + 1]

        push 1
        push rcx
        add
        pop rcx
    
        push 1
        push rax
        add
        pop rax

    jmp :loop_1
    
    last_str:
    
    push 10
    pop [rcx + 1]

    push 1
    push rcx
    add
    pop rcx

    push 0
    pop rax

    ret


clmn:
    
    loop_2:
        
        push 4
        push rax

        je :last_clmn

        push |
        pop [rcx + 1]

        push 1
        push rcx
        add
        pop rcx

        push 1
        push rax
        add
        pop rax

        push 0
        pop rbx

        loop_3:
            
            push 4
            push rbx

            je :lbl

            push 32
            pop [rcx + 1]

            push 1
            push rcx
            add
            pop rcx
        
        jmp :loop_3

        lbl:

        push |
        pop [rcx + 1]

        push 1
        push rcx
        add
        pop rcx

        push 10
        pop [rcx + 1]

        push 1
        push rcx
        add
        pop rcx

    jmp :loop_2

    last_clmn:

    push 0
    pop rax

    ret