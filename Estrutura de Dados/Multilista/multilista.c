#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMSTR 32

// Cabeca controla as materias que controla os alunos
typedef struct aluno {
    char nome[TAMSTR];
    int matricula;
    struct aluno *proxAluno;
} st_Aluno;

typedef struct materia {
    char nome[TAMSTR];
    int codigo;
    int quantAlunos;
    st_Aluno *priAluno;
    st_Aluno *ultAluno;
    struct materia *proxMateria;
} st_Materia;

typedef struct cabeca {
    st_Materia *inicio;
    st_Materia *fim;
    int quantidade;
} st_Cabeca;


void inicCabeca(st_Cabeca *cabeca) {
    cabeca->inicio = NULL;
    cabeca->fim = NULL;
    cabeca->quantidade = 0;
}


void criarMateria(st_Cabeca *cabeca, int codigo, char nome[TAMSTR]) {
    st_Materia *novaMateria = (st_Materia*) malloc(sizeof(st_Materia));
    if(novaMateria == NULL) { return; }

    // Preparando a nova matéria
    strcpy(novaMateria->nome, nome);
    novaMateria->codigo = codigo;
    novaMateria->quantAlunos = 0;
    novaMateria->priAluno = NULL;
    novaMateria->ultAluno = NULL;
    novaMateria->proxMateria = NULL;

    // Ajustando o nó cabeça
    if(cabeca->quantidade) { cabeca->fim->proxMateria = novaMateria; } // Caso já tenha alguma materia criada 
    else { cabeca->inicio = novaMateria; }

    cabeca->fim = novaMateria;
    cabeca->quantidade++;
}


void matricularAluno(st_Materia *materia, int matricula, char nome[TAMSTR]) {
    st_Aluno *novoAluno = (st_Aluno*) malloc(sizeof(st_Aluno));
    if(novoAluno == NULL) { return; }

    // Dado do novo aluno
    strcpy(novoAluno->nome, nome);
    novoAluno->matricula = matricula;
    novoAluno->proxAluno = NULL;

    // Ajustando a matéria
    if(materia->quantAlunos) { materia->ultAluno->proxAluno = novoAluno; } // Caso já tenha algum aluno matriculado
    else { materia->priAluno = novoAluno; }

    materia->ultAluno = novoAluno;
    materia->quantAlunos++;
}


st_Aluno excluirAluno(st_Materia *materia, int matricula) {
    st_Aluno *prescedente = materia->priAluno;
    st_Aluno *liberar; // Aluno que vai ser apagado
    st_Aluno output;

    if(materia->priAluno == materia->ultAluno) { // Caso só exista um aluno na materia
        liberar = materia->priAluno;
        materia->priAluno = NULL;
        materia->ultAluno = NULL;
    }
    else if(materia->priAluno->matricula == matricula) { // Caso o aluno a ser apagado é o primeiro da lista
        liberar = materia->priAluno;
        materia->priAluno = liberar->proxAluno;
    }
    else { // Caso onde o aluno esta no meio da lista ou no fim
        // Achando o aluno anterior ao que vai ser apagado
        while(prescedente != NULL || prescedente->proxAluno->matricula != matricula) {
            prescedente = prescedente->proxAluno;
        }

        liberar = prescedente->proxAluno;
        prescedente->proxAluno = liberar->proxAluno;
    }

    output = *liberar;
    free(liberar);
    materia->quantAlunos--;

    return output;
}


void t_Titulo(char *string) { printf("\n----- %s -----", string); }


void p_CriarDisciplina(st_Cabeca *cabeca) {
    int codigo;
    int repetir;
    char nome[TAMSTR];

    system("cls");
    t_Titulo("CRIAR DISCIPLINA");

    do {
        st_Materia *cursor = cabeca->inicio;
        repetir = 0;

        printf("\n\nDigite o codigo da materia: ");
        scanf("%d", &codigo);

        // Procurando se alguma materia já usa o codigo inserido
        while(cursor != NULL) {
            if(cursor->codigo == codigo) {
                repetir = 1;
                break;
            }

            cursor = cursor->proxMateria;
        }

        if(repetir) { printf("\nUma materia ja possui este codigo. Tente novamente"); }
    } while(repetir);
    
    printf("Digite o nome da materia: ");
    scanf(" %[^\n]s", &nome);

    criarMateria(cabeca, codigo, nome);

    printf("\nMateria criada com sucesso\n\n");
    system("pause");
}


