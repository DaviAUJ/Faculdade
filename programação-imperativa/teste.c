#include <stdio.h>
#include <stdlib.h>

int main() {
    int *lista = (int*) malloc(sizeof(int) * 5);

    for(int i = 0; i < 5; i++) {
        lista[i] = i;
    }

    printf("%d", lista[5]);
}