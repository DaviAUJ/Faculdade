// https://codeforces.com/gym/105327/problem/A

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int main() {
    FAST_IO;

    int n_diret;
    int k_reuni;

    cin >> n_diret >> k_reuni;

    cout << (k_reuni - n_diret + 1) / n_diret << '\n';

    return 0;
}
