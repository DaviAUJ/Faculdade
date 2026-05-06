#include <iostream>

using namespace std;

int main() {
    int 
    n = 0, 
    contagem = 0;

    cin >> n;

    int vector[n];

    for(int cont = 0; cont < n; cont++) { cin >> vector[cont]; }

    for(int cont = 0; cont < n - 2; cont++) { 
        if(vector[cont] == 1 && vector[cont + 1] == 0 && vector[cont + 2] == 0) { contagem++; } 
    }

    cout << contagem << endl;
}
