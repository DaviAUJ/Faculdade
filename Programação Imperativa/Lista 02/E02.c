#include <stdio.h>

int aluno(int totalAlunos, int maxAlunos) {
    if(totalAlunos % maxAlunos == 0) { return totalAlunos / maxAlunos; }
    else { return totalAlunos / maxAlunos - (totalAlunos / maxAlunos) % 1 + 1; }
}

int main() {
    int totalAlunos, maxAlunos;

    printf("Quantos alunos estão matriculados? ");
    scanf("%d", &totalAlunos);

    printf("Quantos alunos cada sala comporta? ");
    scanf("%d", &maxAlunos);

    printf("Para este ano são necessarias %d salas", aluno(totalAlunos, maxAlunos));
}
