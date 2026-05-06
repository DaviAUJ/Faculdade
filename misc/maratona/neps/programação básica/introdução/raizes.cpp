#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    int n;
    double input;

    cin >> n;

    for(int cont = 0; cont < n; cont++) {
        cin >> input;

        cout << fixed;
        cout << setprecision(4) << sqrt(input) << endl;
    }
}