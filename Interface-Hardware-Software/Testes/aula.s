.intel_syntax noprefix
.global main

.section .rodata
msg:
	.string "Hello World"

.section .text
main:
	push rbp
	mov rbp, rsp
	sub rsp, 16

	mov rax, 1
	mov rdi, 1
	mov rsi, [rip + msg]
	syscall
	
	xor rax, rax
	mov rsp, rbp
	pop rbp

	ret
