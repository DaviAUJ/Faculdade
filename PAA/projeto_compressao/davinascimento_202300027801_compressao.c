#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

FILE* entrada;
FILE* saida;

typedef struct string {
    char* string;
    int16_t tamanho;
} st_String;

st_String criarString(int16_t tamanho) {
    st_String saida;

    saida.string = (char*) malloc(sizeof(char) * (tamanho + 1));
    saida.string[tamanho] = '\0';
    saida.tamanho = tamanho;

    return saida;
}

int16_t pegarProxTam() {
    int16_t saida;

    fscanf(entrada, "%d ", &saida);

    return saida;
}

char pegarProxHex() {
    char saida;

    fscanf(entrada, "%X ", &saida);

    return saida;
}

st_String pegarLinha() {
    st_String saida;
    int16_t tamanho = pegarProxTam();

    saida = criarString(tamanho);

    for(int16_t a = 0; a < tamanho; a++) {
        saida.string[a] = pegarProxHex();
    }

    return saida;
}

int main(int argc, char** argv) {
    entrada = fopen(argv[1], "r");
    saida = fopen(argv[2], "w");



    return 0;
}