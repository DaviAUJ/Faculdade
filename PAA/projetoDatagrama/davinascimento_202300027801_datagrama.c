#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdbool.h>

typedef struct pacote {
    int32_t id;
    int32_t tamanho;
    int32_t* dados;
} st_Pacote;

typedef struct espera {
    st_Pacote* pacotes;
    int32_t tamanho;
    int32_t inicio;
    int32_t fim;
    int32_t menorId;
} st_Espera;

st_Pacote criarPacote(int32_t id, int32_t tamanho) {
    st_Pacote saida;

    saida.id = id;
    saida.tamanho = tamanho;
    saida.dados = (int32_t*) malloc(sizeof(int32_t) * tamanho);

    return saida;
}

void fecharPacote(st_Pacote pacote) {
    free(pacote.dados);
}

int32_t pegarProxInt(FILE* arquivo) {
    int32_t saida;

    fscanf(arquivo, "%d ", &saida);

    return saida;
}

int32_t pegarProxHex(FILE* arquivo) {
    int32_t saida;

    fscanf(arquivo, "%X ", &saida);

    return saida;
}

void colocarNaEspera(st_Espera* espera, st_Pacote pacote) {
    if(espera->inicio > 0 && espera->pacotes[espera->inicio].id >= pacote.id) {
        espera->pacotes[--espera->inicio] = pacote;
    }
    else {
        espera->pacotes[++espera->fim] = pacote;
    }

    if(pacote.id < espera->menorId) {
        espera->menorId = pacote.id;
    }
}

void printarPacote(FILE* arquivo, st_Pacote pacote) {
    for(int32_t r = 0; r < pacote.tamanho - 1; r++) {
        fprintf(arquivo, "%02X,", pacote.dados[r]);
    }

    fprintf(arquivo, "%02X|", pacote.dados[pacote.tamanho - 1]);

    free(pacote.dados);
}

void trocarPacote(st_Pacote* a, st_Pacote* b) {
    st_Pacote aux = *a;

    *a = *b;
    *b = aux;
}

int32_t acharFilhoEsq(int32_t index, int32_t inicio) {
    return 2 * index + 1 - inicio;
}

int32_t acharFilhoDir(int32_t index, int32_t inicio) {
    return 2 * (index + 1) - inicio;
}

void heapifyMax(st_Pacote* vetor, int32_t inicio, int32_t fim, int32_t index) {
    int32_t pai = index;
    int32_t filhoEsq = acharFilhoEsq(pai, inicio);
    int32_t filhoDir = acharFilhoDir(pai, inicio);

    if(filhoEsq <= fim && vetor[filhoEsq].id > vetor[pai].id) {
        pai = filhoEsq;
    }

    if(filhoDir <= fim && vetor[filhoDir].id > vetor[pai].id) {
        pai = filhoDir;
    }

    if(pai != index) {
        trocarPacote(&vetor[pai], &vetor[index]);
        heapifyMax(vetor, inicio, fim, pai);
    }
}

void construirHeapMax(st_Pacote* vetor, int32_t inicio, int32_t fim) {
    int32_t primeiro = (fim - inicio) / 2 + inicio;

    for(int32_t k = primeiro; k >= inicio; k--) {
        heapifyMax(vetor, inicio, fim, k);
    }
}

void heapsort(st_Pacote* vetor, int32_t inicio, int32_t fim) {
    construirHeapMax(vetor, inicio, fim);

    for(int32_t m = fim; m > inicio; m--) {
        trocarPacote(&vetor[inicio], &vetor[m]);

        heapifyMax(vetor, inicio, m - 1, inicio);
    }
}

int main(int argc, char** argv) {
    FILE* entrada = fopen(argv[1], "r");
    FILE* saida = fopen(argv[2], "w");
    
    int32_t totalPacotes = pegarProxInt(entrada);
    int32_t quantPacotes = pegarProxInt(entrada);
    int32_t proxId = 0;

    st_Espera lista;
    lista.tamanho = totalPacotes + (totalPacotes / 10);
    lista.inicio = totalPacotes / 10 + 1;
    lista.fim = lista.inicio - 1;
    lista.pacotes = malloc(sizeof(st_Pacote) * lista.tamanho);
    lista.pacotes[lista.inicio] = criarPacote(-1, 0);
    lista.menorId = totalPacotes;
    
    fprintf(saida, "|");
    bool printou = false;
    for(int32_t q = 1; q <= totalPacotes; q++) {
        int32_t idDaVez = pegarProxInt(entrada);
        int32_t tamDaVez = pegarProxInt(entrada);

        if(idDaVez == proxId) {
            for(int32_t w = 0; w < tamDaVez - 1; w++) {
                fprintf(saida, "%02X,", pegarProxHex(entrada));
            }

            fprintf(saida, "%02X|", pegarProxHex(entrada));

            proxId++;
            printou = true;
        }
        else {
            st_Pacote pacote = criarPacote(idDaVez, tamDaVez);

            for(int32_t w = 0; w < tamDaVez; w++) {
                pacote.dados[w] = pegarProxHex(entrada);
            }

            colocarNaEspera(&lista, pacote);
        }

        if(q % quantPacotes == 0 || q == totalPacotes) {
            if(lista.menorId == proxId) {
                while(proxId == lista.pacotes[lista.inicio].id) {
                    printarPacote(saida, lista.pacotes[lista.inicio]);
                    printou = true;
                    lista.inicio++;
                    proxId++;
                }

                heapsort(lista.pacotes, lista.inicio, lista.fim);

                while(proxId == lista.pacotes[lista.inicio].id) {
                    printarPacote(saida, lista.pacotes[lista.inicio]);
                    printou = true;
                    lista.inicio++;
                    proxId++;
                }

                lista.menorId = lista.pacotes[lista.inicio].id;
            }
            
            if(printou && q != totalPacotes) {
                fprintf(saida, "\n|");
                printou = false;
            }
        }
    }

    

    free(lista.pacotes);

    fclose(entrada);
    fclose(saida);
    return 0;
}