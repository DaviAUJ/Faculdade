// Escrever programa para: (a) exibir menu: 1 –
// area, 2 – perímetro e 3 – diagonal; (d) ler
// medida de lado de um quadrado; (c) exibir
// a informação solicitada pelo usuário
// conforme opção de menu selecionada.

#include <stdio.h>
#include <math.h>

float area(float lado) { return lado * lado; }

float perimetro(float lado) { return lado * 4; }

float diagonal(float lado) { return sqrt(2) * lado; }

int main() {
    printf("1 - Area\n2 - Perimetro\n3 - Diagonal\n");

    float lado;
    int escolhaNum;

    printf("\nTamanho do lado do quadrado: ");
    scanf("%f", &lado);

    printf("Escolha uma das opcoes do menu: ");
    scanf("%d", &escolhaNum);

    switch (escolhaNum) {
        case 1: printf("Area: %.2f", area(lado)); break;
        case 2: printf("Perimetro: %.2f", perimetro(lado)); break;
        case 3: printf("diagonal: %.2f", diagonal(lado)); break;

        default: printf("Opcao Invalida");
    }
}