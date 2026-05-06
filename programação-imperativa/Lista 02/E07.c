#include <stdio.h>

// Escrever um programa em C sobre investimento. Deve ser efetuada a
// leitura do valor inicial investido, do valor investido mensalmente e do tempo
// de investimento (desconsiderar juros) e retornar o valor final (montante) e o
// valor do rendimento (montante – valor inicial investido). Deve ser aplicado
// um módulo(função) com dois parâmetros de saída.

double investimento(double vInicial, double vMensal, double tempo, double* saida1, double* saida2) {
    *saida1 = vInicial + vMensal * tempo; // dinheiro total
    *saida2 = vMensal * tempo; // Dinheiro apenas do investimento
}

int main() {
    double vInicial, vMensal, tempo, montante, rendimento;

    printf("Digite o valor inicial do investimento: ");
    scanf("%lf", &vInicial);
    
    printf("Digite o valor mensal do investimento: ");
    scanf("%lf", &vMensal);

    printf("Digite o tempo de investimento: ");
    scanf("%lf", &tempo);

    investimento(vInicial, vMensal, tempo, &montante, &rendimento);

    printf("\nSeu montante e: %lf", montante);
    printf("\nValor do seu investimento: %lf", rendimento);

    return 0;
}
