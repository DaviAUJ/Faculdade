#include <stdio.h>

// Escrever um programa em C para ler um valor V em reais, taxa de
// câmbio fixa de dólar e taxa de câmbio fixa de euro e exibir em tela os
// correspondentes a V em dólar e em euro. Para tanto, criar função F em que
// dados valor e taxa de câmbio, retorna o valor convertido. Criar módulo com
// aplicação de F, parâmetros de entrada e dois parâmetros de saída: valor em
// dólar e valor em euro.

double cambio(double vReal, double cDolar, double cEuro, double* saidaDolar, double* saidaEuro) {
    *saidaDolar = vReal * cDolar;
    *saidaEuro = vReal * cEuro;
}

int main() {
    double real, cambioDolar, cambioEuro, dolar, euro;

    printf("Digite um valor em reais: ");
    scanf("%lf", &real);

    printf("Digite o valor de 1 real em dólar: ");
    scanf("%lf", &cambioDolar);

    printf("Digite o valor de 1 real em euro: ");
    scanf("%lf", &cambioEuro);
    
    cambio(real, cambioDolar, cambioEuro, &dolar, &euro);

    printf("\n%.2lf em dolar e: %.2lf", real, dolar);
    printf("\n%.2lf em euro e: %.2lf", real, euro);

    return 0;
}
