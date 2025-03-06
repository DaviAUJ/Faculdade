#include <stdint.h>
#include <stdio.h>

#define TAMDNA 30
#define DNA

#define PSTRING(var) printf("%s\n", var)
#define PINT(var) printf("%d\n", var)

#define PEGARUINT16(var) fscanf(arqEntrada, "%hu ", &var)
#define PEGARDNA(var) fscanf(arqEntrada, "%s ", var)

FILE* arqEntrada;
FILE* arqSaida;

int main(int argc, char** argv) {
    uint16_t subcadeia;
    char DNA[10000];

    arqEntrada = fopen(argv[1], "r");
    PEGARUINT16(subcadeia);
    PEGARDNA(DNA);
    

    //arqSaida = fopen(argv[2], "w");

    fclose(arqEntrada);
    //fclose(arqSaida);

    return 0;
}