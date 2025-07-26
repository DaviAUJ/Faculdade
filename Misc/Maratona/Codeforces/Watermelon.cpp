#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    FAST_IO;

    uint16_t weight;

    cin >> weight;

    if((weight != 2) && ((weight % 2) == 0) ) {
        cout << "YES\n";

        return 0;
    }

    cout << "NO\n";

    return 0;
}