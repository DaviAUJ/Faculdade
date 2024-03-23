#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

int inverter01(int entrada) {
    if(entrada == 1) { return 0; }
    if(entrada == 0) { return 1; }

    return entrada;
}

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

int bbinaria (char* chave, int inicio, int fim, char vetor[][11]) {
    if (fim < inicio) { return -1; }
    else {
        int meio = (inicio + fim) / 2;

        if(compararStringSM(vetor[meio], chave, '=')) { return meio; }
        else{
            if(compararStringSM(vetor[meio], chave, '<')) { return bbinaria(chave, meio+1, fim, vetor); }
            else { return bbinaria(chave, inicio, meio-1, vetor); }
        }
    }
}

int main() {
    // Sem entrada de dados pois a questão pede apenas para ajustar a busca binaria

    char listaCompras[6][11] = {"Abacaxi", "Amaciante", "Carne", "Guarana", "Sal", "Tomate"};

    int index = bbinaria("Tomate", 0, 5, listaCompras);

    system("cls");

    printf("%d", index);
}