#include <iostream>

using namespace std;

int main(){
    int portaP, portaR;

    cin >> portaP >> portaR;

    if(portaP == 0) {
        cout << "C" << endl;
    } else {
        if(portaR == 0) {
            cout << "B" << endl;
        } else {
            cout << "A" << endl;
        }
    }

    return 0;
}