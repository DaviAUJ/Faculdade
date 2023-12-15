#include <stdio.h>

double cubo(double x) { return x * x * x; }

void main() {
    double valor;

    printf("Digite um numero: ");
    scanf("%lf", &valor);

    valor = cubo(valor);

    printf("Este valor ao cubo e: %lf", valor);
}