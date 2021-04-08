in
pop rax
call :fact
push rcx
out
end

fact:

    push rax
    push 1
    push rax
    sub

    pop rax
    push rax
    push 1

    ja :L1
        call :fact
    L1:


    pop rax
    pop rcx
    
    pop rdx
    push rdx
    push rbx
    je :L2

        push rdx
        push rax
        mul
        push rcx

    L2:

    ret
    