// Link: https://cses.fi/problemset/task/1618
// Current Status:  everything is wrong

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

uint32_t krl(uint32_t a, uint32_t b) {
    return (a % b == 0) ? a / b : a / b + 1;
}

int main() {
    FAST_IO;

    uint32_t n;
    uint64_t ans = 0;
    cin >> n;

    uint32_t i = 1;
    uint32_t fn = 0, tn = 0;

    for(uint32_t l = 5; l <= n; l *= 10) {
        fn = krl(l, 10) - fn;
        ans += fn * i;
        i++;
    }

    i = 1;
    for(uint32_t l = 10; l <= n; l *= 10) {
        tn = krl(l, 10) - tn;
        ans += tn * i;
        i++;
    }
    
    fn = n/ 10 - fn;
    tn = n / 10 - tn;
    ans += (fn + tn) * i;

    cout << ans << '\n';

    return 0;
}
