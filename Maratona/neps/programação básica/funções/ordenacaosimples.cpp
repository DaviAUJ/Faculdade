#include <bits/stdc++.h>

using namespace std;

void bubbleSort(int lista[], int tamanho) {
    bool ordenado = false;
    int aux;

    while(!ordenado) {
        ordenado = true;

        for(int i = 0; i < tamanho - 1; i++) {
            if(lista[i] > lista[i + 1]) {
                aux = lista[i + 1];
                lista[i + 1] = lista[i];
                lista[i] = aux;

                ordenado = false;
            }
        }
    }
}

int main() {
    int tamanho;
    cin >> tamanho;
    
    int lista[tamanho];
    for(int i = 0; i < tamanho; i++) { cin >> lista[i]; }

    bubbleSort(lista, tamanho);

    for(int i = 0; i < tamanho; i++) {
        cout << lista[i] << ' '; 
    }
}