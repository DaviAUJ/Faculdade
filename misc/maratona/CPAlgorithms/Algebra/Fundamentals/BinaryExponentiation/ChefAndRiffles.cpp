// Link: https://www.codechef.com/JAN221B/problems/RIFFLES
// Current Status: tommorow ill do it

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

vector<int> apply(vector<int>& seq, vector<int>& perm) {
    vector<int> out(seq.size());

    for(int i = 0; i < seq.size(); i++) {
        out[perm[i]] = seq[i];
    }

    return std::move(out);
}

int initPerm(int idx, int n) {
    if(idx & 1) {
        return (n / 2) + (idx - 1) / 2;
    }
    else {
        return idx / 2;
    }
}

int main() {
    FAST_IO;

    int t;
    cin >> t;

    while(t--) {
        int n, k;

        cin >> n >> k;

        vector<int> seq(n), perm(n);

        for(int i = 0; i < n; i++) {
            seq[i] = i;
            perm[i] = initPerm(i, n);
        }

        while(k > 0) {
            if(k & 1) {
                seq = apply(seq, perm);
            }

            for(int i = 0; i < n; i++) {
                vector<int> a(n);
                a[initPerm(i, n)] = perm[i];

                perm = a;
            }
            k >>= 1;
        }

        for(int n : seq) {
            cout << n + 1 << ' ';
        }

        cout << '\n';
    }

    return 0;
}
