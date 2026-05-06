// https://cses.fi/problemset/task/1083

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
    vector<int> v(n + 1, 0);

    for(int i = 1; i < n; i++) {
        int a;
        cin >> a;

        v[a] = a;
    }

    for(int i = 1; i <= n; i++) {
        if(v[i] == 0) {
            cout << i << '\n';
            return 0;
        }
    }

    return 0;
}
