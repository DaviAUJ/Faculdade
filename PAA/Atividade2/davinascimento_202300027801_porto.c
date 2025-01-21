#include <stdio.h>

#define tamCodigo 12
#define tamCNPJ 19

typedef struct container {
    unsigned long long int codigo;
    char cnpj[tamCNPJ];
    int peso;
    int ordem;
} st_Container;

int pegarNumeroContainers(FILE* arquivo) {
    char numero[6];
    int saida;

    fgets(numero, 7, arquivo);
    sscanf(numero, "%d", &saida);

    return saida;
}

void pegarContainers(FILE* arquivo, st_Container* destino, int quantidade) {
    for(int a = 0; a < quantidade; a++) {

    }
}

int main(int argc, char** argv) {
    FILE* entrada = fopen(argv[1], "r");
    FILE* saida = fopen(argv[2], "A");

    int numContainers = pegarNumeroContainers(entrada);
    int numVerificoes;
    
    
    
    // fgets()
    // sscanf()
    // fprintf()

    return 0;
}