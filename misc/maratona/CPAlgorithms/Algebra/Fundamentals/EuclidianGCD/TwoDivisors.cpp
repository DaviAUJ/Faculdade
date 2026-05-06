// Link: https://codeforces.com/contest/1916/problem/B
// Status: Accepted

#include <bits/stdc++.h>

using namespace std;

int main() {
    uint64_t n;
    cin >> n;

    while(n--) {
        uint64_t a, b, c;
        cin >> a >> b;

        c = lcm(a, b);
        
        if(c == b) {
            printf("%lu\n", (b / a) * b);
        }
        else {
            printf("%lu\n", c);
        }
    }
}
