#include <stdio.h>

int main() {
    float valor;

    printf("Digite um valor: ");
    scanf("%f", &valor);

    printf("\nTabuada:");
    for(int i = 1; i <= 10; i++) { printf("\n%.2f X %d = %.2f", valor, i, valor * i); }
}