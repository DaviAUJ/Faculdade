// Como pedido pela questão
// Eu encontrei este algoritmo chamado Merge Sort
// ele é recursivo, não foi usado na aula e é baseado no principio de dividir e conquistar

#include <stdio.h>

void mergeSort(int* vetor, int tamanho) {
    if(tamanho > 1) {
        int tamEsq = tamanho / 2, tamDir = tamanho / 2; if(tamanho % 2 == 1) { tamEsq++; }
        int vetorEsq[tamEsq], vetorDir[tamDir];

        // Transferindo os valores pros vetores menores
        for(int i = 0; i < tamEsq; i++) { vetorEsq[i] = vetor[i]; }
        for(int i = tamEsq; i < tamanho; i++) { vetorDir[i - tamEsq] = vetor[i]; }

        // Faz o processo nos vetores menores
        mergeSort(vetorEsq, tamEsq);
        mergeSort(vetorDir, tamDir);

        int indexEsq = 0, indexDir = 0, indexVetor = 0;

        while(indexEsq < tamEsq && indexDir < tamDir) {
            if(vetorEsq[indexEsq] < vetorDir[indexDir]) {
                vetor[indexVetor] = vetorEsq[indexEsq];
                indexEsq++;
                
            } else {
                vetor[indexVetor] = vetorDir[indexDir];
                indexDir++;
                
            }

            indexVetor++;
        }

        while(indexEsq < tamEsq) {
            vetor[indexVetor] = vetorEsq[indexEsq];
            indexEsq++;
            indexVetor++;
        }

        while(indexDir < tamDir) {
            vetor[indexVetor] = vetorDir[indexDir];
            indexDir++;
            indexVetor++;
        }
    }
}

int main() {
    system("cls");

    int tamanho;

    // tenta pegar um valor valido até conseguir
    while(1) {
        printf("Digite o tamanho do vetor: ");
        scanf("%d", &tamanho);

        if(tamanho > 1) { break; }

        printf("\nValor invalido(< 1)\n\n");
    }

    int lista[tamanho];

    printf("\n");
    for(int i = 0; i < tamanho; i++) {
        printf("Digite o valor inteiro #%d: ", i + 1);
        scanf("%d", &lista[i]);
    }

    printf("\nO vetor nao ordenado fica assim: ");
    for(int i = 0; i < tamanho; i++) { printf("%d ", lista[i]); }

    mergeSort(lista, tamanho);

    printf("\n\nO vetor quando ordenado fica assim: ");
    for(int i = 0; i < tamanho; i++) { printf("%d ", lista[i]); }
}