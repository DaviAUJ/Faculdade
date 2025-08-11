%define SYS_READ 0
%define SYS_WRITE 1
%define SYS_EXIT 60
%define STD_IN 0
%define STD_OUT 1
%define EXIT_CODE 0

section .data
    NEW_LINE db 0xa
    input_len db 2

section .bss
    number resb 2

section .text
    global _start



NewLine:
    mov rax, SYS_WRITE
    mov rdi, STD_OUT
    mov rsi, NEW_LINE
    mov rdx, 1
    syscall
    ret



StringToInt:
    xor rax, rax
    mov rcx, 10

__repeat:
    cmp [rsi], byte 0
    je __return
    mov bl, [rsi]
    sub bl, 48
    mul rcx
    add rax, rbx
    inc rsi
    jmp __repeat

__return:
    ret



IntToString:
    mov rcx, 0
    mov rdx, 0
    mov rbx, 10
    div rbx
    add rdx, 48
    push rdx
    inc rcx
    cmp rax, 0
    jne IntToString
    mov rax, rcx


ReadInt:
    mov rax, SYS_READ
    mov rdi, STD_IN
    mov rsi, number
    mov rdx, 2
    syscall

    call StringToInt

    ret



Exit:
    mov rax, SYS_EXIT
    mov rdi, EXIT_CODE

    syscall



_start:
    call ReadInt
    mov r12, [rax]


    
    call NewLine

    call Exit



