#include <bits/stdc++.h>

using namespace std;

int modulo(int num) {
    if(num < 0) { return -1 * num; }
    else { return num; }
}

int main() {
    int qpinos, altura;
    cin >> qpinos >> altura;

    int alturas[qpinos];

    for(int i = 0; i < qpinos; i++) { cin >> alturas[i]; }

    int diferenca, movimentos = 0;

    for(int i = 0; i < qpinos - 1; i++) {
        if(alturas[i] != altura) {
            diferenca = altura - alturas[i];

            alturas[i] += diferenca;
            alturas[i + 1] += diferenca;

            movimentos += modulo(diferenca);
        }
    }

    cout << movimentos << endl;
}
