// Ler notas de alunos e identificar se cada foi aprovado.
// Considerar como sistema de avaliação: em princípio, 3
// notas; são aprovados os alunos com média 7; para os
// alunos com média acima de 3, é possibilitado fazer 4a
// avaliação, então a média passa a ser 5 para obtenção da
// aprovação. Após a identificação de que um aluno foi
// aprovado, ou não; deve ser questionado se o usuário (do
// programa) deseja verificar a situação de outro aluno.

#include <stdio.h>

float media3(float x, float y, float z) { return (x + y + z) / 3; }

void verificarNota(float nota) {
    float notaR;

    if(nota >= 7) { printf("\nAluno aprovado!"); }
    else if(nota >= 3) { 
        printf("\nAluno tera de fazer repositiva");

        printf("\nNota da repositiva: ");
        scanf("%f", &notaR);

        if(notaR >= 5) { printf("\nAluno aprovado!"); }
        else { printf("\nAluno reprovado"); }
    } 
    else { printf("\nAluno reprovado"); }
}

int main() {
    float nota1, nota2, nota3, media;
    char lerNotas = 'S';

    while(lerNotas == 'S' || lerNotas == 's') {
        printf("\nDigite as 3 notas do aluno: ");
        scanf("%f %f %f", &nota1, &nota2, &nota3);

        media = media3(nota1, nota2, nota3);
        printf("media: %.2f\n", media);

        verificarNota(media);

        printf("\nQuer continuar lendo mais notas(s/n)? ");
        scanf(" %c", &lerNotas);
    }

    printf("Programa encerrado");

    return 0;
}