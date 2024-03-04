#include <stdio.h>

int main() {
	float notaTemp;
	int notasAcima = 0;

	for(int numAluno = 1; numAluno <= 50; numAluno++){
		for(int numNota = 1; numNota <= 12; numNota++){
			printf("Digite a nota %d do aluno %d: ", numNota, numAluno);
			scanf("%f", &notaTemp);

			// Verificação e contagem das notas acima de 7
			if(notaTemp >= 7) {
				notasAcima++;
			}
		}

		// Verificação da aprovação do aluno
		if(notasAcima >= 5) {
			printf("\nAluno %d Aprovado\n\n", numAluno);
			
		} else {
			printf("\nAluno %d Reprovado\n\n", numAluno);

		}
	
		notasAcima = 0; // Reseta a nota
	}
}
	