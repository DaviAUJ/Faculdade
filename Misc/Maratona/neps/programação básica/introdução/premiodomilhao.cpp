#include <iostream>

using namespace std;

int main(){
    int dias, dia, accacessos = 0, accdias = 0;

    cin >> dias;

    while(accacessos < 1000000) {
        cin >> dia;

        accacessos += dia;

        accdias++;
    }

    cout << accdias << endl;   
}