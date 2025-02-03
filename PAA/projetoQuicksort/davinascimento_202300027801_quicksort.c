#include <stdio.h>
#include <stdint.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int32_t passos = 0;

typedef struct dado {
    char nome[3];
    int32_t passos;
} st_Dado;

int32_t pegarProxInt(FILE* arquivo) {
    int32_t saida;

    fscanf(arquivo, "%d ", &saida);

    return saida;
}

void trocarInt32(int32_t* a, int32_t* b) {
    passos++;
    int32_t temp = *a;

    *a = *b;
    *b = temp;
}

int32_t* mediana(int32_t* num1, int32_t* num2, int32_t* num3) {
    if(*num1 <= *num2 && *num2 <= *num3 || *num1 >= *num2 && *num2 > *num3) {
        return num2;
    }

    if(*num1 > *num2 && *num1 < *num3 || *num1 < *num2 && *num1 > *num3) {
        return num1;
    }

    return num3;
}


int32_t* aleatorio(int32_t* vetor, int32_t inicio, int32_t fim) {
    return &vetor[inicio + abs(vetor[inicio]) % (fim - inicio + 1)];
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

int32_t hoareRandom(int32_t* vetor, int32_t inicio, int32_t fim) {
    trocarInt32(&vetor[inicio], aleatorio(vetor, inicio, fim));

    return hoare(vetor, inicio, fim);
}

int32_t medianaHoare(int32_t* vetor, int32_t inicio, int32_t fim) {
    int32_t tamanho = fim - inicio + 1;

    trocarInt32(&vetor[inicio], mediana(
        &vetor[tamanho / 4 + inicio],
        &vetor[tamanho / 2 + inicio],
        &vetor[(tamanho * 3) / 4 + inicio]
    ));

    return hoare(vetor, inicio, fim);
}

int32_t lomuto(int32_t* vetor, int32_t inicio, int32_t fim) {
    int32_t pivo = vetor[fim];
    int32_t cursor = inicio - 1;

    for(int x = inicio; x < fim; x++) {
        if(vetor[x] <= pivo) {
            trocarInt32(&vetor[++cursor], &vetor[x]);
        }
    }

    trocarInt32(&vetor[++cursor], &vetor[fim]);

    return cursor;
}

int32_t lomutoRandom(int32_t* vetor, int32_t inicio, int32_t fim) {
    trocarInt32(&vetor[fim], aleatorio(vetor, inicio, fim));

    return lomuto(vetor, inicio, fim);
}

int32_t medianaLomuto(int32_t* vetor, int32_t inicio, int32_t fim) {
    int32_t tamanho = fim - inicio + 1;

    trocarInt32(&vetor[fim], mediana(
        &vetor[tamanho / 4 + inicio],
        &vetor[tamanho / 2 + inicio],
        &vetor[(tamanho * 3) / 4 + inicio]
    ));

    return lomuto(vetor, inicio, fim);
}

void quicksortHP(int32_t* vetor, int32_t inicio, int32_t fim) {
    passos++;
    if(inicio < fim) {
        int32_t pivo = hoare(vetor, inicio, fim); 
        quicksortHP(vetor, inicio, pivo);
        quicksortHP(vetor, pivo + 1, fim);
    }
}

void quicksortLP(int32_t* vetor, int32_t inicio, int32_t fim) {
    passos++;
    if(inicio < fim) {
        int32_t pivo = lomuto(vetor, inicio, fim); 
        quicksortLP(vetor, inicio, pivo - 1);
        quicksortLP(vetor, pivo + 1, fim);
    }
}

void quicksortHA(int32_t* vetor, int32_t inicio, int32_t fim) {
    passos++;
    if(inicio < fim) {
        int32_t pivo = hoareRandom(vetor, inicio, fim); 
        quicksortHA(vetor, inicio, pivo);
        quicksortHA(vetor, pivo + 1, fim);
    }
}

void quicksortLA(int32_t* vetor, int32_t inicio, int32_t fim) {
    passos++;
    if(inicio < fim) {
        int32_t pivo = lomutoRandom(vetor, inicio, fim); 
        quicksortLA(vetor, inicio, pivo - 1);
        quicksortLA(vetor, pivo + 1, fim);
    }
}

void quicksortHM(int32_t* vetor, int32_t inicio, int32_t fim) {
    passos++;
    if(inicio < fim) {
        int32_t pivo = medianaHoare(vetor, inicio, fim); 
        quicksortHM(vetor, inicio, pivo);
        quicksortHM(vetor, pivo + 1, fim);
    }
}

void quicksortLM(int32_t* vetor, int32_t inicio, int32_t fim) {
    passos++;
    if(inicio < fim) {
        int32_t pivo = medianaLomuto(vetor, inicio, fim); 
        quicksortLM(vetor, inicio, pivo - 1);
        quicksortLM(vetor, pivo + 1, fim);
    }
}

void merge(st_Dado* saida, st_Dado* vetor, int inicio, int meio, int fim) {
    int indexEsq = inicio;
    int indexDir = meio + 1;
    int indexSaida = inicio;

    while(indexEsq <= meio && indexDir <= fim) {
        if(vetor[indexEsq].passos <= vetor[indexDir].passos) {
            saida[indexSaida] = vetor[indexEsq];
            indexEsq++;
        }
        else {
            saida[indexSaida] = vetor[indexDir];
            indexDir++;
        }

        indexSaida++;
    }

    while(indexEsq <= meio) {
        saida[indexSaida] = vetor[indexEsq];
        indexSaida++;
        indexEsq++;
    }

    while(indexDir <= fim) {
        saida[indexSaida] = vetor[indexDir];
        indexSaida++;
        indexDir++;
    }

    for(int c = inicio; c <= fim; c++) {
        vetor[c] = saida[c];
    }
}

void mergeSort(st_Dado* saida, st_Dado* vetor, int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        mergeSort(saida, vetor, inicio, meio);
        mergeSort(saida, vetor, meio + 1, fim);

        merge(saida, vetor, inicio, meio, fim);
    }
}

