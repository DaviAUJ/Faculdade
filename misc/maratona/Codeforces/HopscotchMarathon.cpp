// https://codeforces.com/gym/103960/problem/M

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<uint32_t, uint32_t> ii;

int smallestPrimeFactor(int n) {
    static int lp[100001];
    static int pr[50000];
    static int pr_idx;
    static int i = 2;

    if(n == 1) {
        return 1;
    }

    if(lp[n] != 0) {
        return lp[n];
    }

    for(; i <= 100000; ++i) {
        if(lp[i] == 0) {
            lp[i] = i;
            pr[pr_idx++] = i;
        }

        for(int j = 0; i * pr[j] <= 100000; ++j) {
            lp[i * pr[j]] = pr[j];
            if(pr[j] == lp[i]) {
                break;
            }
        }

        if(lp[n] != 0) {
            ++i;

            return lp[n];
        }
    }

    return lp[n];
}

int main() {
    FAST_IO;

    int n_runners, n_rounds;
    
    cin >> n_runners >> n_rounds;
    
    vector<int> pos(n_runners + 1);
    vector<int> win(n_runners + 1, -1);
    vector<ii> rounds_info(n_rounds + 1);

    for(int i = 1; i <= n_runners; i++) {
        cin >> pos[i];
    }

    for(int i = 1; i <= n_rounds; i++) {
        cin >> rounds_info[i].ff >> rounds_info[i].ss;
    }

    cout << "-1\n";

    int factor;
    int i;
    int j;

    for(i = 1; i <= n_rounds; i++) {
        const ii& current = rounds_info[i];

        factor = smallestPrimeFactor(current.ff);
        if(factor == 1) continue;

        for(j = factor; j <= n_runners; j += factor) {
            if(win[j] != -1) {
                continue;
            }

            pos[j] -= current.ss;

            if(pos[j] <= 0) {
                win[j] = i;
            }
        }
    }

    for(int i = 2; i <= n_runners; i++) {
        cout << win[i] << '\n';
    }

    return 0;
}
