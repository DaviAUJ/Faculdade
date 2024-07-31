#include <stdio.h>
#include <stdlib.h>

typedef struct no{
    int dado;
    struct no *ponteiro;
} no;

int criarNoInicial(no **primeiro, no **ultimo, int valor) {
    no *noInicial = (no*) malloc(sizeof(no));

    if(noInicial == NULL) { return 0; } // Alocação falhou

    noInicial->dado = valor;
    noInicial->ponteiro = NULL;
    *primeiro = noInicial;
    *ultimo = noInicial;

    return 1; 
}

int adicionarNaFrente(no **primeiro, no **ultimo, int valor) {
    no *novoNo;

    if(*primeiro == NULL) { criarNoInicial(&primeiro, &ultimo, valor); }
    else {
        novoNo = (no*) malloc(sizeof(no));

        if(novoNo == NULL) { return 0; } // Alocação falhou

        novoNo->dado = valor;
        novoNo->ponteiro = *primeiro;
        *primeiro = novoNo;

        return 1;
    }
}

int exibirLista(no **primeiro) {
    no *noAtual;

    if(*primeiro == NULL) { return 0; }

    noAtual = *primeiro;

    printf("Lista encadeada: [ ");
    while(1) {
        printf("%d", noAtual->dado);
        noAtual = noAtual->ponteiro;

        if(noAtual == NULL) { break; }

        printf(", "); // Esse esquema aqui é só para aparecer a lista bonitinha
    }

    printf(" ]");

    return 1;
}

int main() {
    no *inicial = NULL, *final = NULL;
    int resp, entrada;

    system("cls");

    printf("Digite um valor: ");
    scanf("%d", &entrada);

    resp = criarNoInicial(&inicial, &final, entrada);
    if(!resp) { printf("Memoria nao alocada"); }

    while(resp) {
        printf("Digite outro valor: ");
        scanf(" %d", &entrada);
        adicionarNaFrente(&inicial, &final, entrada);

        printf("Adicionar outro elemento(S/N)? ");
        scanf(" %c", &entrada);
        printf("\n");

        if(entrada != 83 && entrada != 115) { resp = 0; }
    }

    resp = exibirLista(&inicial);
    if(resp == 0) { printf("Lista vazia"); }

    return 0;
}