void p_MatricularAluno(st_Cabeca *cabeca) {
    int matricula;
    int repetir;
    char nome[TAMSTR];
    st_Materia *materia;

    system("cls");
    t_Titulo("MATRICULAR ALUNO");

    do {
        int codigoMateria;
        st_Materia *cursor = cabeca->inicio;

        printf("\n\nCodigo da materia: ");
        scanf("%d", &codigoMateria);

        // Procurando a matéria usando o código inserido
        while(cursor != NULL) {
            if(cursor->codigo == codigoMateria) { break; }

            cursor = cursor->proxMateria;
        }

        materia = cursor;

        if(materia == NULL) { printf("\nCodigo de materia nao encontrado. Tente novamente"); }
    } while(materia == NULL);
    
    do {
        st_Aluno *cursor = materia->priAluno;
        repetir = 0;

        printf("Codigo do aluno: ");
        scanf("%d", &matricula);

        // Procurando se já existe algum aluno com essa matricula
        while(cursor != NULL) {
            if(cursor->matricula == matricula) {
                repetir = 1;
                break;
            }

            cursor = cursor->proxAluno;
        }

        if(repetir) { printf("\nEsta matricula ja esta sendo utilizada. Tente novamente\n"); }
    } while(repetir);

    printf("Nome do aluno: ");
    scanf(" %[^\n]s", &nome);

    matricularAluno(materia, matricula, nome);

    printf("\nAluno matriculado com sucesso\n\n");
    system("pause");
}


void p_ExcluirAluno(st_Cabeca *cabeca) {
    int matricula = 0;
    st_Materia *materia;

    system("cls");
    t_Titulo("EXCLUIR ALUNO");

    do {
        int codigoMateria;
        st_Materia *cursor = cabeca->inicio;

        printf("\n\nCodigo da materia: ");
        scanf("%d", &codigoMateria);

        // Procurando a matéria usando o código inserido
        while(cursor != NULL) {
            if(cursor->codigo == codigoMateria) { break; }

            cursor = cursor->proxMateria;
        }

        materia = cursor;

        if(materia == NULL) { printf("\nCodigo de materia nao encontrado. Tente novamente\n"); }
    } while(materia == NULL);

    while(!matricula) {
        st_Aluno *cursor = materia->priAluno;

        printf("Matricula do aluno: ");
        scanf("%d", &matricula);

        // Procurando pela matricula do aluno
        while(cursor != NULL) {
            if(cursor->matricula == matricula) { break; }
            
            cursor = cursor->proxAluno;
        }

        if(cursor == NULL) { 
            printf("Matricula nao encontrada. Tente novamente\n");
            matricula = 0; 
        }
    }

    excluirAluno(materia, matricula);

    printf("\n\nAluno excluido com sucesso\n\n");
    system("pause");
}


void p_MostrarMultilista(st_Cabeca *cabeca) {
    st_Aluno *cursorAluno;
    st_Materia *cursorMateria = cabeca->inicio;

    system("cls");
    t_Titulo("MOSTRAR MULTILISTA");

    printf("\n\nMaterias -> Alunos ");
    while(cursorMateria != NULL) {
        printf("\n\n||\n**\n||\n\n");
        printf("[%s | %d]", cursorMateria->nome, cursorMateria->codigo);

        cursorAluno = cursorMateria->priAluno;
        while(cursorAluno != NULL) {
            printf(" -> [%s | %d]", cursorAluno->nome, cursorAluno->matricula);
            cursorAluno = cursorAluno->proxAluno;
        }

        cursorMateria = cursorMateria->proxMateria;
    }

    printf("\n\n");
    system("pause");
}

int main() {
    st_Cabeca geral;
    int escolha;
    int sair = 0;

    inicCabeca(&geral);

    while(!sair) {
        system("cls");
        t_Titulo("MATERIAS E ALUNOS");

        printf("\n\n1 - Criar nova disciplina");
        printf("\n2 - Matricular novo aluno");
        printf("\n3 - Excluir Matricula de aluno");
        printf("\n4 - Mostrar multilista");
        printf("\n5 - Sair");

        printf("\n\nEscolha: ");
        scanf("%d", &escolha);

        switch(escolha) {
        case 1: p_CriarDisciplina(&geral); break;
        case 2: p_MatricularAluno(&geral); break;
        case 3: p_ExcluirAluno(&geral); break;
        case 4: p_MostrarMultilista(&geral); break;
        case 5: sair = 1; break;
        default: printf("\nPrompt errado. Tente novamente\n\n"); system("pause");
        }
    }
    
    printf("\n\nSaindo...");
}