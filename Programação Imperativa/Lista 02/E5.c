#include <stdio.h>

const float PI = 3.141592;

double quadrado(double valor) { return valor * valor; }
double areaCirculo(double raio) { return PI * quadrado(raio); }

int main() {
    double raio;

    printf("Digite um raio de um circulo para saber sua area: ");
    scanf("%lf", &raio);

    printf("\nA area deste circulo e: %lf", areaCirculo(raio));

    return 0;
}