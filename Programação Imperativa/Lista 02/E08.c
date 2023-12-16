#include <stdio.h>

// Cotação do dólar e euro do dia 16/12/2023
// 1 real == 0.20 Dolár == 0.19 euro

const double DOLAR = 0.2;
const double EURO = 0.19;

double cambio(double vReal, double* saidaDolar, double* saidaEuro) {
    *saidaDolar = vReal * DOLAR;
    *saidaEuro = vReal * EURO;
}

int main() {
    double real, dolar, euro;

    printf("Digite um valor em reais: ");
    scanf("%lf", &real);

    cambio(real, &dolar, &euro);

    printf("\nIsto em dolar e: %.2lf", dolar);
    printf("\nIsto em euro e: %.2lf", euro);

    return 0;
}