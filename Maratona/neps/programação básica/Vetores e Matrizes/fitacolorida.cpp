#include <bits/stdc++.h>

using namespace std;

int main() {
    int numeroQuadrados;
    
    cin >> numeroQuadrados;

    int fita[numeroQuadrados];

    for(int i = 0; i < numeroQuadrados; i++) { cin >> fita[i]; }

    bool fimEsquerda, fimDireita;
    int posRelativa, posEsq, posDir;
    for(int i = 0; i < numeroQuadrados; i++) {
        if(fita[i] == 0) {
            fimEsquerda = false;
            fimDireita = false;
            posRelativa = 0;

            while(!fimEsquerda || !fimDireita) {
                posRelativa++;
                posEsq = i - posRelativa;
                posDir = i + posRelativa;

                if(posEsq >= 0 && fita[posEsq] != 0 && (fita[posEsq] > posRelativa || fita[posEsq] == -1)) {
                    if(posRelativa > 9) { fita[posEsq] = 9; }
                    else { fita[posEsq] = posRelativa; }

                } else { fimEsquerda = true; }

                if(posDir <= numeroQuadrados - 1 && fita[posDir] != 0 && (fita[posDir] > posRelativa || fita[posDir] == -1)) {
                    if(posRelativa > 9) { fita[posDir] = 9; }
                    else { fita[posDir] = posRelativa; }
                    
                } else { fimDireita = true; }
            }
        }
    }

    for(int i = 0; i < numeroQuadrados; i++) { 
        if(i == numeroQuadrados - 1) { cout << fita[i]; }
        else { cout << fita[i] << " "; }
    }
}