// https://cses.fi/problemset/task/1069

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define dbg(x) cout << #x << " = " << x << endl
#define ff first
#define ss second

typedef pair<int, int> ii;

int main() {
    FAST_IO;

    string s;

    cin >> s;
    
    int streak = 0;
    int count = 0;
    char looking = s[0];

    for(char c : s) {
        if(c == looking) {
            count++;
        }
        else {
            looking = c;
            streak = max(streak, count);
            count = 1;
        }
    }

    streak = max(streak, count);
    cout << streak;

    return 0;
}
