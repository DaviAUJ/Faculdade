#include <iostream>

using namespace std;

int main(){
    int input;

    cin >> input;

    if(input > 0) {
        cout << "positivo";
    } else if(input < 0) {
        cout << "negativo";
    } else {
        cout << "nulo";
    }
}