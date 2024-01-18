// Para conter o crescimento da quantidade de gatos
// abandonados na UFS, e seus consequentes prejuízos, surgiu o
// projeto "CastraçãoSolidária", a partir do qual 4 veterinários
// experientes e 1 recém formado decidiram efetuar capturas e
// castrações todos os dias úteis, sendo os animais capturados
// divididos igualitariamente entre os veterinários experientes, e
// havendo sobras (não sendo possível uma divisão exata), o
// restante fica sob a responsabilidade do 5o veterinário – recém
// formado. Por exemplo, se capturados 22 gatos, cada
// veterinário experiente fica com 5 castrações, e o recém
// formado fica com 2. Se capturados 19, os experientes ficam
// com 4 e o formado recentemente fica com 3. Escrever
// programa em C para ler número de gatos capturados e exibir a
// distribuição das castrações entre os veterinários. Vale
// esclarecer que se capturados 4 ou menos gatos, as castrações
// ficam sob a responsabilidade de todos os veterinários, em
// conjunto.

#include <stdio.h>

int divisaoInteira (int dividendo, int divisor) { return dividendo / divisor - (dividendo / divisor) % 1; }

int main() {
    int gatos;

    printf("Quantos gatos foram capturados? ");
    scanf("%d", &gatos);

    // Esta quantidade de ifs serve para acomodar os plurais dos substantivos das mensagens
    if(gatos == 0) { 
        printf("Nenhum gato foi capturado"); 

    } else if(gatos <= 4) { 
        printf("O(s) %d gato(s) capturado sera(ao) responsabilidade dos 5 veterinarios", gatos); 

    } else { 
        printf("Cada veterinario experiente cuidara de %d gato(s) e o novato cuidara de %d gato(s)", divisaoInteira(gatos, 4), gatos % 4); 

    }
}