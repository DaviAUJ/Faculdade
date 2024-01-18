#include <stdio.h>

// Os colegas do filho de Sr. Zé estão sentindo dificuldade para
// alugar um ônibus para levá-los ao “Museu da Gente
// Sergipana”. Então Sr. Zé resolveu disponibilizar sua Kombi,
// mas a depender do número de inscritos, serão necessárias
// muitas viagens, e alguns passageiros deverão ir de coletivo.
// Considerando que a Kombi tem capacidade para transportar 11
// pessoas (fora o motorista – Sr. Zé), escrever um programa em
// C, para, dado o número de inscritos no passeio ao Museu,
// exibir o número de viagens que devem ser necessárias e o
// número de passagens de coletivo. Exemplos: se 22 pessoas –
// 2 viagens de kombi e 0 passagem em coletivo; se 37 pessoas
// – 3 viagens e 4 passagens em coletivo. Vale esclarecer que se
// o número de passageiros for inferior a 11, Sr. Zé os levará de Kombi.

int divisaoInteira (int dividendo, int divisor) { return dividendo / divisor - (dividendo / divisor) % 1; }

int main() {
    int participantes;

    printf("Quantas pessoas estao participando? ");
    scanf("%d", &participantes);

    if(participantes < 11) {
        printf("\nSr. Ze ira levar os participantes de kombi sem problemas");

        return 0; // Fecha o programa
    }

    printf("\nSerao necessarias %d viagens de Kombi e %d passagens", divisaoInteira(participantes, 11), participantes % 11);
}