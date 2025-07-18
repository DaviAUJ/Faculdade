#include <bits/stdc++.h>

using namespace std;

int main() {
    string risada, vogais;
    cin >> risada;

    for(int i = 0; i < risada.size(); i++) {
        if(risada[i] == 'a' || risada[i] == 'e' || risada[i] == 'i' || risada[i] == 'o' || risada[i] == 'u') {
            vogais += risada[i];
        }
    }

    char igual = 'S';
    for(int i = 0; i < floor(vogais.size() / 2); i++) {
        if(vogais[i] != vogais[vogais.size() - i - 1]) {
            igual = 'N';
        }
    }

    cout << igual;
}