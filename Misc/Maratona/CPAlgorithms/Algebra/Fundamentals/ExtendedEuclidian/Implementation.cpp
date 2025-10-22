#include <cstdio>
#include <iostream>
#include <utility>

using namespace std;

pair<int64_t, int64_t> ExtGCD(int64_t a, int64_t b) {
    pair<int64_t, int64_t> out;
    pair<int64_t, int64_t> aux;
    
    int64_t swap;
    int64_t q;

    aux.first = 1;
    aux.second = 0;

    while(b) {
        q = a / b;

        out.first = aux.second;
        out.second = aux.first - aux.second * q;

        out.swap(aux);

        a -= q * b;
        swap = a;
        a = b;
        b = swap;
    }

    return out;
}

int main() {
    int64_t a, b;

    cin >> a >> b;

    auto c = ExtGCD(a, b);

    printf("(%ld, %ld)\n", c.first, c.second);
}
