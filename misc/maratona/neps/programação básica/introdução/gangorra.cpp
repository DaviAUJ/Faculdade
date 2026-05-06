#include <iostream>

using namespace std;

int main(){
    int p1, c1, p2, c2, output;

    cin >> p1 >> c1 >> p2 >> c2;

    if(p1 * c1 > p2 * c2) {
        output = -1;
    } else if(p1 * c1 < p2 * c2) {
        output = 1;
    } else {
        output = 0;
    }

    cout << output << endl;
}