int main(int argc, char** argv) {
    FILE* entrada = fopen(argv[1], "r");
    FILE* saida = fopen(argv[2], "w");

    int32_t numVetores = pegarProxInt(entrada);
    st_Dado dados[6];

    for(int32_t z = 0; z < numVetores; z++) {
        int32_t tamanho = pegarProxInt(entrada);
        int32_t* vOriginal = (int32_t*) malloc(sizeof(int32_t) * tamanho);
        int32_t* vBagunca = (int32_t*) malloc(sizeof(int32_t) * tamanho);
        
        for(int32_t w = 0; w < tamanho; w++) {
            vOriginal[w] = pegarProxInt(entrada);
        }
        
        memcpy(vBagunca, vOriginal, tamanho * sizeof(int32_t));
        quicksortLP(vBagunca, 0, tamanho - 1);
        dados[0].nome[0] = 'L'; 
        dados[0].nome[1] = 'P'; 
        dados[0].nome[2] = '\0'; 
        dados[0].passos = passos;
        passos = 0;

        memcpy(vBagunca, vOriginal, tamanho * sizeof(int32_t));
        quicksortLM(vBagunca, 0, tamanho - 1);
        dados[1].nome[0] = 'L'; 
        dados[1].nome[1] = 'M'; 
        dados[1].nome[2] = '\0'; 
        dados[1].passos = passos;
        passos = 0;

        memcpy(vBagunca, vOriginal, tamanho * sizeof(int32_t));
        quicksortLA(vBagunca, 0, tamanho - 1);
        dados[2].nome[0] = 'L'; 
        dados[2].nome[1] = 'A'; 
        dados[2].nome[2] = '\0'; 
        dados[2].passos = passos;
        passos = 0;

        memcpy(vBagunca, vOriginal, tamanho * sizeof(int32_t));
        quicksortHP(vBagunca, 0, tamanho - 1);
        dados[3].nome[0] = 'H'; 
        dados[3].nome[1] = 'P'; 
        dados[3].nome[2] = '\0'; 
        dados[3].passos = passos;
        passos = 0;
        
        memcpy(vBagunca, vOriginal, tamanho * sizeof(int32_t));
        quicksortHM(vBagunca, 0, tamanho - 1);
        dados[4].nome[0] = 'H'; 
        dados[4].nome[1] = 'M'; 
        dados[4].nome[2] = '\0'; 
        dados[4].passos = passos;
        passos = 0;

        memcpy(vBagunca, vOriginal, tamanho * sizeof(int32_t));
        quicksortHA(vBagunca, 0, tamanho - 1);
        dados[5].nome[0] = 'H'; 
        dados[5].nome[1] = 'A'; 
        dados[5].nome[2] = '\0'; 
        dados[5].passos = passos;
        passos = 0;

        st_Dado* aux = (st_Dado*) malloc(sizeof(st_Dado) * 6);
        mergeSort(aux, dados, 0, 5);
        free(aux);

        fprintf(saida, "%d:N(%d),%s(%d),%s(%d),%s(%d),%s(%d),%s(%d),%s(%d)\n",
            z, tamanho,
            dados[0].nome, dados[0].passos,
            dados[1].nome, dados[1].passos,
            dados[2].nome, dados[2].passos,
            dados[3].nome, dados[3].passos,
            dados[4].nome, dados[4].passos,
            dados[5].nome, dados[5].passos
        );

        free(vBagunca);
        free(vOriginal);
    }

    fclose(entrada);
    fclose(saida);

    return 0;
}