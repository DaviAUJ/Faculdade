#include <stdio.h>
#include <string.h>

int compararStr(char* str1, char* str2) {
    int tamanho1 = strlen(str1), tamanho2 = strlen(str2);

    if(tamanho1 != tamanho2) { return 0; }

    for(int cont = 0; cont <= tamanho1; cont++) {
        if(str1[cont] != str2[cont]) { return 0; }
    }

    return 1;
}

int contAlunosGeron(char* ano) {
    unsigned short int cont = 0;
    char anoAluno[5] = "", cursoAluno[3] = "", matricula[11];

    for(int aluno = 1; aluno <= 100; aluno++){
        printf("Digite a matricula do aluno #%d: ", aluno);
        scanf(" %s", matricula);

        // extraindo o ano da matricula
        anoAluno[0] = matricula[0];
        anoAluno[1] = matricula[1];
        anoAluno[2] = matricula[2];
        anoAluno[3] = matricula[3];
        
        // extraindo o curso
        cursoAluno[0] = matricula[4];
        cursoAluno[1] = matricula[5];

        if(compararStr(anoAluno, ano) && compararStr(cursoAluno, "99")) { cont++; }
    }

    return cont;
}

int main() {
    char ano[5];
    unsigned short int contAlunos;

    printf("Digite o ano alvo: ");
    scanf("%s", ano);

    contAlunos = contAlunosGeron(ano);

    printf("%d alunos de gerontologia entraram em %s", contAlunos, ano);
}
