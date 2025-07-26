#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    FAST_IO;

    uint16_t questions;
    uint16_t a, b = 0;
    uint16_t saida = 0;

    cin >> questions;

    while(questions--) {
        cin >> a;
        b += a;
        cin >> a;
        b += a;
        cin >> a;
        b += a;

        if(b >= 2) {
            saida++;
        }

        b = 0;
    }

    cout << saida << '\n';

    return 0;
}