// Calcule IMC e mostre o nível de obesidade

#include <stdio.h>
#include <math.h>

float imc(float altura, float peso) { return peso / pow(altura / 100, 2); }

int main() {
    float altura, peso, indice;

    printf("Peso(kg): ");
    scanf("%f", &peso);

    printf("Altura(cm): ");
    scanf("%f", &altura);

    indice = imc(altura, peso);

    printf("\nIndice: %.2f\n", indice);

    if(indice < 18.5) { printf("Magreza"); }
    else if(indice < 25) { printf("Saudavel"); }
    else if(indice < 30) { printf("Sobrepeso"); }
    else if(indice < 35) { printf("Obesidade I"); }
    else if(indice < 40) { printf("Obesidade II (Severa)");; }
    else { printf("Obesidade III (Morbida)"); }
}