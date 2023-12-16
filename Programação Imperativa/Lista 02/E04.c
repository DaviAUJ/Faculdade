#include <stdio.h>

double CParaF(double celsius) { return celsius * 9 / 5 + 32; }
double CParaK(double celsius) { return celsius + 273.5; }

int main() {
    double temperatura;

    printf("Digite uma temperatura em Celsius: ");
    scanf("%lf", &temperatura);

    printf("\nEm Kelvin: %.2lf", CParaK(temperatura));
    printf("\nEm Fahrenheit: %.2lf", CParaF(temperatura));
}