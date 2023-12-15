#include <iostream>
#include <cmath>
#include <iomanip>

using namespace std;

int main() {
    double n1, n2;

    cin >> n1 >> n2;

    cout << fixed;
    cout << setprecision(4);
    cout << pow(n1, n2);
}