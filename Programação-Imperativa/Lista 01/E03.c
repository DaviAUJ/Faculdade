#include <stdio.h>

int main() {
    int ano, intervalo;

    printf("Digite o ano da primeira dose: ");
    scanf("%d", &ano);

    printf("Digite o intervalo entre doses: ");
    scanf("%d", &intervalo);

    printf("\nOs proximos anos para tomar a vacina são: %d, %d, %d", ano + intervalo, ano + 2 * intervalo, ano + 3 * intervalo);
}