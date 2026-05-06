#include <iostream>

using namespace std;

int main() {
    int N, L, C;
    int cont = 0, CoposQuebrados = 0;

    cin >> N;
    
    while(cont < N) {
        cin >> L >> C;

        if(L > C) { CoposQuebrados += C; }
        
        cont++;
    }

    cout << CoposQuebrados << endl;

    return 0;
}
