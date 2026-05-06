// https://codeforces.com/problemset/problem/507/B

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define SLOG(x) cout << x << endl;
#define ff first
#define ss second

typedef pair<int, int> iVec2;

int main() {
    FAST_IO;

    double r, x, y, xl, yl;

    cin >> r >> x >> y >> xl >> yl;

    double d;

    d = (xl - x) * (xl - x) + (yl - y) * (yl - y);
    d = sqrt(d);

    cout << ceil(d / (2.0 * r)) << '\n';

    return 0;
}
