// https://cses.fi/problemset/task/1068

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int main() {
    FAST_IO;

    uint64_t n;

    cin >> n;
    cout << n << ' ';

    while(n != 1) {
        if(n & 0x1) {
            n = n * 3 + 1;
        }
        else {
            n >>= 1;
        }

        cout << n << ' ';
    }

    return 0;
}
