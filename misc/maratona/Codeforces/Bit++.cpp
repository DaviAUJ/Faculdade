#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    FAST_IO;

    uint16_t statements;
    string s;
    int16_t x;

    cin >> statements;
    
    while(statements--) {
        cin >> s;

        if(s.front() == '+') {
            x++;
            continue;
        }

        if(s.front() == '-') {
            x--;
            continue;
        }

        if(s.back() == '+') {
            x++;
            continue;
        }

        x--;
    }

    cout << x << '\n';

    return 0;
}
