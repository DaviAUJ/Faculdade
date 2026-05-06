#include <stdio.h>
#include <stdlib.h>
#include <math.h>

typedef struct container {
    char codigo[12];
    char cnpj[19];
    int peso;
} st_Container;

typedef struct deltaPeso {
    char codigo[12];
    int diferenca;
    short int porcentagem;
} st_DeltaPeso;

int pegarNumeroContainers(FILE* arquivo) {
    int saida;
    
    fscanf(arquivo, "%d ", &saida);

    return saida;
}

int pegarNumeroChecagens(FILE* arquivo, int numContainers) {
    int saida;
    
    fseek(arquivo, numContainers * 37 - 1, SEEK_CUR);
    fscanf(arquivo, "%d ", &saida);

    return saida;
}

st_Container pegarUmContainer(FILE* arquivo) {
    char infos[38];
    st_Container container;

    fgets(infos, 38, arquivo);
    sscanf(infos, "%s %s %d", container.codigo, container.cnpj, &container.peso);

    return container;
}

void pegarContainers(FILE* arquivo, st_Container* destino, int quantidade) {
    char infos[38];
    st_Container container;

    for(int a = 0; a < quantidade; a++) {
        fgets(infos, 38, arquivo);
        sscanf(infos, "%s %s %d", container.codigo, container.cnpj, &container.peso);

        destino[a] = container;
    }
}

void copiarCodigo(char* deste, char* para) {
    for(int f = 0; f < 12; f++) {
        para[f] = deste[f];
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

char compararCNPJ(char* cnpj1, char* cnpj2) {
    for(int e = 0; e < 18; e++) {
        if(cnpj1[e] < cnpj2[e]) {
            return 'a';
        }

        if(cnpj1[e] > cnpj2[e]) {
            return 'p';
        }
    }

    return 'i';
}

void conquistarPorCodigo(st_Container* saida, st_Container* vetor, int inicio, int meio, int fim) {
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

        conquistarPorCodigo(saida, vetor, inicio, meio, fim);
    }
}

void conquistarPorPorcentagem(st_DeltaPeso* saida, st_DeltaPeso* vetor, int inicio, int meio, int fim) {
    int indexEsq = meio + 1;
    int indexDir = inicio;
    int indexSaida = inicio;

    while(indexEsq <= fim && indexDir <= meio) {
        if(vetor[indexEsq].porcentagem <= vetor[indexDir].porcentagem) {
            saida[indexSaida] = vetor[indexEsq];
            indexEsq++;
        }
        else {
            saida[indexSaida] = vetor[indexDir];
            indexDir++;
        }

        indexSaida++;
    }

    while(indexEsq <= fim) {
        saida[indexSaida] = vetor[indexEsq];
        indexSaida++;
        indexEsq++;
    }

    while(indexDir <= meio) {
        saida[indexSaida] = vetor[indexDir];
        indexSaida++;
        indexDir++;
    }

    for(int c = inicio; c <= fim; c++) {
        vetor[c] = saida[c];
    }
}

// Mergesort
void ordernarPorPorcentagem(st_DeltaPeso* saida, st_DeltaPeso* vetor, int inicio, int fim) {
    if(inicio < fim) {
        int meio = inicio + (fim - inicio) / 2;

        ordernarPorPorcentagem(saida, vetor, inicio, meio);
        ordernarPorPorcentagem(saida, vetor, meio + 1, fim);

        conquistarPorPorcentagem(saida, vetor, inicio, meio, fim);
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
    FILE* saida = fopen(argv[2], "w");

    int numListagens = pegarNumeroContainers(entrada);
    int numChecagens = pegarNumeroChecagens(entrada, numListagens);

    printf("%d - %d", numListagens, numChecagens);

    st_Container checagens[numChecagens];
    st_DeltaPeso pesosDiferentes[numChecagens];

    pegarContainers(entrada, checagens, numChecagens);

    st_Container* aux = malloc(sizeof(st_Container) * numChecagens);
    ordernarPorCodigo(aux, checagens, 0, numChecagens - 1);
    free(aux);

    fseek(entrada, 0, SEEK_SET);
    pegarNumeroContainers(entrada); // gambiarra

    int indexPeso = 0;

    for(int d = 0; d < numListagens; d++) {
        st_Container iterador = pegarUmContainer(entrada);
        int index = buscaBinariaCodigo(checagens, numChecagens, iterador.codigo);
        
        if(index != -1) {
            if(compararCNPJ(checagens[index].cnpj, iterador.cnpj) != 'i') {
                fprintf(saida, "%s:%s<->%s\n", iterador.codigo, iterador.cnpj, checagens[index].cnpj);
            }
            else if(checagens[index].peso != iterador.peso) {
                st_DeltaPeso temp;

                copiarCodigo(checagens[index].codigo, temp.codigo);
                temp.diferenca = abs(checagens[index].peso - iterador.peso);
                temp.porcentagem = roundf((temp.diferenca * 100.0) / (float)iterador.peso);

                if(temp.porcentagem > 10) {
                    pesosDiferentes[indexPeso] = temp;
                    indexPeso++;
                }
            }
        }
    }

    st_DeltaPeso* aux2 = (st_DeltaPeso*)malloc(sizeof(st_DeltaPeso) * (indexPeso + 1));
    ordernarPorPorcentagem(aux2, pesosDiferentes, 0, indexPeso);
    free(aux2);

    for(int g = indexPeso; g > 1; g--) {
        fprintf(saida, "%s:%dkg(%d%%)\n", pesosDiferentes[g].codigo, pesosDiferentes[g].diferenca, pesosDiferentes[g].porcentagem);
    }

    fprintf(saida, "%s:%dkg(%d%%)", pesosDiferentes[1].codigo, pesosDiferentes[1].diferenca, pesosDiferentes[1].porcentagem);

    fclose(entrada);
    fclose(saida);
    
    return 0;
}