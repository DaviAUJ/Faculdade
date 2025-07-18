#include <bits/stdc++.h>

using namespace std;

int main() {
    char operacao;
    double num1, num2;

    cin >> operacao >> num1 >> num2;

    cout << fixed;
    cout << setprecision(2);

    if(operacao == 'M') { cout << num1 * num2 << endl; }
    if(operacao == 'D') { cout << num1 / num2 << endl; }
}