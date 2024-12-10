#include <iostream>

using namespace std;

// Complexidade de tempo:
// Melhor: O(1)
// Medio: O(n)
// Pior: O(n)

// Complexidade de espaço:
// Melhor: O(1)
// Medio: O(1)
// Pior: O(1)

int fatorial(int num) {
    int output = 1;

    for(int i = num; i > 1; i--) {
        output *= i;
    }

    return output;
}

int main() {
    cout << fatorial(5) << endl;
}

