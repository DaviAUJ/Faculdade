#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define tamanho 25
#define tamMaxString 21

// Palavras pegas num gerador de palavras
char lista[tamanho][tamMaxString] = {
    "mosquito", "lamente", "ir", "protesto", "oferta",
    "tecido", "cavalheiro", "rasteira", "infinito", "locomotiva",
    "ciclone", "esquilo", "irmos", "funeral", "pronunciar",
    "casal", "assustar", "consumir", "esquilo", "robin",
    "camisola", "esquilo", "alavanca", "inspecionar", "falsificar"
};

// Função retirada do Exercício 2
int inverter01(int entrada) {
    if(entrada == 1) { return 0; }
    if(entrada == 0) { return 1; }

    return entrada;
}

// Função retirada do Exercício 2
int compararStringSM(char* str1, char* str2, char operacao) {
    // SM - sem maiuscula - não leva em conta se as letras estão maiusculas ou não
    // operação pode ser >, <, =
    // > - comparar para ver se na ordem alfabetica str1 é maior que str2
    // < - comparar para ver se na ordem alfabetica str1 é menor que str2
    // = - compara se str1 é igual a str2
    
    int tam1 = strlen(str1), tam2 = strlen(str2);
    char charAux1, charAux2;

    if(operacao == '=') {
        if(tam1 != tam2) { return 0; }

        for(int i = 0; i <= tam1; i++) {
            charAux1 = tolower(str1[i]);
            charAux2 = tolower(str2[i]);

            if(charAux1 != charAux2) { return 0; }
        }

        return 1;

    } else {
        // Operação padrão >, caso seja < basta inverter o 0 ou 1 no final
        
        int tamMenorPalavra = tam1; if(tam2 < tam1) { tamMenorPalavra = tam2; }
        int output;

        // procura pelo primeiro caracter não correspondente nas duas strings
        for(int i = 0; i < tamMenorPalavra; i++) {
            charAux1 = tolower(str1[i]);
            charAux2 = tolower(str2[i]);

            if(charAux1 != charAux2) {
                if(charAux1 > charAux2) { output = 1; }
                else { output = 0; }

                if(operacao == '<') { output = inverter01(output); }
                return output;
            }
        }

        // Caso str1 esteja contido dentro de str2 então str2 fica como a frente na ordem alfabetica
        output = 0;

        // Inverter se a operação for '<'
        if(operacao == '<') { output = inverter01(output); }
        return output;
    }
}

// A função aqui funciona do mesmo jeito
// Apenas troquei as comparações de número pela minha função de comparação de string
// e troquei as assossiações por strcpy()
void mergeSortStr(char vetor[tamanho][tamMaxString], int tamanhoVetor) {
    if(tamanhoVetor > 1) {
        int tamEsq = tamanhoVetor / 2, tamDir = tamanhoVetor / 2; if(tamanhoVetor % 2 == 1) { tamEsq++; }
        char vetorEsq[tamEsq][tamMaxString], vetorDir[tamDir][tamMaxString];

        // Transferindo os valores pros vetores menores
        for(int i = 0; i < tamEsq; i++) { strcpy(vetorEsq[i], vetor[i]); }
        for(int i = tamEsq; i < tamanhoVetor; i++) { strcpy(vetorDir[i - tamEsq], vetor[i]); }

        // Faz o processo nos vetores menores
        mergeSortStr(vetorEsq, tamEsq);
        mergeSortStr(vetorDir, tamDir);

        int indexEsq = 0, indexDir = 0, indexVetor = 0;

        while(indexEsq < tamEsq && indexDir < tamDir) {
            if(compararStringSM(vetorEsq[indexEsq], vetorDir[indexDir], '<')) {
                strcpy(vetor[indexVetor], vetorEsq[indexEsq]);
                indexEsq++;
                
            } else {
                strcpy(vetor[indexVetor], vetorDir[indexDir]);
                indexDir++;
                
            }

            indexVetor++;
        }

        while(indexEsq < tamEsq) {
            strcpy(vetor[indexVetor], vetorEsq[indexEsq]);
            indexEsq++;
            indexVetor++;
        }

        while(indexDir < tamDir) {
            strcpy(vetor[indexVetor], vetorDir[indexDir]);
            indexDir++;
            indexVetor++;
        }
    }
}

int main() {
    system("cls");

    printf("O vetor nao ordenado fica assim: \n\n");
    for(int i = 0; i < tamanho; i++) { printf("%d - %s\n", i + 1, lista[i]); }

    mergeSortStr(lista, tamanho);

    printf("\n\nO vetor quando ordenado fica assim: \n\n");
    for(int i = 0; i < tamanho; i++) { printf("%d - %s\n", i + 1, lista[i]); }
}
