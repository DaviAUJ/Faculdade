#include <stdio.h>
#include <ctype.h>
#include <string.h>

// Função feita no exercicio 2
char* capitalizar(char* str) {
    int tamanho = strlen(str);

    // processo de capitalização do nome
    str[0] = toupper(str[0]);
    for(int cont = 1; cont < tamanho; cont++) {
        // Se encontrar um char com um espaço atrás transforma ele em maiuscula
        if(str[cont - 1] == ' ') {
            str[cont] = toupper(str[cont]);

        } else {
            str[cont] = tolower(str[cont]);

        }
    }

    return str;
}

char* upperstr(char* str) {
    int tamanho = strlen(str);

    // transforma todas as letras minusculas em maisculas uma por uma
    for(int cont = 0; cont < tamanho; cont++){
        str[cont] = toupper(str[cont]);
    }

    return str;
}

int main() {
    char nome[21] = "", sobrenome[31] = "", continuar = 's';
    int operacao = 1;

    while(continuar == 's') {
        printf("\nOperacao numero %d", operacao);
        printf("\nDigite um nome completo(20 chars para o nome, 30 chars para o sobrenome): ");
        scanf("%s ", nome); // pega o primeiro nome
        gets(sobrenome); // pega o resto

        printf("\nEste nome quando estilizado se torna: %s, %s\n\n", upperstr(sobrenome), capitalizar(nome));

        operacao++;

        printf("Deseja continuar?(s/n) ");
        scanf("%c", &continuar);
    }

    printf("\nPrograma encerrado");
}