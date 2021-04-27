push 6144
pop  rdx

call :coeff
call :scanf
call :a_eq_zero

push rdx
push 1
je :l6

call :discr
jmp :l7

l6:

call :linear

l7:

call :print
end


scanf:

    in
    pop rax

    in
    pop rbx
    
    in
    pop rcx
    
    ret

discr:

    push 4
    push rax
    mul
    push rcx
    mul

    push rbx
    push rbx
    mul

    sub

    pop rdx

    push 0
    push rdx
    jb :no_roots

    push 0
    push rdx
    je :one_root

    push 0
    push rdx
    ja :two_roots

    l1:
    ret

print:

    push rcx
    out

    push rcx
    push 1
    je :print_one

    push rcx
    push 2
    je :print_two

    l2:
    ret

linear:
    
    call :b_eq_zero
    
    push rdx
    push 2
    jne :l8

    call :c_eq_zero

    push rdx
    push 3
    jne :l9

    push 8
    pop rcx
    ret

    l8:

    push rbx

    push rcx
    push -1
    mul

    div
    pop rax

    push 1
    pop rcx

    ret

    l9:

    push 0
    pop rcx
    ret

no_roots:

    push 0
    pop rcx
    jmp :l1

one_root:

    push 1
    pop rcx

    push rax
    push 2
    mul

    push rbx
    push -1
    mul

    div
    pop rax
    jmp :l1

two_roots:

    push 2
    pop rcx

    push rbx
    push -1
    mul
    pop rbx

    push rdx
    fsqrt
    pop rdx

    push rax
    push 2
    mul

    push rbx
    push rdx
    add

    div

    push rax
    push 2
    mul

    push rdx
    push rbx
    sub

    div

    pop rbx
    pop rax

    jmp :l1

print_one:
    
    push rax
    out
    jmp :l2

print_two:
    
    push rax
    out
    push rbx
    out
    jmp :l2

a_eq_zero:
    
    push rax
    push 0
    jne :l3

    push 1
    pop rdx

    l3:
    ret

b_eq_zero:

    push rbx
    push 0
    jne :l4

    push 2
    pop rdx

    l4:
    ret

c_eq_zero:

    push rcx
    push 0
    jne :l5

    push 3
    pop rdx

    l5:
    ret
coefficients
coeff:

    push _
    push s
    push t
    push n
    push e
    push i
    push с
    push i
    push f
    push f
    push e
    push o
    push c
    push _
    push r
    push e
    push t
    push n
    push E

    push 19
    pop  rcx

    Loop:
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
        jb :Loop

    print

    ret
