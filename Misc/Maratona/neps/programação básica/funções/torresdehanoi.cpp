#include <bits/stdc++.h>

using namespace std;

int cont = 0;

void hanoi(int n, char origem='a', char destino='c', char restante='b') {
    if(n == 0) { return; }

    hanoi(n - 1, origem, restante, destino);
    cont += 1;
    hanoi(n - 1, restante, destino, origem);
}

int main() {
    int discos, ntestes = 1;
    cin >> discos;

    while(discos != 0) {
        cout << "Teste " << ntestes << endl;

        hanoi(discos);

        cout << cont << endl << endl;

        cont = 0;
        ntestes++;
        cin >> discos;
    }
}