#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int64_t binExpRecursive(int64_t base, uint64_t exponent) {
    return 0;
}

int64_t binExp(int64_t base, uint64_t exponent) {
    int64_t out = 1;
    int64_t tmp = base;

    while(exponent != 0) {
        if(exponent & 1) {
            out *= tmp;
        }

        exponent >>= 1;

        tmp *= tmp;
    }

    return out;
}

int main() {
    FAST_IO;

    int64_t in1;
    uint64_t in2;
    cin >> in1 >> in2;
    cout << binExp(in1, in2) << '\n';

    return 0;
}
