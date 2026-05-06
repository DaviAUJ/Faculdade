section .data
    num1 dq 100
    num2 dq 50
    msg  db "The sum is correct!", 10

section .text
    global _start

_start:
    mov rax, [num1]
    mov rbx, [num2]
    add rax, rbx

.compare:
    cmp rax, 150
    jne .exit
    jmp .correctSum

.correctSum:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, 20
    syscall 
    jmp .exit

.exit:
    mov rax, 60
    mov rdi, 0
    syscall 