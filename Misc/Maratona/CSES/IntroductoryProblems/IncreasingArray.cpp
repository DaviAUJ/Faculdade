// https://cses.fi/problemset/task/1094

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int main() {
    FAST_IO;
    
    uint64_t ans = 0;
    int n;
    cin >> n;

    vector<int> v(n + 1);
    v[0] = 0;

    for(int i = 1; i <= n; i++) {
        cin >> v[i];
        
        if(v[i] >= v[i - 1]) continue;

        ans += v[i - 1] - v[i];
        v[i] = v[i - 1];
    }

    cout << ans;

    return 0;
}
