#include <bits/stdc++.h>
#include <cstdint>

using namespace std;

#define FAST_IO ios_base::sync_with_stdio(0); cin.tie(0)

int main() {
    FAST_IO;

    uint64_t n, m;
    uint64_t a;

    cin >> n >> m;
    cin >> a;

    n = n % a == 0 ? n / a : n / a + 1;
    m = m % a == 0 ? m / a : m / a + 1;
    a = n * m;

    cout << a << '\n';

    return 0;
}
