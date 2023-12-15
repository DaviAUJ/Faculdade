#include <stdio.h>

int main() {
    // Escrever um programa em C para calcular a área de um retângulo. 
    // O usuário deve fornecer o comprimento e a largura desse.

    float base, altura;

    printf("Digite a base do retangulo: ");
    scanf("%f", &base);

    printf("Digite a altura do retangulo: ");
    scanf("%f", &altura);

    printf("\nA area do retangulo e %.2f", base * altura);
}