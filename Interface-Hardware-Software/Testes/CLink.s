;; Importe as funções que quer usar
extern printf
extern exit

;; Definição das variáveis
section .data
    msg db "Hello World!", 0
    fmt db "Output is: %s", 10, 0

section .text

;; Para linkar com o C, o nome do entry point precisa ser main, igual no C
global main

main:
    ;; Passando os parametros
    ;; printf(rdi, rsi);
    ;; As funções em assembly seguem essa ordem de registrador: rdi, rsi, rdx, rcx, r8, r9
    ;; Não me pergunte o porquê dessa bomba ser assim
    mov rdi, fmt
    mov rsi, msg

    ;; Alinha a stack, senão algo explode e as coisas apontam pro lugar errado
    ;; a função do alinhamento é A(n) = -2*n sendo n o número de argumentos
    and rsp, -16

    ;; Chama a função
    call printf

    ;; Fazendo o mesmo que fiz acima
    mov rdi, 0
    and rsp, -8
    call exit ;; Finaliza o programa

;; Usei três comandos para rodar:
;; nasm -f elf64 -o obj.o MeuArquivoASM.s
;; gcc -z noexecstack -no-pie obj.o -o exec
;;./exec

;; Output is: Hello World!

;; Esse -z noexecstack serve pra fazer o compilador calar a boca. Não sei as reais implicações disso
;; -no-pie tem haver com o kernel jogar nosso programa numa posição aleatória da memória e essa
;; flag diz que não é pra fazer isso. Só compila se usar
