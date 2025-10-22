// Link:
// Current Status:

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int main() {
    FAST_IO;

    uint32_t n, m, a, k;

    cin >> n >> m >> a >> k;

    while(n != 0 || m != 0 || a != 0 || k != 0) {
        k += a;    
    
        if(a == 0) {
            cout << "Impossible\n";
        }
        else if(m == 0) {
            
        }
        else if(a > m) {
            cout << k + a << '\n';
        }
        else if(m > a) {
            cout << m + n << '\n';
        }
        else {
            if(k % a == n % m) {
                cout << max(k, n) << '\n';
            }
            else {
                cout << "Impossible\n";
            }
        }

        cin >> n >> m >> a >> k;
    }

    return 0;
}
