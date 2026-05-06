#include <bits/stdc++.h>

using namespace std;

int hanoi(int discos) { return pow(2, discos) - 1; }

int main() {
    int discos = 0, cont = 1;
    cin >> discos;

    while(discos != 0) {
        cout << "Teste " << cont << endl;
        cout << hanoi(discos) << endl << endl;
        
        cin >> discos;
        cont++;
    }
}