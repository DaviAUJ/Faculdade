// Escrever programa para exibir menu: U – unidade, D –
// dezena, C – centena, M – unidade de milhar e Z –
// dezena de milhar; ler um número de 0 a 99.999 e deste
// identificar a unidade, ou a dezena, ou a centena, ou a
// unidade de milhar, ou a centena de milhar; conforme a
// opção selecionada.
// Deve funcionar para o caso do usuário pressionar letras
// maiúsculas ou minúsculas.
// Deve ser aplicado switch-case.
// Deve haver mensagem de erro para o caso do usuário
// selecionar opção não existente.
// Deve ser modularizado.

#include <stdio.h>

int power(int x, int y) {
    int output = 1;

    for(int i = 0; i < y; i++) { output *= x; }

    return output;
}

int pegarCasa(int valor, int index) { return (valor % power(10, index + 1)) / power(10, index); }

int main() {
    char escolha;
    int num, casa;

    printf("Digite um valor de 0 a 99.999: ");
    scanf("%d", &num);

    printf("\nEscolha casa para destacar\nU - Unidade\nD - Dezena\nC - Centena\nM - Unidade de Milhar\nZ - Dezena de Milhar\n");
    printf("\nEscolha: ");
    scanf(" %c", &escolha);

    switch (escolha) {
        case 'u':
        case 'U': printf("Unidade: %d", pegarCasa(num, 0)); break;

        case 'd':
        case 'D': printf("Dezena: %d", pegarCasa(num, 1)); break;

        case 'c':
        case 'C': printf("Centena: %d", pegarCasa(num, 2)); break;

        case 'm':
        case 'M': printf("Unidade de Milhar: %d", pegarCasa(num, 3)); break;

        case 'z':
        case 'Z': printf("Dezena de Milhar: %d", pegarCasa(num, 4)); break;

        default: printf("Opcao Invalida");
    }
}