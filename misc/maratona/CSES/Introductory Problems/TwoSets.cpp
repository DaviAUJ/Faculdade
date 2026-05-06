// Link: https://cses.fi/problemset/task/1092
// Current Status: Accepted

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

    if(n % 4 == 0) {
        cout << "YES\n" <<  n / 2 << '\n';

        for(uint64_t i = 1; i <= n / 2; i += 2) {
            cout << i << ' ' << n - i + 1 << ' '; 
        }

        cout << '\n' << n / 2 << '\n';

        for(uint64_t i = 2; i <= n / 2; i += 2) {
            cout << i << ' ' << n - i + 1 << ' ';
        }

        cout << '\n';

        return 0;
    }

    if(n % 4 == 3) {
        cout << "YES\n" <<  n / 2 + 1 << '\n';

        for(uint64_t i = 1; i <= n / 2; i += 2) {
            cout << i << ' ' << n - i << ' '; 
        }

        cout << '\n' << n / 2 << '\n';

        for(uint64_t i = 2; i <= n / 2; i += 2) {
            cout << i << ' ' << n - i << ' ';
        }

        cout << n << '\n';

        return 0;
    }

    cout << "NO\n";

    return 0;
}
