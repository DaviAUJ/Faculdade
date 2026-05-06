#include <stdio.h>
#include <stdlib.h>

#define TAMSTR 32

typedef struct musica {
    char nome[TAMSTR];
    char banda[TAMSTR];
} st_Musica;

typedef struct fila {
    st_Musica *musicas;
    int capacidade;
    int inicio;
    int fim;
    int quantidade;
} st_Fila;


void inicializarFila(st_Fila *novaFila, int capacidade) {
    novaFila->musicas = (st_Musica*) malloc(sizeof(st_Musica) * capacidade);
    if(novaFila->musicas == NULL) { return; }

    novaFila->capacidade = capacidade;
    novaFila->inicio = 0;
    novaFila->fim = 0;
    novaFila->quantidade = 0;
}


void inserir(st_Fila *fila, st_Musica novaMusica) {
    if(fila->fim == fila->capacidade) { fila->fim = 0; }
    
    fila->musicas[fila->fim] = novaMusica;
    fila->fim++;
    fila->quantidade++;
}


st_Musica remover(st_Fila *fila) {
    st_Musica saida = fila->musicas[fila->inicio];
    fila->inicio++;

    if(fila->inicio == fila->capacidade) { fila->inicio = 0; }

    fila->quantidade--;
    return saida;
}


int estaVazia(st_Fila *fila) {
    return !fila->quantidade;
}


int estaCheia(st_Fila *fila) {
    return fila->quantidade == fila->capacidade;
}

int mostrarPrimeiro(st_Fila *fila) {
    if(fila->quantidade) {
        printf("\n\nMusica tocando agora");
        printf("\nNome: %s", fila->musicas[fila->inicio].nome);
        printf("\nBanda: %s", fila->musicas[fila->inicio].banda);
    }
    else { printf("\n\nNada esta tocando agora"); }
}


void t_Titulo(char *string) { printf("\n----- %s -----", string); }


void p_PularMusica(st_Fila *fila) {
    st_Musica musica;

    system("cls");
    t_Titulo("PULAR MUSICA");

    if(!fila->quantidade) {
        printf("\n\na musica nao foi pulada, nenhuma musica na fila");
    }
    else {
        musica = remover(fila);

        printf("\n\n%s - %s retirado da fila", musica.banda, musica.nome);
    }

    printf("\n\n");
    system("pause");
}


void p_AdicionarMusica(st_Fila *fila) {
    char escolha = 's';
    st_Musica musica;

    system("cls");
    t_Titulo("ADICIONAR MUSICA");

    // Se estiver cheio
    if(fila->capacidade == fila->quantidade) {
        printf("\n\nFila cheia");
        escolha = 'n';
    }
    
    while(escolha == 's' || escolha == 'S') {
        printf("\n\nNome: ");
        scanf(" %[^\n]s", &musica.nome);

        printf("Banda: ");
        scanf(" %[^\n]s", &musica.banda);

        inserir(fila, musica);
        printf("\n%s - %s adicionado na fila", musica.banda, musica.nome);

        printf("\n\nAdicionar mais uma musica(s/n)? ");
        scanf(" %c", &escolha);

        // Se agora estiver cheio
        if(fila->capacidade == fila->quantidade) {
            printf("\nFila cheia");
            escolha = 'n';
        }
    }

    printf("\n\n");
    system("pause");
}


void p_VerFila(st_Fila *fila) {
    int cursor = fila->inicio;
    
    system("cls");
    t_Titulo("VISUALIZAR VILA");

    if(!fila->quantidade) {  printf("\n\nLista vazia"); }

    for(int i = 0; i < fila->quantidade; i++) {
        printf("\n\n%d.", i + 1);
        printf("\nNome: %s", fila->musicas[cursor].nome);
        printf("\nBanda: %s", fila->musicas[cursor].banda);

        cursor++;
        if(fila->capacidade == cursor) { cursor = 0; }
    }

    printf("\n\n");
    system("pause");
}


int main() {
    st_Fila fila;
    int escolha, sair = 0;

    inicializarFila(&fila, 3);

    while(!sair) {
        system("cls");
        t_Titulo("BEM-VINDO AO EDIFY");

        mostrarPrimeiro(&fila);

        printf("\n\n1 - Pular a musica atual");
        printf("\n2 - Adicionar musicas na fila");
        printf("\n3 - Ver fila de musicas");

        printf("\n\nEscolha: ");
        scanf("%d", &escolha);

        switch(escolha) {
        case 1: p_PularMusica(&fila); break;
        case 2: p_AdicionarMusica(&fila); break;
        case 3: p_VerFila(&fila); break;
        case 4: sair = 1; break;

        default: printf("Opcao errada. Tente novamente"); system("pause");
        }
    }

    printf("Ate a proxima!");
    printf("Desligando...");
}