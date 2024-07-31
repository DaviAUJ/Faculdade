#include <stdio.h>
#include <stdlib.h>

typedef struct no {
    int dado;
    struct no *ponteiro;
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

    return 1;
}

int adicionarNaFrente(noCabeca *cabeca, int valor) {
    no *novoNo;

    if(cabeca->inicio == NULL) { criarNoInicial(cabeca, valor); }
    else {
        novoNo = (no*) malloc(sizeof(no));

        if(novoNo == NULL) { return 0; }

        novoNo->dado = valor;
        novoNo->ponteiro = cabeca->inicio;
        cabeca->inicio = novoNo;
        cabeca->quantidade++;

        return 1;
    }
}

int exibeLista(noCabeca *cabeca) {
    no *noAtual;

    if(cabeca->inicio == NULL) { return 0; }
    noAtual = cabeca->inicio;

    printf("Lista encadeada com cabeca: [ ");
    while(1) {
        printf("%d", noAtual->dado);
        noAtual = noAtual->ponteiro;

        if(noAtual == NULL) { break; }

        printf(", "); // Esse esquema aqui é só para aparecer bonitinho
    }

    printf(" ]");

    return 1;
}

int main() {
    noCabeca cabeca;
    int entrada, resp;

    inicializa(&cabeca);  

    printf("Digite um valor: ");
    scanf("%d", &entrada);

    resp = criarNoInicial(&cabeca, entrada);
    if(!resp) { printf("Memoria nao alocada"); }
    
    while(resp) {
        printf("Digite outro valor: ");
        scanf("%d", &entrada);
        adicionarNaFrente(&cabeca, entrada);

        printf("Adicionar outro elemento(S/N)? ");
        scanf(" %c", &entrada);
        printf("\n");

        if(entrada != 83 && entrada != 115) { resp = 0; }
    }

    resp = exibeLista(&cabeca);
    if(resp == 0) { printf("Lista vazia"); }

    return 0;
}