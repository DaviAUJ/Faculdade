// https://cses.fi/problemset/task/1070/

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

    if(n == 1) {
        cout << '1';
        return 0;
    }

    if(n <= 3) {
        cout << "NO SOLUTION";
        return 0;
    }

    if(n == 4) {
        cout << "2 4 1 3";
        return 0;
    }

    for(int i = n; i >= 1; i -= 2) {
        cout << i << ' ';
    }

    for(int i = n - 1; i >= 1; i -= 2) {
        cout << i << ' ';
    }

    return 0;
}
