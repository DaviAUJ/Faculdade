#include <stdio.h>

int main() {
    const float COT_DOL_REAL = 4.91; // 1 dólar = 4,91 reais 29/11/2023
    float valor;

    printf("Digite o valor em reais: ");
    scanf("%f", &valor);

    printf("R$%.2f em dolar sao: $%.2f", valor, valor / COT_DOL_REAL);
}