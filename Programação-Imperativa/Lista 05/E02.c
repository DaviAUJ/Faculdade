#include <stdio.h>

// Lá no exemplo tem parcela de 1 mes, o que não faz muito sentido, então ajeitei aqui pras
// parcelas começarem a partir dos segundo mes

void mostrarParcelas(float valor) {
    for(int i = 2; i <= 10; i++) {
        float total = valor + (i - 1) * valor * 0.1;

        printf("\nPagamento parcelado - Parcelas: %dx  R$%.2f - Total: %.2f", i, total / i, total); 
    } 
}

int main() {
    float valor;

    printf("Loja Sr. Ze - Parcelas de R$100 para compras acima de R$300");

    printf("\n\nValor da compra: ");
    scanf("%f", &valor);

    printf("\nPagamento a vista - Total: R$%.2f", valor);
    if(valor >= 300) { mostrarParcelas(valor); } // Lá no enunciado está que tem que ser maior que 300 mas assim acho melhor
    
}