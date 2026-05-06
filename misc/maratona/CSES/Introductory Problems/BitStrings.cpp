// Link: https://cses.fi/problemset/task/1617
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

    int n, ans = 1;
    cin >> n; 
    
    for(int i = 0; i < n; i++) {
        ans = (ans << 1) % 1000000007;
    }

    cout << ans << '\n';

    return 0;
}
