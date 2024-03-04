#include <stdio.h>

int fatorial(int valor) {
    int output = 1;

    for(int i = 2; i <= valor; i++) { output *= i; }

    return output;
}

int main() {
    int N, fator;

    printf("Quantas fatoriais serao calculadas? ");
    scanf("%d", &N);

    for(int i = 0; i < N; i++) {
        printf("\nDigite um valor: ");
        scanf("%d", &fator);

        // Caso o numero seja negativo pedir de novo
        while(fator < 0) {
            printf("Digite novamente um valor: ");
            scanf("%d", &fator);
        }

        printf("%d! e igual a %d\n", fator, fatorial(fator));
    }
}