// Ajustar o código dado de forma que seja identificado também quando a
// meta da vaquinha foi ultrapassada, passando a haver duas
// mensagens de retorno ao usuário, e para, sempre que houver uma
// doação, exibir o valor parcial alcançado.]

#include <stdio.h>

int main() {
    float meta, doacao, soma = 0;

    printf("Meta de vaquinha: ");
    scanf("%f", &meta);

    do {
        printf("\nValor da doacao: ");
        scanf("%f", &doacao);

        soma += doacao;

        printf("Valor atual da vaquinha: %.2f\n", soma);
    } while (soma < meta);

    if(soma == meta) { printf("A meta foi alcancada!"); }
    else { printf("A meta foi um sucesso! Valor ultrapassado em %.2f", soma - meta); }

    return 0;
}