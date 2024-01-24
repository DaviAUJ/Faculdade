// Ajustar o código dado de forma que seja exibida o número da compra.

#include <stdio.h>

void ValidaCompra(float *L, int *C){
    float D;

    printf("\nCompra #%d\n", *C); // Linha Adicionada
    printf("Debito: ");
    scanf("%f",&D);

    if (*L - D >= 0) { 
        printf("Compra possivel! \n"); 

        *L = *L - D;
        *C += 1; // Linha adicionada

    } else { printf("Compra ""estourarah"" o cartao! \n"); }

    printf("Limite restante: %.2f \n\n",*L);
}

int main() {
    float Limite;
    int cont = 1; // Linha Adicionada

    printf("Limite do cartao: ");
    scanf("%f",&Limite);

    while(Limite > 0) { ValidaCompra(&Limite, &cont); } // Linha modificada
        
    printf("Seu limite de compras acabou!");

    return 0;
}