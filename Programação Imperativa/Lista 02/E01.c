#include <stdio.h>

// Há pessoas que precisam fazer tratamento de saúde contínuo (em
// comprimidos), a exemplo de reposição hormonal. Sabendo que uma
// pessoa deve fazer uso de X comprimidos ao mês e que em cada caixa
// desse há N unidades (comprimidos); escrever um programa em C
// onde se lê X e N e é exibido o número de caixas a serem adquiridas.

int remedio(int comMes, int comCaixa ) {
    if(comMes % comCaixa == 0) { return comMes / comCaixa; }
    else { return comMes / comCaixa - (comMes / comCaixa) % 1 + 1; }
}

// Esta primeiro exercicio e o segundo podem ser implmentados com a mesma função
// esta função seria uma de divisão com arredondamento para cima

int main() {
    int comprimidosMes, comprimidosCaixa;

    printf("Quantos comprimidos precisam ser usados ao mes? ");
    scanf("%d", &comprimidosMes);

    printf("Quantos comprimidos tem em uma caixa? ");
    scanf("%d", &comprimidosCaixa);

    printf("Para este mes é necessario comprar %d caixas de comprimido", remedio(comprimidosMes, comprimidosCaixa));
}
