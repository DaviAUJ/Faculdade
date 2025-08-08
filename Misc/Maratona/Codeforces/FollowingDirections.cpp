// https://codeforces.com/problemset/problem/270/A

#include <bits/stdc++.h>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)
#define SLOG(x) cout << x << endl;

struct Vec2 {
    int32_t x;
    int32_t y;
};

int main() {
    FAST_IO;

    uint16_t t;
    uint16_t n;
    char dir;
    bool ans;
    Vec2 pos;

    cin >> t;

    while(t--) {
        pos = { 0, 0 };
        cin >> n;
        //n++;
        ans = false;
        
        while(n--) {
            cin >> dir;
            //SLOG(dir);

            switch(dir) {
                case 'U': pos.y++; break;
                case 'R': pos.x++; break;
                case 'D': pos.y--; break;
                case 'L': pos.x--; break;
                default: ; 
            }

            if(pos.x == 1 && pos.y == 1) {
                ans = true;
            }
        }
        
        if(ans) {
            cout << "YES\n";
        }
        else {
            cout << "NO\n";
        }
    }

    return 0;
}
