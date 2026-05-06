#include <bits/stdc++.h>

using namespace std;

int main() {
    int n, contagens[10] = {};
    cin >> n;

    string input;

    for(int i = 0; i < n; i++) {
        cin >> input;

        for(int j = 0; j < input.size(); j++) { contagens[input[j] - '0']++; }
    }

    for(int i = 0; i < 10; i++) { cout << i << " - " << contagens[i] << endl; }
}