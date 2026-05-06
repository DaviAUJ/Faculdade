// https://cses.fi/problemset/task/2189/

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0);cin.tie(0);cout.tie(0)

struct iVec2 {
    int64_t x;
    int64_t y;
};

int main() {
    FAST_IO;

    iVec2 p1, p2, p3;
    int64_t t;

    cin >> t;

    while(t--) {
        cin >> p1.x >> p1.y >> p2.x >> p2.y >> p3.x >> p3.y;

        int64_t a = (p1.x - p2.x) * (p3.y - p2.y) - (p1.y - p2.y) * (p3.x - p2.x);

        if(a < 0) {
            cout << "LEFT\n";
        }
        else if(a > 0) {
            cout << "RIGHT\n";
        }
        else {
            cout << "TOUCH\n";
        }
    }

    return 0;
}
