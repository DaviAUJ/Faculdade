#include <stdio.h>

#define numAlunos 3 // Quantidade de alunos da turma
#define tamanhoNome 41 // Quantidade de caracteres no nome do aluno

typedef struct aluno {
    char nome[tamanhoNome];
    float nota1;
    float nota2;
    float nota3;
    float presenca;
} aluno;

float mediaAluno(aluno aluno) { return (aluno.nota1 + aluno.nota2 + aluno.nota3) / 3; }

char* definirSituacao(aluno aluno, float mediaTurma) {
    float media = mediaAluno(aluno);

    if(media > mediaTurma && aluno.presenca > 65) { return "APROVADO"; }
    else { return "REPROVADO"; }
}

int main() {
    aluno turma[numAlunos];
    float mediaTurma = 0;
    
    system("cls");

    // Leitura dos dados
    for(int i = 0; i < numAlunos; i++) {
        printf("\naluno #%d\n\n", i + 1);

        printf("Nome: ");
        fflush(stdin);
        fgets(turma[i].nome, tamanhoNome, stdin);

        printf("Nota 1: ");
        scanf("%f", &turma[i].nota1);

        printf("Nota 2: ");
        scanf("%f", &turma[i].nota2);

        printf("Nota 3: ");
        scanf("%f", &turma[i].nota3);

        // Tentar pegar um float no intervalo [0, 100]
        while(1) {
            printf("Percentual de presenca(0 - 100): ");
            scanf("%f", &turma[i].presenca);

            if(turma[i].presenca <= 100 && turma[i].presenca >= 0) { break; }
            else { printf("Entrada fora do intervalo\n\n"); }
        }

        // Calculo media da turma
        mediaTurma += mediaAluno(turma[i]);
    }

    mediaTurma /= numAlunos;

    printf("\nDados coletados com sucesso\n\n");
    system("pause");
    system("cls");

    // exibição dos dados coletados
    for(int i = 0; i < numAlunos; i++) {
        printf("\naluno #%d - %s", i + 1, turma[i].nome);
        printf("notas: [%.1f   %.1f   %.1f] - media: %.1f\n", turma[i].nota1, turma[i].nota2, turma[i].nota3, mediaAluno(turma[i]));
        printf("%s\n", definirSituacao(turma[i], mediaTurma));
    }

    printf("\n");
}