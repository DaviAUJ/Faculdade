// Aprovados no concurso do IBGE

#include <stdio.h>

int main() {
    int qPort, qMat, aprvds = 0;
    float notaRed;
    char escolha = 'S';

    while(escolha == 's' || escolha == 'S') {
        printf("\nQuestoes corretas na prova de portugues: ");
        scanf(" %d", &qPort);

        printf("Questoes corretas na prova de matematica: ");
        scanf(" %d", &qMat);

        printf("Nota na redacao: ");
        scanf(" %f", &notaRed);

        if(qPort >= 40 && qMat >= 21 && notaRed >= 7) { aprvds++; }

        printf("\nDeseja continuar(S/N)? ");
        scanf(" %c", &escolha);
    }

    printf("\nNumero de aprovados: %d", aprvds);
}