#include <stdio.h>
#include <stdlib.h>

// Para eu poder usar uma constante para definir a matriz
// eu preciso usar esse método
// Isso acontece por algo muito técnico que ainda não entendo muito bem
#define N_MARCAS 6
int Frz = -1, Crc = -1;

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

void SelecionaFreezer(freezer* lista, int* F) {
    int Op;

    printf("Selecione o freezer desejado:\n");
    printf("\n1 - Deia\n");
    printf("2 - Sul\n");
    printf("3 - NSul\n");
    printf("4 - Frio\n");
    printf("5 - Fri\n");
    printf("6 - Lux\n\n");

    printf("Opcao: ");
    scanf("%d", &Op);

    *F = Op - 1;
}

void SelecionaCaracteristica(freezer* lista, int* C) {
    int Op;

    printf("Caracteristica desejado\n");
    printf("\n1 - Capacidade (litros)\n");
    printf("2 - Garantia (meses)\n");
    printf("3 - Economia(kWh/mes)\n");
    printf("4 - Temperatura Minima (Celsius)\n");
    printf("\nOpcao: ");
    
    scanf("%d", &Op);

    *C = Op - 1;
}

void alterarDado(freezer* lista, int linha, int coluna, float novoValor) {
    // linha de cima para baixo, 0 até x
    // Coluna esquerda para direita 0 até y
    // x e y são a quantidade de linhas e colunas, respectivamente

    if(linha > N_ATRIBUTOS || linha < 0) { printf("Atributo nao existente!\n"); }
    else if(coluna > N_MARCAS || coluna < 0) { printf("Marca nao existente!\n"); }
    else {
        matriz[linha][coluna] = novoValor;

        printf("Valor alterado com sucesso\n");
    }
}
              
int main() {
    while(1) {
        int Op;
        float aux;

        system("cls");

        printf(">>> Pesquisa Freezer <<<\n\n");
        printf("Selecione a opcao desejada:\n");
        printf("1 - Exibir Levantamento\n");
        printf("2 - Dados de um Freezer\n");
        printf("3 - Dados de uma Caracteristica\n");
        printf("4 - Alterar Dado\n");
        printf("5 - Melhor Freezer em Capacidade\n");
        printf("6 - Melhor Freezer em Garantia\n");
        printf("7 - Melhor Freezer em Economia\n");
        printf("8 - Melhor Freezer em Temperatura\n");
        printf("9 - Sair\n");

        printf("\nOpcao: ");
        scanf("%d", &Op);

        system("cls");
        
        switch(Op) {
            case 1: ExibeMatriz(M, 4, 6);
                    break;

            case 2: SelecionaFreezer(M, &Frz);
                    ExibeColuna(M, 4, Frz);
                    break;

            case 3: SelecionaCaracteristica(M, &Crc);
                    ExibeLinha(M, Crc, 6);
                    break;

            case 4: SelecionaCaracteristica(M, &Crc);
                    printf("\n");
                    SelecionaFreezer(M, &Frz);
                    printf("\n");
            
                    printf("Novo valor: ");
                    scanf("%f", &aux);

                    alterarMatrizFloat(M, Crc, Frz, aux);
                    break; 

            case 5: melhorFreezer(M, 0); // Melhor freezer em capacidade
                    break;

            case 6: melhorFreezer(M, 1); // Melhor freezer em garantia
                    break;

            case 7: melhorFreezer(M, 2); // Melhor freezer em economia
                    break;

            case 8: melhorFreezer(M, 3); // Melhor freezer em temperatura
                    break;

            case 9: break;
        }

        if(Op == 9) { break; }
        else {
            printf("\n");
            system("pause");
        }
    }

    return 0;
}
