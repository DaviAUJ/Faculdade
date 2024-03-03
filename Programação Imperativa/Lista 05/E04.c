#include <stdio.h>

int main() {
	int somaNotaAluno, notaTemp;

	for(int numAluno = 1; numAluno <= 50; numAluno++){
		for(int numNota = 1; numNota <= 12; numNota++){
			printf("Digite a nota %d do aluno %d", numNota, numAluno);
			scanf("%f", &notaTemp);

			somaNotaAluno += notaTemp;
		}

		printf("A media do aluno %d é %f", numAluno, somaNotaAluno / 12);
	}
}
	