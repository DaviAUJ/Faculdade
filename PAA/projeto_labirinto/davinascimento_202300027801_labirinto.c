#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#define PSTRING(ptr) printf("%s\n", ptr)

char bufferEntrada[10000000];
char bufferSaida[10000000];
char* bufferPtr;

int main(int argc, char** argv) {
    int32_t n_Labirintos;
    int32_t n_Colunas;
    int32_t n_Linhas;

    FILE* arqEntrada = fopen(argv[1], "r");
    fread(bufferEntrada, sizeof(char), 10000000, arqEntrada);
    fclose(arqEntrada);

                

    return 0;
}