#include <iostream>

using namespace std;

int main() {
    double prova1, prova2, media;

    cin >> prova1 >> prova2;

    media = (prova1 + prova2) / 2;

    if(media >= 7) {
        cout << "Aprovado" << endl;
    } else if(media >= 4) {
        cout << "Recuperacao" << endl;
    } else {
        cout << "Reprovado" << endl;
    }
}