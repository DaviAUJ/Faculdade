section .data
    msg db "hello, world!\n"

section .text
    global Main

Main:
    mov rax, 1
    mov rdi, 1
    mov rsi, msg
    mov rdx, 13

    syscall
    mov rax, 60
    mov rdi, 0
    syscall
    