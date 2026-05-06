#include <stdio.h>
#include <ctype.h>
#include <string.h>

int main() {
    // Como mostrado no slide, este char permitiria apenas 20 caracteres porem eu consigo associar mais quando usado o scanf ou o gets
    // para testar use a palavra desinstitucionalizado, ela tem 21 letras, portanto não deveria ser possível usa-lá como input
    char palavraMin[21] = "", palavraMai[21] = "";

    printf("Digite uma palavra(max 20 caracteres): ");
    scanf("%s", palavraMin);

    // Transformação em maiuscula
    for(int cont = 0; cont < strlen(palavraMin); cont++) {
        palavraMai[cont] = toupper(palavraMin[cont]); // Transformado char por char em maiúscula
    }

    printf("A palavra %s toda maiuscula e: %s", palavraMin, palavraMai);

    return 0;
}