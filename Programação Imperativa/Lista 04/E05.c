// Ajudar carla a determinar o ph das soluções

#include <stdio.h>

int main() {
    float ph;
    
    do {
        printf("\nPH: ");
        scanf("%f", &ph);
        
        if(ph > 7) { printf("BASICA\n"); }
        else if(ph == 7) { printf("NEUTRA\n"); }
        else if(ph >= 0) { printf("ACIDA\n"); }

    } while(ph != -1);

    return 0;
}