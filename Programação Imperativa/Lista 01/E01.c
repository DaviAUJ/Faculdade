#include <stdio.h>

int main() {
    int valor;

    printf("Digite um valor: ");
    scanf("%d", &valor);

    printf("\nO antecessor eh %d e o sucessor eh %d", valor - 1, valor + 1);
}