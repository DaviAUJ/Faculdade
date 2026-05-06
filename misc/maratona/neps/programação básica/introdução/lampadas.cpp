#include <iostream>

using namespace std;

int main(){
    int
    interruptor,
    nvezes,
    a = 0, 
    b = 0;

    cin >> nvezes;

    for(int i = 0; i < nvezes; i++) {
        cin >> interruptor;

        if(a == 0) { a = 1; }
        else { a = 0; }

        if(interruptor == 2) {
            if(b == 0) { b = 1; }
            else { b = 0; }
        }
    }

    cout << a << endl;
    cout << b << endl;
}