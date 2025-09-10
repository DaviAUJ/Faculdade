// LINK
// Current Status:

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

uint64_t max_value[64];
uint64_t n_bits[64];

uint64_t countBits(uint64_t n) {
    uint64_t ret = 0;

    while(n != 0) {
        ret += n & 0x1;
        n >>= 1;
    }

    return ret;
}

int main() {
    FAST_IO;

    uint64_t n;
    uint64_t ans = 0;
    cin >> n;

    n_bits[0] = 1;
    max_value[0] = 1;

    for(uint64_t i = 1; i < 64; i++) {
        n_bits[i] = n_bits[i - 1] * 2 -
    }

    cout << ans << '\n';

    return 0;
}
