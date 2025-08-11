.intel_syntax noprefix

.section .bss
	Output: .quad 0
	Input: .quad 0
	Image_Vector: .quad 0
	Image_Vector_Size: .quad 0
	Height: .quad 0
	Length: .quad 0
	.lcomm Colors, 16

.section .rodata
	WRITE_MODE: .asciz "w"
	READ_MODE: .asciz "r"
	INT_READ_FORMAT: .asciz "%d "
	HEX_READ_FORMAT: .asciz "%X "
	IMAGE_NUMBER_FORMAT: .asciz "[%d]\n"
	NEWLINE_FORMAT: .asciz "%s\n"

.section .text
.global main



# int getDec()
# Pega um inteiro decimal do arquivo e retorna-o
getDec:
	# Prólogo
	push rbp
	mov rbp, rsp
	sub rsp, 16

	# argumentos fscanf
	mov rdi, [rip + Input]
	lea rsi, [rip + INT_READ_FORMAT]
	lea rdx, [rbp - 4]
	call fscanf@plt

	# colocando em rax
	mov eax, [rbp - 4]

	# Epílogo
	mov rsp, rbp
	pop rbp
	ret



# void getColors()
# Preenche o vetor de cores com elas
getColors:
	# Prólogo
	push rbp
	mov rbp, rsp
	sub rsp, 8
	push rbx

	# Zera contador
	xor rbx, rbx

__getColors_ForLoop:
	# Chamada função para pegar os valores
	call getDec
	

	# Preenche vetor
	lea rdi, [rip + Colors]
	mov [rdi + rbx], al 

	# Lógica do for. Repete 16 vezes
	inc rbx
	cmp rbx, 16
	jne __getColors_ForLoop

__getColors_Exit:
	# Epílogo
	pop rbx
	mov rsp, rbp
	pop rbp
	ret



# int getHex()
# Pega o próximo hex do arquivo
getHex:
	# Prólogo
	push rbp
	mov rbp, rsp
	sub rsp, 16
	
	# Pegando o hex
	mov rdi, [rip + Input]
	lea rsi, [rip + HEX_READ_FORMAT]
	lea rdx, [rbp - 4]
	call fscanf@plt

	# Colocando em rax
	mov eax, [rbp - 4]

	# Epílogo
	mov rsp, rbp
	pop rbp
	ret



# void getImageVector()
# Preenche o vetor com os bytes que representam a imagem
getImageVector:
	# Prólogo
	push rbp
	mov rbp, rsp
	push r12
	push r13
	push r14
	push r15

	# Preparando registradores que serão usados
	mov r13, [rip + Image_Vector]
	mov r12, [rip + Image_Vector_Size]
	xor r14, r14

__getImageVector_For:
	# Pegando bytes do arquivo
	call getHex
	
	# Preenchendo vetor
	mov [r13 + r14], al
	
	# Lógica do for
	inc r14
	cmp r14, r12
	jne __getImageVector_For

__getImageVector_Exit:
	# Epílogo
	pop r15
	pop r14
	pop r13
	pop r12
	mov rsp, rbp
	pop rbp
	ret


# void println(char *string)
println:
	push rbp
	mov rbp, rsp

	mov rdx, rdi
	mov rdi, [rip + Input]
	lea rsi, [rip + NEWLINE_FORMAT]

	call fprintf

	mov rsp, rbp
	pop rbp


# void printCurrentImage()
# Printa no arquivo de saída a imagem atual presente nas variáveis globais
printCurrentImage:
	# Prólogo
	push rbp
	mov rbp, rsp

	sub rsp, 8
	push rbx
	push r12
	push r13
	# Ponteiro inicial do Image_Vector
	push r14
	# Index do Image_Vector
	push r15

	mov r15, QWORD PTR [rip + Image_Vector]
	xor r15, r15



__printCurrentImage_Exit:

	# Epílogo
	pop r15
	pop r14
	pop r13
	pop r12
	pop rbx
	mov rsp, rbp
	pop rbp
	ret



# Ponto de entrada do programa
main:
	# Prólogo
	push rbp
	mov rbp, rsp
	
	# Iterador de imagem
	push r12
	# Número de imagens
	push rbx
	
	# Pegando nome dos arquivos
	mov rdi, [rsi + 8]
	mov [rip + Input], rdi
	mov rdi, [rsi + 16]
	mov [rip + Output], rdi

	# Pegando arquivo de entrada
	mov rdi, [rip + Input]
	lea rsi, [rip + READ_MODE]
	call fopen@plt
	mov [rip + Input], rax

	# Pegando arquivo de saida
	mov rdi, [rip + Output]
	lea rsi, [rip + WRITE_MODE]
	call fopen@plt
	mov [rip + Output], rax

	# Pegando as cores
	call getColors

	# Salvando número de imagens
	call getDec
	mov rbx, rax

	# Preparando loop
	xor r12, r12

__main_ImageLoop:
	# Salvando tamanho do vetor de imagem
	call getDec
	mov [rip + Image_Vector_Size], eax

	# Criando vetor da imagem
	mov rdi, rax
	call malloc@plt
	mov [rip + Image_Vector], rax
	
	# Pegando bytes da imagem
	call getImageVector

	# Pegando largura e altura
	call getDec
	mov [rip + Height], eax
	call getDec
	mov [rip + Length], eax
	
	# Printando número da imagem
	mov rdi, [rip + Output]
	lea rsi, [rip + IMAGE_NUMBER_FORMAT]
	mov edx, r12d
	call fprintf@plt

	# Printa imagem
	call printCurrentImage

	# Desalocando vetor 
	mov rdi, [rip + Image_Vector]
	call free@plt

	inc r12
	cmp rbx, r12
	jne __main_ImageLoop

__main_Exit:
	# Fechando entrada
	mov rdi, [rip + Input]
	call fclose@plt

	# Fechando entrada
	mov rdi, [rip + Output]
	call fclose@plt
	
	# Colocando retorno
	xor rax, rax

	# Epílogo
	pop rbx
	pop r12
	mov rsp, rbp
	pop rbp
	ret
