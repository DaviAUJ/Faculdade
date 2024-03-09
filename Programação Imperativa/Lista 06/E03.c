#include <stdio.h>
#include <ctype.h>

int contVogais(char* str) {
    int passo = 0, vogais = 0;
    char charDaVez;

    while(str[passo] != '\0') {
        charDaVez = tolower(str[passo]); // é necessário para não ter confusão entre maisculas e minusculas

        if(charDaVez == 'a' || charDaVez == 'e' || charDaVez == 'i' || charDaVez == 'o' || charDaVez == 'u') {
            vogais++;

        }

        passo++;
    }

    return vogais;
}

int main() {
    printf("Para encerrar digite 0 e aperte enter\n\n");

    char palavra[21] = "";
    int vogais, operacao = 0;
    
    while(1) {
        printf("\nOperacao numero %d\n", operacao);
        printf("Digite uma palavra: ");
        scanf("%s", palavra);

        if(palavra[0] == '0') { break; }

        vogais = contVogais(palavra);

        printf("\nA quantidade de vogais em %s e igual a %d\n\n", palavra, vogais);

        operacao++;
    }

    printf("\nPrograma encerrado");

    return 0;
}