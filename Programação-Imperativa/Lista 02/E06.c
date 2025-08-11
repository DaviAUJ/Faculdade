#include <stdio.h>
#include <math.h>

// Escrever um programa em C para ler peso em kg e altura em m. Calcular
// e exibir o IMC da pessoa considerando IMC = peso / altura^2. Para cálculo
// de IMC usar função, e nessa aplicar função de cálculo da potência (seja
// definida pelo programação ou nativa).

double imc(double altura, double peso) { return peso / pow(altura, 2); }

int main() {
    double altura, peso;

    printf("Digite sua altura(m): ");
    scanf("%lf", &altura);

    printf("Digite seu peso(kg): ");
    scanf("%lf", &peso);

    printf("\nSeu IMC e: %.2lf", imc(altura, peso));

    return 0;
}
