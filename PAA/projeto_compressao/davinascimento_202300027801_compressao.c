#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

FILE* arqEntrada;
FILE* arqSaida;

typedef struct string {
    uint8_t* string;
    uint16_t tamanho;
} st_String;

st_String criarString(int16_t tamanho) {
    st_String saida;

    saida.string = (uint8_t*) malloc(sizeof(uint8_t) * (tamanho + 1));
    saida.string[tamanho] = '\0';
    saida.tamanho = tamanho;

    return saida;
}

uint16_t pegarProxTam() {
    uint16_t saida;

    fscanf(arqEntrada, "%hu ", &saida);

    return saida;
}

uint8_t pegarProxHex() {
    uint8_t saida;

    fscanf(arqEntrada, "%X ", &saida);

    return saida;
}

st_String pegarLinha() {
    st_String saida;
    uint16_t tamanho = pegarProxTam();

    saida = criarString(tamanho);

    for(uint16_t a = 0; a < tamanho; a++) {
        saida.string[a] = pegarProxHex();
    }

    return saida;
}

void printarLinha(st_String string) {
    for(int c = 0; c < string.tamanho; c++) {
        fprintf(arqSaida, "%02X", string.string[c]);
    }
}

st_String RLF(st_String string) {
    uint8_t* stringComprimida = (uint8_t*) malloc(sizeof(uint8_t) * (string.tamanho + 1));
    stringComprimida[string.tamanho] = '\0';

    uint16_t indexCompressao = 0;
    uint8_t repeticoes = 1;
    uint8_t referencia = string.string[0];

    for(uint16_t b = 1; b < string.tamanho + 1; b++) {
        if(string.string[b] == referencia && repeticoes < UINT8_MAX) {
            repeticoes++;
        }
        else {
            stringComprimida[indexCompressao++] = repeticoes;
            stringComprimida[indexCompressao++] = referencia;

            repeticoes = 1;
            referencia = string.string[b];
        }
    }

    st_String saida;
    saida.tamanho = indexCompressao;
    realloc(stringComprimida, sizeof(uint8_t) * (saida.tamanho + 1));
    stringComprimida[saida.tamanho] = '\0';
    saida.string = stringComprimida;

    return saida;
}

st_String Huffman(st_String string) {

}

int main(int argc, char** argv) {
    arqEntrada = fopen(argv[1], "r");
    arqSaida = fopen(argv[2], "w");

    uint32_t linhas;
    fscanf(arqEntrada, "%d", &linhas);

    st_String teste = pegarLinha();
    st_String testesaida = RLF(teste);

    printarLinha(testesaida);

    return 0;
}