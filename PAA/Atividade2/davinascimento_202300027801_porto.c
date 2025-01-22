#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct container {
    char codigo[12];
    char cnpj[19];
    int peso;
} st_Container;

int pegarNumeroContainers(FILE* arquivo) {
    char numero[7];
    int saida;
    
    fgets(numero, 7, arquivo);
    sscanf(numero, "%d", &saida);

    return saida;
}

int pegarNumeroChecagens(FILE* arquivo, int numContainers) {
    char numero[7];
    int saida;
    
    fseek(arquivo, numContainers * 38, SEEK_CUR);
    fgets(numero, 7, arquivo);
    sscanf(numero, "%d", &saida);

    return saida;
}

void pegarContainers(FILE* arquivo, st_Container* destino, int quantidade) {
    char infos[38];
    st_Container container;

    for(int a = 0; a < quantidade; a++) {
        fgets(infos, 38, arquivo);

        sscanf(infos, "%s %s %d", &container.codigo, &container.cnpj, &container.peso);

        destino[a] = container;
    }
}

char compararCodigo(char* codigo1, char* codigo2) {
    for(int b = 0; b < 11; b++) {
        if(codigo1[b] < codigo2[b]) {
            return 'a';
        }

        if(codigo1[b] > codigo2[b]) {
            return 'p';
        }
    }

    return 'i';
}

void conquistar(st_Container* saida, st_Container* vetor, int inicio, int meio, int fim) {
    int indexEsq = inicio;
    int indexDir = meio + 1;
    int indexSaida = inicio;

    while(indexEsq <= meio && indexDir <= fim) {
        if(compararCodigo(vetor[indexEsq].codigo, vetor[indexDir].codigo) != 'p') {
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

// Mergesort
void ordernarPorCodigo(st_Container* saida, st_Container* vetor, int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        ordernarPorCodigo(saida, vetor, inicio, meio);
        ordernarPorCodigo(saida, vetor, meio + 1, fim);

        conquistar(saida, vetor, inicio, meio, fim);
    }
}

int buscaBinariaCodigo(st_Container* vetor, int tamanhoVetor, char* codigo) {
    int min = 0;
    int max = tamanhoVetor - 1;
    int cursor;

    char resultado;

    while(min <= max) {
        cursor = min + (max - min) / 2;
        resultado = compararCodigo(codigo, vetor[cursor].codigo);

        if(resultado == 'i') {
            return cursor;
        }

        if(resultado == 'p') {
            min = cursor + 1;
        }
        else {
            max = cursor - 1;
        }
    }

    return -1;
}

int main(int argc, char** argv) {
    FILE* entrada = fopen(argv[1], "r");

    int numContainers = pegarNumeroContainers(entrada);
    int numChecagens = pegarNumeroChecagens(entrada, numContainers);

    st_Container checagens[numChecagens];
    st_Container* aux = malloc(sizeof(st_Container) * numChecagens);

    pegarContainers(entrada, checagens, numChecagens);
    ordernarPorCodigo(aux, checagens, 0, numChecagens - 1);

    return 0;
}