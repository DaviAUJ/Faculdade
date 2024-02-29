#include <stdio.h>

void mostrarMediaEGanhos(int totalPassageiros) {
    printf("\nMedia de passageiros: %.2f", (float)totalPassageiros / 11);
    printf("\nGanhos: %d", totalPassageiros * 22);
}

int main() {
    int numPassageiros, menosPassageiros;
    int piorHorario, totalPassageiros = 0;

    for(int horas = 8; horas <= 18; horas++) {
        printf("Numero de passageiras do %d horas: ", horas);
        scanf("%d", &numPassageiros);

        // Contagem do total de passageiros do dia
        totalPassageiros += numPassageiros; 

        // Definição do horario com menos pessoas
        if(horas == 8) {
            piorHorario = horas;
            menosPassageiros = numPassageiros; // Determinando a base para comparação

        } else if(numPassageiros < menosPassageiros) {
            piorHorario = horas;
            menosPassageiros = numPassageiros;

        }
	}	

    printf("\nHorario de menor procura: %d.", piorHorario);
    mostrarMediaEGanhos(totalPassageiros);
    
    return 0;	
}