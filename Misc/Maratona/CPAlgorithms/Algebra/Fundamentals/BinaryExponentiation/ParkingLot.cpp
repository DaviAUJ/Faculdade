// Link: https://codeforces.com/problemset/problem/630/I
// Current Status: Accepted

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

uint64_t binPow(uint64_t b, uint64_t e) {
    uint64_t out = 1;

    while(e > 0) {
        if(e & 1) {
            out *= b;
        }

        b *= b;
        e >>= 1;
    }

    return out;
}

int main() {
    FAST_IO;
    
    uint64_t n;
    cin >> n;
    uint64_t ans = 2 * 3 * binPow(4, n - 2) + (n - 3) * 3 * 3 * binPow(4, n - 3);
    cout << ans << '\n';

    return 0;
}
