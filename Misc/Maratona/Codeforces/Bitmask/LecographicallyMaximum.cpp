// https://codeforces.com/gym/105327/problem/L
// Current Status: Accepted

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int bit_count[30];

void countBits(int n) {
    int i = 0;

    while(n != 0) {
        bit_count[i] += n & 0x1;

        i++;
        n >>= 1;
    }
}

int makeBits() {
    int ret = 0;

    for(int i = 0; i < 30; i++) {
        if(bit_count[i] > 0) {
            ret |= 0x1 << i;
            bit_count[i]--;
        }
    }

    return ret;
}

int main() {
    FAST_IO;

    int n;
    cin >> n;

    for(int i = 0; i < n; i++) {
        int temp;
        cin >> temp;

        countBits(temp);
    }

    for(int i = 0; i < n; i++) {
        cout << makeBits() << ' ';
    }

    return 0;
}
