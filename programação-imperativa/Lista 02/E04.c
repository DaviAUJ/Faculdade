#include <stdio.h>

// Escrever um programa em C para ler uma temperatura em Celsius C e
// a retornar em Fahrenheit e em Kelvin. Fórmulas de conversão para
// Fahrenheit: F = (C * 9/5) + 32; para Kelvin: K = C + 273,5.
// Criar uma função para cada conversão.

double CParaF(double celsius) { return celsius * 9 / 5 + 32; }
double CParaK(double celsius) { return celsius + 273.5; }

int main() {
    double temperatura;

    printf("Digite uma temperatura em Celsius: ");
    scanf("%lf", &temperatura);

    printf("\nEm Kelvin: %.2lf", CParaK(temperatura));
    printf("\nEm Fahrenheit: %.2lf", CParaF(temperatura));
}
