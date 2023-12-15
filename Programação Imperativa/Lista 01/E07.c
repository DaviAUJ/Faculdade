#include <stdio.h>

int main() {
    // Criar um programa em C que converta a temperatura de Celsius para Fahrenheit.
    // Solicite ao usuário a temperatura em Celsius e exiba o resultado em Fahrenheit.
    // Pesquise e escreva, como comentário, a regra de conversão usada.

    float celsius;

    printf("Digite um valor de temperatura em graus Celsius: ");
    scanf("%f", &celsius);

    // Para converter de Celsius para Fahrenheit você multiplica o valor em graus celsius por 9,
    // Divide por 5 e soma 32
    float fahrenheit = celsius * 9 / 5 + 32;

    printf("%.1f graus Celsius em Fahrenheit: %.1f ", celsius, fahrenheit);
}