// Questão das sequencia de números

#include <stdio.h>

void printSeq(int num) {
    int contagem = 1;

    while(contagem <= num) { 
        printf("%d ", contagem); 

        contagem++;
    }

    printf("\n");
}

int main() {
    int ultimo, contagem = 1;

    printf("Digite um valor: ");
    scanf("%d", &ultimo);

    while(contagem <= ultimo) {
        printSeq(contagem);
        
        contagem++;
    }
}