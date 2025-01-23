#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>

int32_t passos = 0;

int32_t pegarProxInt(FILE* arquivo) {
    int32_t saida;

    fscanf(arquivo, "%d ", &saida);

    return saida;
}

void trocarInt32(int32_t* a, int32_t* b) {
    int32_t temp = *a;

    *a = *b;
    *b = temp;
}

int32_t hoare(int32_t* vetor, int32_t inicio, int32_t fim) {
    int32_t pivo = vetor[inicio];
    int32_t esq = inicio - 1;
    int32_t dir = fim + 1;

    while(true) {
        while(vetor[--dir] > pivo);
        while(vetor[++esq] < pivo);

        if(esq < dir) {
            trocarInt32(&vetor[esq], &vetor[dir]);
        }
        else {
            return dir;
        }
    }
}

int32_t lomuto(int32_t* vetor, int32_t inicio, int32_t fim) {
    int32_t pivo = vetor[fim];
    int32_t cursor = inicio - 1;

    for(int x = 0; x < fim; x++) {
        if(vetor[x] <= pivo) {
            trocarInt32(&vetor[++cursor], &vetor[x]);
        }
    }

    trocarInt32(&vetor[++cursor], &vetor[fim]);

    return cursor;
}

void quicksortHP(int32_t* vetor, int32_t inicio, int32_t fim) {
    if(inicio < fim) {
        int32_t pivo = hoare(vetor, inicio, fim); 
        quicksortHP(vetor, inicio, pivo);
        quicksortHP(vetor, pivo + 1, fim);
    }
}

void quicksortLP(int32_t* vetor, int32_t inicio, int32_t fim) {
    if(inicio < fim) {
        int32_t pivo = lomuto(vetor, inicio, fim); 
        quicksortHP(vetor, inicio, pivo);
        quicksortHP(vetor, pivo + 1, fim);
    }
}

int main(int argc, char** argv) {
    FILE* entrada = fopen(argv[1], "r");

    int32_t numVetores = pegarProxInt(entrada);

    for(int32_t z = 0; z < numVetores; z++) {
        int32_t tamanho = pegarProxInt(entrada);
        int32_t* vOriginal = malloc(sizeof(int32_t) * tamanho);

        for(int32_t y = 0; y < tamanho; y++) {
            vOriginal[y] = pegarProxInt(entrada);
        }

        quicksortLP(vOriginal, 0, tamanho - 1);

        for(int32_t y = 0; y < tamanho; y++) {
            printf("%d\n", vOriginal[y]);
        }

        return 0;

        free(vOriginal);
    }
}