#include <bits/stdc++.h>

using namespace std;

int main() {
    int dimensao;
    cin >> dimensao;

    int tabuleiro[dimensao][dimensao];

    for(int i = 0; i < dimensao; i++) {
        for(int j = 0; j < dimensao; j++) {
            cin >> tabuleiro[i][j];
        }
    }

    int somaL[dimensao] = {};
    int somaC[dimensao] = {};
    
    for(int i = 0; i < dimensao; i++) {
        for(int j = 0; j < dimensao; j++) {
            somaL[i] += tabuleiro[i][j];
            somaC[i] += tabuleiro[j][i];
        } 
    }

    int maiorSoma = 0;
    int maiorSomaAux = 0;

    for(int i = 0; i < dimensao; i++) {
        for(int j = 0; j < dimensao; j++) {
            maiorSomaAux = somaL[i] + somaC[j] - 2 * tabuleiro[i][j];

            if(maiorSomaAux > maiorSoma) { maiorSoma = maiorSomaAux; }
        }
    }
    
    cout << maiorSoma << endl;
}