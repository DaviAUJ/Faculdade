// https://codeforces.com/problemset/problem/2125/C
// Current Status: not good

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int bucha(int from, int to) {
    int a = to - from + 1;

    for(int i = from; i <= to; i++) {
        if(i % 2 == 0) {
            a--;
        }
        else if(i % 3 == 0) {
            a--;
        }
        else if(i % 5 == 0) {
            a--;
        }
        else if(i % 7 == 0) {
            a--;
        }
    }

    return a;
}

int main() {
    FAST_IO;
 
    uint64_t n, frangles = bucha(2, 210);
    cin >> n;

    cout << bucha(2, 4200) << "<- Teste\n";

    while(n--) {
        uint64_t l, r;
        cin >> l >> r;

        uint64_t low  = ((l - 1) / 210) * frangles + bucha(l - (l - 1) % 210, l - 1);
        uint64_t high = (r / 210) * frangles + bucha(r - r % 210 + 1, r);

        cout << high - low << '\n';
    }

    return 0;
}
