// Escrever programa para ler as três notas de
// um aluno, calcular a média deste (média
// ponderada: primeira nota com peso 1,
// segunda nota com peso 2 e terceira nota com
// peso 3) e determinar a situação do aluno:
// APROVADO – se média igual ou superior a 7;
// EM RECUPERAÇÃO – se não aprovado e com
// média igual ou superior a 5; REPROVADO –
// quando média inferior a 5.

#include <stdio.h>

int main() {
    float nota1, nota2, nota3, media;

    printf("Digite as notas do aluno: ");
    scanf("%f %f %f", &nota1, &nota2, &nota3);

    media = (nota1 + nota2 + nota3) / 3;

    printf("Media: %.2f - ", media);

    if(media < 5) { printf("REPROVADO"); }
    else if(media < 7) { printf("RECUPERACAO"); }
    else { printf("APROVADO"); }
}