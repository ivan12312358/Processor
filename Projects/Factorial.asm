push 6144
pop  rdx

call :printf

in
pop rax

push rax
push 1

jb :L3
    push 1
    out
    end
L3:

push rax
pop rbx

call :factorial
end

factorial:

    push rax
    push 1
    push rax
    sub

    pop rax
    push rax
    push 1

    ja :L1
        call :factorial
    L1:


    pop rax
    pop rcx

    pop rdx
    push rdx
    push rbx

    jne :L2    
        push rax
        push rdx
        mul
        out
        ret
    L2:

    push rdx
    push rax
    mul
    push rcx


    ret

printf:

    push _
    push r
    push e
    push b
    push m
    push u
    push n
    push _
    push r
    push e
    push t
    push n
    push E

    push 13
    pop  rcx

    L4:
        pop [rdx]
        push 1
        push rdx
        add
        pop rdx
        push 1
        push rcx
        sub
        pop  rcx
        push rcx
        push 0
        jb :L4

    print

    ret
