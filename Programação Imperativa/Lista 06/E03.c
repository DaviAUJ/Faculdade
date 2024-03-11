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
    char palavra[21] = "", continuar = 's';
    int vogais, operacao = 1;
    
    while(continuar == 's') {
        printf("\n\nOperacao numero %d\n", operacao);
        printf("Digite uma palavra(max 20 caracteres): ");
        scanf("%s", palavra);

        vogais = contVogais(palavra);

        printf("\nA quantidade de vogais em %s e igual a %d\n\n", palavra, vogais);

        operacao++;

        printf("Deseja continuar?(s/n) ");
        scanf(" %c", &continuar);
    }

    printf("\nPrograma encerrado");

    return 0;
}