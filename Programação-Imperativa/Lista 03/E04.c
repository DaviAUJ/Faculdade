// Faça um programa para ler um número
// inteiro, positivo de três dígitos, e gerar outro
// número formado pelos dígitos invertidos do
// número lido. (Ex: Numero Lido = 123;
// Numero Gerado = 321) Em seguida informar:
// NÚMERO GERADO MAIOR QUE NÚMERO LIDO ou
// NÚMERO LIDO MAIOR QUE NÚMERO GERADO, ou
// ainda, NÚMERO GERADO IGUAL AO NÚMERO LIDO.

#include <stdio.h>

int main() {
    int num, inverso = 0;

    printf("Digite um numero de 3 digitos: ");
    scanf("%d", &num);

    // processo de inversão
    inverso += (num % 10) * 100;
    inverso += (num % 100) - (num % 10);
    inverso += num / 100;

    printf("%d inverso e %d\n", num, inverso);
    if(inverso > num) { printf("NUMERO GERADO MAIOR QUE NUMERO LIDO"); }
    else if(inverso < num) { printf("NUMERO LIDO MAIOR QUE NUMERO GERADO"); }
    else { printf("NUMERO GERADO IGUAL AO NUMERO LIDO"); }
}