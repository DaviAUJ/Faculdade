#include <iostream>

using namespace std;

int main(){
    int M, A;

    cin >> M >> A;

    if(M + A > 50) {
        cout << "N";
    } else {
        cout << "S";
    }
}