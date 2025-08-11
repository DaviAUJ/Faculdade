#include <stdio.h>

void dieta(float pesoF, float peso) {
    int mes = 1;

    for(peso -= 5; peso > pesoF; peso -= 5) {
        printf("\n%.2f KG alcancado no %d mes", peso, mes);
        
        mes++;
    }

    if(peso < pesoF) {
        printf("\nNo %d e ultimo mes voce precisou perder apenas %.2f KG para atingir o peso almejado de %.2f KG", mes, (5 + peso) - pesoF, pesoF);

    } else {
        printf("\nVoce atingiu o peso almejado de %.2f KG no %d mes", pesoF, mes);
        
    }
}

int main() {
    float pesoF = 0, pesoI = 0;

    while(pesoF >= pesoI) {
        printf("\nDigite o peso atual: ");
        scanf("%f", &pesoI);

        printf("Digite o peso almejado: ");
        scanf("%f", &pesoF);
    }

    dieta(pesoF, pesoI);

    return 0;
}