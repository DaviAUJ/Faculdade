#include <stdio.h>
#include <math.h>

int main() {
    float vMedia, distancia;

    printf("Digite a velocidade media esperada(km/h): "); 
    scanf("%f", &vMedia);

    printf("Digite a distancia(km): ");
    scanf("%f", &distancia);

    float tempoHoras = distancia / vMedia;
    printf("\nTempo de viagem estimado: %.0f horas e %.0f minutos", floor(tempoHoras), 60 * (tempoHoras - floor(tempoHoras)));
}