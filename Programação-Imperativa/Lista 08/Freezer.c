#include <stdio.h>
#include <stdlib.h>

// Para eu poder usar uma constante para definir a matriz
// eu preciso usar esse método
// Isso acontece por algo muito técnico que ainda não entendo muito bem
#define N_MARCAS 6
#define N_ATRIBUTOS 4
int Frz = -1, Crc = -1;

float M[N_ATRIBUTOS][N_MARCAS] = {
    {385, 534, 309, 546, 503, 477},
    {12, 12, 12, 3, 24, 12},
    {35.9, 72.1, 46.2, 74.3, 78, 90},
    {-28, -18, -18, -18, -22, -18}
};


void ExibeMatriz(float Matriz[N_ATRIBUTOS][N_MARCAS], int L, int C) {
    printf("                      Deia   Sul  NSul  Frio   Fri   Lux \n");

    for(int i = 0; i < L; i++) {
        if(i == 0) printf("Capacidade (litros) ");
        if(i == 1) printf("Garantia (meses)    ");
        if(i == 2) printf("Economia (KWh/mes)  ");
        if(i == 3) printf("Temperatura Min (C) "); 

        for(int j = 0; j < C; j++) { printf("%6.1f", Matriz[i][j]); }

        printf("\n");
    }
}

void ExibeColuna(float Matriz[N_ATRIBUTOS][N_MARCAS], int L, int C) {
    for(int i = 0; i < L; i++){
        if(i == 0) printf("\nCapacidade (litros) ");
        if(i == 1) printf("Garantia (meses)    ");
        if(i == 2) printf("Economia (KWh/mes)  ");
        if(i == 3) printf("Temperatura Min (C) ");

        printf("%6.1f\n", Matriz[i][C]);
    }
}

void ExibeLinha(float Matriz[N_ATRIBUTOS][N_MARCAS], int L, int C) {
    printf("\nDeia   Sul  NSul  Frio   Fri   Lux \n");

    for(int i = 0; i < C; i++) { printf("%.1f ", Matriz[L][i]); }

    printf("\n");
}

void SelecionaFreezer(float Matriz[N_ATRIBUTOS][N_MARCAS], int* F) {
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

void SelecionaCaracteristica(float Matriz[N_ATRIBUTOS][N_MARCAS], int* C) {
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

void alterarMatrizFloat(float matriz[N_ATRIBUTOS][N_MARCAS], int linha, int coluna, float novoValor) {
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

// Retorna o index do maior valor do vetor
int maiorValorVetorFloatIndex(float* vetor, int tamanho) {
    float temp = vetor[0];
    int output;

    for(int i = 1; i < tamanho; i++) {
        if(temp < vetor[i]) { output = i; }
    }

    return output;
}

// Retorna o index do menor valor do vetor
int menorValorVetorFloatIndex(float* vetor, int tamanho) {
    float temp = vetor[0];
    int output;

    for(int i = 1; i < tamanho; i++) {
        if(temp > vetor[i]) { output = i; }
    }

    return output;
}

void melhorFreezer(float matriz[N_ATRIBUTOS][N_MARCAS], int indexAtributo) {
    int index;

    // Caso seja o vetor do gasto de energia mensal ou temperatura ele precisa achar o menor valor
    if(indexAtributo == 2 || indexAtributo == 3) { index = menorValorVetorFloatIndex(matriz[indexAtributo], N_MARCAS); } 
    else { index = maiorValorVetorFloatIndex(matriz[indexAtributo], N_MARCAS); }

    // Montando a frase para ser exibida
    printf("O freezer da marca ");
    switch(index) {
        case 0: printf("Deia"); break;

        case 1: printf("Sul"); break;

        case 2: printf("NSul"); break;

        case 3: printf("Frio"); break;

        case 4: printf("Fri"); break;

        case 5: printf("Lux"); break;
    }
    printf(" tem a ");
    switch(indexAtributo) {
        case 0: printf("maior capacidade(%.2f L)", matriz[indexAtributo][index]); break;

        case 1: printf("garantia mais longa(%.0f meses)", matriz[indexAtributo][index]); break;

        case 2: printf("melhor eficiencia(%.2f KWh/mes)", matriz[indexAtributo][index]); break;

        case 3: printf("menor temperatura minima(%.2f C)", matriz[indexAtributo][index]); break;
    }
    printf("\n\n");
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
