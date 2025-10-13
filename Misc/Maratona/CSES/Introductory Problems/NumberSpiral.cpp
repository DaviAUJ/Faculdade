// https://cses.fi/problemset/task/1071

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int main() {
    FAST_IO;

    int n;
    cin >> n;

    while(n--) {
        uint64_t r, c;

        cin >> r >> c;

        uint64_t layer = max(r, c);
        uint64_t diff = r - c;
        uint64_t mid = layer * layer + (layer - 1) * (layer - 1) + 1;
        mid >>= 1;

        if(layer & 0x1) {
            cout << mid - diff << '\n';
        }
        else {
            cout << mid + diff << '\n';
        }
    }

    return 0;
}
