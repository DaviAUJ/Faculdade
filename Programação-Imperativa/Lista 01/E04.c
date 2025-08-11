#include <stdio.h>

int main() {
    float valor, cotacao;

    printf("Digite a cotação do dólar");
    scanf("%f", &cotacao);

    printf("Digite o valor em reais: ");
    scanf("%f", &valor);

    printf("R$%.2f em dolar sao: $%.2f", valor, valor * cotacao);
}