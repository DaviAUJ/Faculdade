// https://codeforces.com/problemset/problem/520/B

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define SLOG(x) cout << x << endl;
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
        if(start * 2 <= reach) {
            start *= 2;
            ans++;
            continue;
        }

        int dodiff;

        if(reach % 2 == 1) {
            dodiff = start - (reach >> 1) - 1;
            ans += dodiff + 2;
            break;
        }

        dodiff = start - (reach >> 1);
        ans += dodiff + 1;

        break;
    }

    cout << ans << '\n';

    return 0;
}
