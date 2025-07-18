#include <iostream>

using namespace std;

int main() {
    int n;
    
    cin >> n;

    int lista[n];

    for(int i = 0; i < n; i++) { cin >> lista[i]; }

    if(n == 1) { cout << lista[0] << endl; }
    else {
        int cont;

        for(int i = 0; i < n; i++) {
        if(i == 0) { cont = lista[i] + lista[i + 1]; } 
        else if(i == n - 1) { cont = lista[i - 1] + lista[i]; } 
        else { cont = lista[i - 1] + lista[i] + lista[i + 1]; }
        
        cout << cont << endl;
        }
    }
}