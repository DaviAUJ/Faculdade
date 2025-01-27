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
} st_Espera;

st_Pacote criarPacote(int32_t id, int32_t tamanho) {
    st_Pacote saida;

    saida.id = id;
    saida.tamanho = tamanho;
    saida.dados = (int32_t*) malloc(sizeof(int32_t) * tamanho);

    return saida;
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

void colocarNaEspera(st_Espera espera, st_Pacote pacote) {
    if(espera.inicio > 0 && espera.pacotes[espera.inicio].id >= pacote.id) {
        espera.pacotes[--espera.inicio] = pacote;
    }
    else {
        espera.pacotes[++espera.fim] = pacote;
    }
}

void printarPacote(FILE* arquivo, st_Pacote pacote) {
    for(int r = 0; r < pacote.tamanho; r++) {
        fprintf(arquivo, "%X,", pacote.dados[r]);
    }

    fprintf(arquivo, "%X|", pacote.dados[pacote.tamanho - 1]);
}

void con

void heapsort() {

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
    
    fprintf(saida, "|");
    for(int32_t q = 1; q <= totalPacotes; q++) {
        int32_t idDaVez = pegarProxInt(entrada);
        int32_t tamDaVez = pegarProxInt(entrada);
        
        if(idDaVez == proxId) {
            for(int32_t w = 0; w < tamDaVez - 1; w++) {
                fprintf(saida, "%X,", pegarProxHex(entrada));
            }

            fprintf(saida, "%X|", pegarProxHex(entrada));

            proxId++;
        }
        else {
            st_Pacote pacote = criarPacote(idDaVez, tamDaVez);

            for(int32_t w = 0; w < tamDaVez; w++) {
                pacote.dados[w] = pegarProxHex(entrada);
            }

            colocarNaEspera(lista, pacote);
        }

        if(q % quantPacotes == 0) {
            while(proxId == lista.pacotes[lista.inicio].id) {
                printarPacote(saida, lista.pacotes[lista.inicio]);
                lista.inicio++;
                proxId++;
            }

            fprintf(entrada, "\n|");
        }

        
    }


    fclose(entrada);
    fclose(saida);
    return 0;
}