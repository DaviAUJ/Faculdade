// https://codeforces.com/problemset/problem/520/B

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> iVec2;

int main() {
    FAST_IO;

    int start, reach;
    cin >> start >> reach;

    if(reach <= start) {
        cout << start - reach << '\n';
        return 0;
    }

    int ans = 0;

    while(reach != start) {
        if(reach % 2) {
            ans++;
            reach++;
        }

        ans++;
        reach >>= 1;

        if(reach < start) {
            ans += start - reach;
            reach = start;
        }
    }

    cout << ans << '\n';

    return 0;
}
