// https://codeforces.com/problemset/problem/270/A

#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define SLOG(x) cout << x << endl;

int main() {
    FAST_IO;
    // n = -360 / (a - 180)

    uint16_t t;
    uint16_t a;
    double sla;

    cin >> t;

    while(t--) {
        cin >> a;

        sla = -360 / ((double)a - 180);

        if(floor(sla) == sla) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }

    return 0;
}
