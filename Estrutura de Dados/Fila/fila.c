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
} st_Fila;


void inicializarFila(st_Fila *novaFila, int capacidade) {
    novaFila->musicas = (st_Musica*) malloc(sizeof(st_Musica) * capacidade);
    if(novaFila->musicas == NULL) { return; }

    novaFila->capacidade = capacidade;
    novaFila->inicio = 0;
    novaFila->fim = -1;
}


void inserir(st_Fila *fila, st_Musica novaMusica) {
    // Quando o fim da fila chega no fim do array seu valor volta a ser -1 para
    // o ++ botar ele no começo do array
    if(fila->fim == fila->capacidade - 1) { fila->fim = -1; }

    fila->fim++;
    fila->musicas[fila->fim] = novaMusica;
}


st_Musica remover(st_Fila *fila) {
    st_Musica saida = fila->musicas[fila->inicio];
    fila->inicio++;

    if(fila->inicio == fila->capacidade) { fila->inicio = 0; }

    return saida;
}


int main() {

}