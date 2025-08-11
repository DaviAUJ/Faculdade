.intel_syntax noprefix

.section .bss
	OUTPUT: .quad 0
	INPUT: .quad 0

.section .rodata
	WRITE_MODE: .asciz "w"
	READ_MODE: .asciz "r"

.section .data


.section .text
.global main

main:
	// Prólogo
	push rbp
	mov rbp, rsp
	sub rsp, 16
	
	// Pegando nome dos arquivos
	mov rdi, [rsi + 8]
	mov [rip + INPUT], rdi
	mov rdi, [rsi + 16]
	mov [rip + OUTPUT], rdi

	// Pegando arquivo de entrada
	mov rdi, [rip + INPUT]
	lea rsi, [rip + READ_MODE]
	call fopen@plt
	mov [rip + INPUT], rax

	// Pegando arquivo de saida
	mov rdi, [rip + OUTPUT]
	lea rsi, [rip + WRITE_MODE]
	call fopen@plt
	mov [rip + OUTPUT], rax



exit:
	// Fechando entrada
	mov rdi, [rip + INPUT]
	call fclose@plt

	// Fechando saída
	mov rdi, [rip + OUTPUT]
	call fclose@plt

	// Epílogo
	xor rax, rax
	mov rsp, rbp
	pop rbp
	ret
