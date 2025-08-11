#include <stdio.h>
#include <math.h>

int main() {
    float pAtual, pIdeal, perdaMensal;

    printf("Digite o peso atual do paciente: ");
    scanf("%f", &pAtual);

    printf("Digite o peso ideal do paciente: ");
    scanf("%f", &pIdeal);

    printf("Digite a perda mensal do paciente: ");
    scanf("%f", &perdaMensal);

    int dias = ceil((pAtual - pIdeal) / perdaMensal * 30);
    
    printf("\nO paciente chegara no peso ideal em %d dias", dias);
}