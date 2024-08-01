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


int inicializa(noCabeca *cabeca) {
    cabeca->inicio = NULL;
    cabeca->fim = NULL;
    cabeca->quantidade = 0;

    return 1;
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


int removerDoInicio(noCabeca *cabeca) {
    no *noApagado = cabeca->inicio;

    if(noApagado == NULL) { return 0; }

    if(noApagado == cabeca->fim) { inicializa(cabeca); } // Caso onde tem apenas um único elemento na lista
    else {
        cabeca->inicio = noApagado->ponteiro;
        cabeca->quantidade--;
    }
    
    free(noApagado);

    return 1;
}


int removerDoFim(noCabeca *cabeca) {
    no *noApagado = cabeca->fim;
    no *noPrecedente;

    if(noApagado == NULL) { return 0; }

    if(cabeca->inicio == noApagado) { inicializa(cabeca); } // Caso onde tem um único elemento na lista
    else {
        // Achando o nó precedente
        noPrecedente = cabeca->inicio;
        while(noPrecedente->ponteiro != noApagado) { noPrecedente = noPrecedente->ponteiro; }

        noPrecedente->ponteiro = NULL;
        cabeca->fim = noPrecedente;
        cabeca->quantidade--;
    }
    
    free(noApagado);

    return 1;
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

    if(cabeca->inicio == 0) { return 0; }
    else if(cabeca->inicio == NULL) { printf("[ ]"); }
    noAtual = cabeca->inicio;

    printf("\nLista encadeada com cabeca: [ ");
    while(1) {
        printf("%d", noAtual->dado);
        noAtual = noAtual->ponteiro;

        if(noAtual == NULL) { printf(" ]"); break; } 

        printf(", "); // Esse esquema aqui é só para aparecer bonitinho
    }

    printf("\nNumero de elementos: %d\n", cabeca->quantidade);
    printf("Inicio: %d\n", cabeca->inicio->dado);
    printf("Fim: %d\n", cabeca->fim->dado);

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


int adicionarNoIndex(noCabeca *cabeca, int index, int valor) {
    no *novoNo, *noPrecedente;

    if(cabeca->inicio == NULL) { return 0; }

    // Caso o index dado não seja no meio da lista o novo nó vai para o inicio ou fim
    if(index <= 0) { adicionarNoInicio(cabeca, valor); }
    else if(index >= cabeca->quantidade - 1) { adicionarNoFim(cabeca, valor); }
    else {
        novoNo = (no*) malloc(sizeof(no));
        if(novoNo == NULL) { return 0; }

        noPrecedente = cabeca->inicio;
        for(int i = 0; i < index - 1; i++) { noPrecedente = noPrecedente->ponteiro; } // Pegando o nó anterior ao index escolhido

        novoNo->ponteiro = noPrecedente->ponteiro; 
        novoNo->dado = valor;
        noPrecedente->ponteiro = novoNo;
        cabeca->quantidade++;
    }

    return 1;
}


int removerDoIndex(noCabeca *cabeca, int index) {
    no *noPrecedente, *noApagado;

    if(cabeca->inicio == NULL) { return 0; }

    if(index <= 0) { removerDoInicio(cabeca); }
    else if(index >= cabeca->quantidade - 1) { removerDoFim(cabeca); }
    else{
        noPrecedente = cabeca->inicio;
        for(int i = 0; i < index - 1; i++) { noPrecedente = noPrecedente->ponteiro; } // Pegando o nó anterior ao index escolhido

        noApagado = noPrecedente->ponteiro;
        noPrecedente->ponteiro = noApagado->ponteiro;
        free(noApagado);

        cabeca->quantidade--;
    }
    
    return 1;
}


int main() {
    noCabeca cabeca;
    int entrada, resp, escolha, estaInicializado;

    printf("--- LISTA ENCADEADA ---");
    
    printf("\n\n");
    resp = exibeLista(&cabeca);
    if(!resp) { 
        if(estaInicializado) { printf("[ ]" ); }
        else { printf("Lista nao inicializada"); }
    }

    printf("\n\n1 - Inicializar lista");
    printf("\n2 - Adicionar nó");
    printf("\n3 - Remover nó");
    printf("\n4 - Apagar lista");
    printf("\n\nEscolha: ");
    scanf("%d", escolha);

    switch(escolha) {
    case 1: 
        printf("hey");
        estaInicializado = inicializa(&cabeca);
        break;
    }

    return 0;
}