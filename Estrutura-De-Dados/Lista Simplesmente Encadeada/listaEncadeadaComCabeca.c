// Davi Araújo

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


int exibeLista(noCabeca *cabeca, int detalhes) {
    no *noAtual;

    printf("\n\n");
    if(cabeca->inicio == NULL) { 
        printf("[ Lista vazia ]"); 
        return 0; 
    }
    noAtual = cabeca->inicio;

    printf("[ ");
    while(1) {
        printf("%d", noAtual->dado);
        noAtual = noAtual->ponteiro;

        if(noAtual == NULL) { break; } 

        printf(", "); // Esse esquema aqui é só para aparecer bonitinho
    }

    printf(" ]");
    if(detalhes) {
        printf("\n\nNumero de elementos: %d\n", cabeca->quantidade);
        printf("Inicio: %d\n", cabeca->inicio->dado);
        printf("Fim: %d\n", cabeca->fim->dado);
    }
    
    return 1;
}


// Função requerida na atividade
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


// Função requerida na atividade
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


// Função requerida na atividade
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


// Função requerida na atividade
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


// Função requerida na atividade
int adicionarNoIndex(noCabeca *cabeca, int index, int valor) {
    no *novoNo, *noPrecedente;

    if(cabeca->inicio == NULL) { criarNoInicial(cabeca, valor); }
    // Caso o index dado não seja no meio da lista o novo nó vai para o inicio ou fim
    else if(index <= 0) { adicionarNoInicio(cabeca, valor); }
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


// Função requerida na atividade
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


void t_Titulo(char *string) { printf("\n----- %s -----", string); }


void p_AdicionarNo(noCabeca *cabeca) {
    int valor, index, escolha;

    system("cls");
    t_Titulo("ADICIONAR NO");

    printf("\n\n1 - Adicionar no inicio da lista");
    printf("\n2 - Adicionar no fim da lista");
    printf("\n3 - Adicionar no index");
    
    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    printf("Valor: ");
    scanf("%d", &valor);

    switch(escolha) {
    case 1:
        adicionarNoInicio(cabeca, valor);
        break;
    case 2:
        adicionarNoFim(cabeca, valor);
        break;
    case 3:
        printf("Index: ");
        scanf("%d", &index);
        adicionarNoIndex(cabeca, index, valor);
        break;
    }

    printf("\nItem adicionado na lista\n\n");
    system("pause");
}


void p_RemoverNo(noCabeca *cabeca) {
    int index, escolha, deuCerto = 1;

    system("cls");
    t_Titulo("REMOVER NO");

    printf("\n\n1 - Remover no inicio da lista");
    printf("\n2 - Remover no fim da lista");
    printf("\n3 - Remover no index");

    printf("\n\nEscolha: ");
    scanf("%d", &escolha);

    switch(escolha) {
    case 1:
        deuCerto = removerDoInicio(cabeca);
        break;
    case 2:
        deuCerto = removerDoFim(cabeca);
        break;
    case 3:
        printf("Index: ");
        scanf("%d", &index);
        deuCerto = removerDoIndex(cabeca, index);
        break;
    }

    if(deuCerto) { printf("\nItem removido da lista\n\n"); }
    else { printf("\nItem não removido; Lista Vazia\n\n"); }
    system("pause");
}


void p_ApagarLista(noCabeca *cabeca) {
    char escolha;

    system("cls");
    t_Titulo("APAGAR LISTA");

    printf("\n\nTem certeza que quer apagar todos os itens da lista(S/N)? ");
    scanf(" %c", &escolha);

    if(escolha == 's' || escolha == 'S') { destruirLista(cabeca); }
    
    printf("\nLista apagada\n\n");
    system("pause");
}


void p_Detalhes(noCabeca *cabeca) {
    system("cls");
    t_Titulo("DETALHES");

    exibeLista(cabeca, 1);

    printf("\n");
    system("pause");
}


void p_BuscarValor(noCabeca *cabeca) {
    int valor, index;

    system("cls");
    t_Titulo("BUSCAR VALOR");

    printf("\n\nValor: ");
    scanf("%d", &valor);

    index = procurarValor(cabeca, valor);
    if(index == -1) { printf("\nEste valor nao foi encontrado na lista\n\n"); }
    else { printf("\nEste valor foi encontrado no index %d da lista\n\n", index); }

    system("pause");
}


int p_Sair() {
    char escolha;

    system("cls");
    t_Titulo("SAIDA");

    printf("\n\nDeseja sair(S/N)? ");
    scanf(" %c", &escolha);

    if(escolha == 's' || escolha == 'S') { return 0; }

    printf("\nPrograma nao encerrado\n\n");
    system("pause");
}


int main() {
    noCabeca cabeca;
    int entrada, resp, escolha, continuar = 1;

    inicializa(&cabeca);

    while(continuar) {
        system("cls");
        t_Titulo("LISTA ENCADEADA");

        exibeLista(&cabeca, 0);

        printf("\n\n1 - Adicionar no");
        printf("\n2 - Remover no");
        printf("\n3 - Apagar lista");
        printf("\n4 - Buscar valor");
        printf("\n5 - Detalhes");
        printf("\n6 - Sair");
        printf("\n\nEscolha: ");
        scanf("%d", &escolha);

        switch(escolha) {
        case 1: p_AdicionarNo(&cabeca); break;
        case 2: p_RemoverNo(&cabeca); break;
        case 3: p_ApagarLista(&cabeca); break;
        case 4: p_BuscarValor(&cabeca); break;
        case 5: p_Detalhes(&cabeca); break;
        case 6: continuar = p_Sair(); break;
        }
    }

    printf("\nPrograma encerrado");
    
    return 0;
}