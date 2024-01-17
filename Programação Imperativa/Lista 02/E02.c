#include <stdio.h>

// No pré-escolar “Balão Mágico” o número máximo de alunos de uma
// turma é definido anualmente, após as reformas de fim de ano e
// evolução curricular. Escrever programa em C onde se lê o número
// total de alunos matriculados, o número máximo de alunos por
// turma e exibir o número de turmas a serem formadas.

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
