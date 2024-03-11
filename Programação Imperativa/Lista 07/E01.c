#include <stdio.h>

float media(float* vetor, int tamanho) {
    float soma = 0;

    for(int cont = 0; cont < tamanho; cont++) { soma += vetor[cont]; }

    return soma / tamanho;
}

int main() {
    const int nVendedores = 5;
    
    int vendRuins;
    float lista[nVendedores];
    float mediaVendas;

    // coleta de dados
    for(int cont = 0; cont < nVendedores; cont++) {
        printf("Digite o total vendas do mes do vendedor #%d: ", cont + 1);
        scanf("%f", &lista[cont]);
    }

    mediaVendas = media(lista, nVendedores);
    printf("\nA media de vendas deste mes foi: R$%.2f", mediaVendas);

    // verificação de quantos estão abaixo da média
    for(int cont = 0; cont < nVendedores; cont++) { if(lista[cont] < mediaVendas) { vendRuins++; } }

    printf("\nTiveram %d vendedores abaixo da media este mes", vendRuins);

    return 0;
}