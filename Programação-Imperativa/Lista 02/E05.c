#include <stdio.h>

// Escrever um programa em C para ler o raio de um círculo e exibir em
// tela a área desse (círculo) usando a fórmula: Área = π * raio^2. Usar um
// módulo/função para cálculo da área, outro módulo/função para cálculo do
// quadrado. E usar uma constante para definição de π. Recomenda-se o
// uso de função e/ou constante nativa, se houver.

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
