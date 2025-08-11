#include <stdio.h>
#include <stdlib.h>

// Para eu poder usar uma constante para definir a matriz
// eu preciso usar esse método
// Isso acontece por algo muito técnico que ainda não entendo muito bem
#define N_MARCAS 6
#define N_ATRIBUTOS 4

typedef struct freezer {
    char nome[21];
    float capacidade;
    int garantia;
    float gasto;
    float temperaturaMinima;
} freezer;

freezer listaFreezers[N_MARCAS] = {
    // Marca, Capacidade, Duração da garantia, Gasto de energia, Temperatura minima
    {"Deia", 385, 12, 35.9, -28},
    {"Sul", 534, 12, 72.1, -18},
    {"Nsul", 309, 12, 46.2, -18},
    {"Frio", 546, 3, 74.3, -18},
    {"Fri", 503, 24, 78, -22},
    {"Lux", 477, 12, 90, -18},
};

void alterarDado(freezer* lista, int nFreezer, int nCarac, float novoValor) {
    // linha de cima para baixo, 0 até x
    // Coluna esquerda para direita 0 até y
    // x e y são a quantidade de linhas e colunas, respectivamente

    if(nFreezer > N_ATRIBUTOS || nFreezer < 0) { printf("Atributo nao existente!\n"); }
    else if(nCarac > N_MARCAS || nCarac < 0) { printf("Marca nao existente!\n"); }
    else {
        switch(nCarac) {
            case 0: lista[nFreezer].capacidade = novoValor; break;
            case 1: lista[nFreezer].garantia = novoValor; break;
            case 2: lista[nFreezer].gasto = novoValor; break;
            case 3: lista[nFreezer].temperaturaMinima = novoValor; break;
        }

        printf("Valor alterado com sucesso\n");
    }
}