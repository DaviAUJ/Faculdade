#include <iostream>

using namespace std;

int main() {
    int 
    n = 0,
    input = 0,
    inputaux = 0,
    rep = 1,
    maiorrep = 0;
    
    cin >> n;

    for(int cont = 0; cont < n; cont++) {
        inputaux = input;
        cin >> input;

        if(input == inputaux) { 
            rep += 1;

            if(rep > maiorrep) { maiorrep = rep; }
        } else { rep = 1; }
    }

    cout << maiorrep << endl;
}