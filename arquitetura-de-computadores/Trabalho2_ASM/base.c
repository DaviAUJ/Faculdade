#include <stdio.h>

int elevar(int base, int expoente) {
    if(expoente <= 0) {
        return 1;
    }

    return elevar(base, expoente - 1) * base;
}

void elevarVetor(int vetor[], int tamanho, int divisor) {
    for(int i = 0; i < tamanho; i++) {
        vetor[i] = elevar(vetor[i], divisor);
    }
}

int main() {
    int tamanho = 5;
    int vetor[] = {10, 2, 5, 3, 4};

    elevarVetor(vetor, tamanho, 3);

    for(int i = 0; i < tamanho; i++) {
        printf("%d\n", vetor[i]);
    }

    return 0;
}



