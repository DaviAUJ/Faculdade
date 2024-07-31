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


int adicionarNoInicio(noCabeca *cabeca, int valor) {
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


int adicionarNoFim(noCabeca *cabeca, int valor) {
    no *novoNo;

    if(cabeca->inicio == NULL) { criarNoInicial(cabeca, valor); }
    else {
        novoNo = (no*) malloc(sizeof(no));

        if(novoNo == NULL) { return 0; }

        novoNo->dado = valor;
        novoNo->ponteiro = NULL;
        cabeca->fim->ponteiro = novoNo; // Altera o ponteiro do antigo fim da lista
        cabeca->fim = novoNo;
        cabeca->quantidade++;

        return 1;
    }
}


int destruirLista(noCabeca *cabeca) {
    no *noAtual, *noSeguinte;

    // Caso onde não existe nenhum elemento na lista
    if(cabeca->inicio == NULL) { return 0; }
    
    // Caso onde lista tem apenas um nó
    if(cabeca->inicio->ponteiro == NULL) { free(cabeca->inicio); }
    else {
        // Caso onde lista tem dois ou mais nós
        noAtual = cabeca->inicio;
        noSeguinte = cabeca->inicio->ponteiro;
    
        while(noSeguinte != NULL) {
            free(noAtual);
            noAtual = noSeguinte;
            noSeguinte = noSeguinte->ponteiro;
        }

        free(noAtual); // Libera mais uma vez pois o while deixa faltando um espaço de memória sobrando
    }

    // nó cabeça é reinicializado pois agora ele não está atrelado a nenhuma lista encadeada
    inicializa(cabeca);
    return 1;
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
    printf("\nNumero de elementos: %d", cabeca->quantidade);

    return 1;
}


int procurarValor(noCabeca *cabeca, int valor) {
    no *noAtual;
    int index = 0, sair = 0;

    if(cabeca->inicio == NULL) { return -1; }
    noAtual = cabeca->inicio;

    while(!sair) {
        if(noAtual == NULL) { 
            sair = 1; 
            index = -1; 
        } 
        else if(noAtual->dado == valor) { sair = 1; } 
        else {
            noAtual = noAtual->ponteiro;
            index++;
        } 
    }

    return index;
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
        adicionarNoFim(&cabeca, entrada);

        printf("Adicionar outro elemento(S/N)? ");
        scanf(" %c", &entrada);
        printf("\n");

        if(entrada != 83 && entrada != 115) { resp = 0; }
    }

    resp = exibeLista(&cabeca);
    if(!resp) { printf("Lista vazia"); }

    printf("\n%d", NULL == 20);

    return 0;
}