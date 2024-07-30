#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no ponteiro;
} no;

typedef struct noCabeca {
    no *inicio;
    no *fim;
    int quantidade;
} noCabeca;

void inicializa(noCabeca *cabeca) {
    cabeca->inicio = NULL;
    cabeca->fim = NULL;
    cabeca->quantidade = 0;
}

int criarNoInicial(noCabeca *cabeca, int valor) {
    no *noInicial = (no*) malloc(sizeof(no));

    if(noInicial == NULL) { return 0; }

    noInicial->dado = valor;
    noInicial->ponteiro = NULL;
    cabeca->inicio = noInicial;
    cabeca->fim = noInicial;
    cabeca->quantidade++;
}

int main() {
    
    
    return 0;
}