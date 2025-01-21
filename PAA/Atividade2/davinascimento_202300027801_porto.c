#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct container {
    char codigo[12];
    char cnpj[19];
    int peso;
    int ordem;
} st_Container;

int pegarNumeroContainers(FILE* arquivo) {
    char numero[7];
    int saida;

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
        container.ordem = a;

        destino[a] = container;
    }
}

st_Container* ordernarPorCodigo(st_Container* original) {

}

int main(int argc, char** argv) {
    FILE* entrada = fopen(argv[1], "r");

    int numContainers = pegarNumeroContainers(entrada);
    st_Container containers[numContainers];

    pegarContainers(entrada, containers, numContainers);
    

    fclose(entrada);

    return 0;
}