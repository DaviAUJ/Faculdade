#include <stdio.h>
#include <math.h>

double imc(double altura, double peso) { return peso / pow(altura, 2); }

int main() {
    double altura, peso;

    printf("Digite sua altura: ");
    scanf("%lf", &altura);

    printf("Digite seu peso: ");
    scanf("%lf", &peso);

    printf("\nSeu IMC e: %.2lf", imc(altura, peso));

    return 0;
}