// https://codeforces.com/problemset/problem/1986/A

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define SLOG(x) cout << x << endl;

int64_t middle(int64_t a, int64_t b, int64_t c) {
    int64_t t;

    if(a > b) {
        t = a;
        a = b;
        b = t;
    }

    if(b > c) {
        t = c;
        c = b;
        b = t;
    }

    if(a > b) {
        t = a;
        a = b;
        b = t;
    }
    
    return b;
}

int64_t f(int64_t a, int64_t b, int64_t c, int64_t m) {
    return abs(c - m) + abs(b - m) + abs(a - m);
}

int main() {
    FAST_IO;

    int64_t n;
    int64_t a, b, c;

    cin >> n;
    
    while(n--) {
        cin >> a >> b >> c;

        int64_t m = middle(a, b, c);

        cout << f(a, b, c, m) << '\n';
    }

    return 0;
}
