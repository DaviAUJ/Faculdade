#include <bits/stdc++.h>

using namespace std;

int main() {
    char operador;
    int limite, num1, num2, resultado = 0;

    cin >> limite >> num1 >> operador >> num2;

    if(operador == '+') { resultado = num1 + num2; }
    if(operador == '*') { resultado = num1 * num2; }

    if(resultado > limite) { cout << "OVERFLOW" << endl; }
    else { cout << "OK" << endl; }
}