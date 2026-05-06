#include <bits/stdc++.h>

using namespace std;

int main() {
    int tamanho;
    cin >> tamanho;

    int quadrado[tamanho][tamanho];

    for(int i = 0; i < tamanho; i++) {
        for(int j = 0; j < tamanho; j++) {
            cin >> quadrado[i][j];
        }
    }

    bool magicidade = true;
    int somaH, somaV, somaD, somaDI, somaFixa, i = 0, j;

    while(magicidade && i < tamanho) {
        somaH = 0;
        somaV = 0;
        somaD = 0;
        somaDI = 0;

        for(j = 0; j < tamanho; j++) { 
            somaH += quadrado[i][j]; 
            somaV += quadrado[j][i];
            somaD += quadrado[j][j];
            somaDI += quadrado[j][tamanho - j - 1];
        }

        if(somaH != somaFixa || somaV != somaFixa || somaD != somaFixa || somaDI != somaFixa) {
            if(i == 0) { somaFixa = somaH; }
            else { magicidade = false; somaFixa = -1; }
        }
    
        i++;
    }

    cout << somaFixa << endl;
}