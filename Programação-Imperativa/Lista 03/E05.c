// Faça um programa para verificar se
// determinado número inteiro lido N é divisível
// por A ou B, mas não simultaneamente pelos
// dois valores dados. São A e B, bem como N,
// dados pelo usuário. Atendendo a condição
// estabelecida, emitir mensagem “ATENDE
// CONDIÇÃO”; caso contrário, exibir: “NÃO
// ATENDE CONDIÇÃO”.

#include <stdio.h>

int main() {
    int N, A, B;

    printf("Digite o dividendo e os divisores: ");
    scanf("%d %d %d", &N, &A, &B);

    if(N % A == 0 && N % B == 0) { printf("Condicao nao atendida"); }
    else { printf("Condicao atendida"); }
}