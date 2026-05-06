// https://cses.fi/problemset/task/1146
// Current Status: Half accepted

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

uint64_t count_msb[60] = {0, 1};

uint64_t dabi(uint64_t n) {
    for(uint64_t i = 2; i < 60; i++) {
        count_msb[i] = (count_msb[i - 1] - 1) * 2 + (0x1 << (i - 2)) + 1;
    }

    uint64_t msb_pos = 0, i = 0, ans = 0;

    for(i = n; i != 0; i >>= 1) {
        msb_pos++;
    }

    for(i = 0; i < msb_pos - 1; i++) {
        if((n >> i) & 0x1) {
            ans += count_msb[i + 1] + (((0x1 << (i + 1)) - 1) & n);
        }
    }

    ans += count_msb[i + 1];

    return ans;
}

uint64_t brute(uint64_t n) {
    uint64_t ret = 0;

    for(uint64_t i = 1; i <= n; i++) {
        uint64_t j = i;

        while(j != 0) {
            ret += j & 0x1;
            j >>= 1;
        }
    }

    return ret;
}

uint64_t will(uint64_t n) {
    uint64_t ret = 0;

    n++;

    for(uint64_t i = 0; (n >> i) != 0; i++) {
        uint64_t p = 0x1 << (i + 1);
        uint64_t q = n / p;
        uint64_t r = n % p;

        ret += q * (0x1 << i) + (r > (p >> 1) ? r - (p >> 1) : 0);
    }

    return ret;
}

int main() {
    FAST_IO;

    uint64_t n;
    cin >> n;

    cout << "Will: " << will(n) << endl;
    cout << "Davi: " << dabi(n) << endl; 
    cout << "Brute: " << brute(n) << endl;

    return 0;
}
