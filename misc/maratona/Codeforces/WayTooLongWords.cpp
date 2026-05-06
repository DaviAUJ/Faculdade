// https://codeforces.com/problemset/problem/71/A

#include <bits/stdc++.h>
#include <cstdint>
#include <cstdio>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    FAST_IO;

    uint16_t words;
    string a;

    cin >> words;

    while(words--) {
        cin >> a;

        if(a.length() > 10) {
            cout << a.front() << a.length() - 2 << a.back() << '\n';
            continue;
        }

        cout << a << '\n';
    }

    return 0;
}