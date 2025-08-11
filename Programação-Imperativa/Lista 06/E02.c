#include <stdio.h>
#include <ctype.h>
#include <string.h>

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

int main() {
    char nome[41] = "";

    printf("Digite um nome(max 40 caracteres): ");
    gets(nome);

    printf("O nome inserido quando capitalizado vira: %s", capitalizar(nome));

    return 0;
}