#include <bits/stdc++.h>

using namespace std;

bool eh_primo(int x){
    if(x == 1) { return false; }

	for(int i = 2; i <= floor(x / 2); i++) {
        if(x % i == 0) { return false; }
    }

    return true;
}

int main(){
	int x;

	cin>>x;

	if(eh_primo(x)){
		cout << "S" << "\n";
	}else{
		cout << "N" << "\n";
	}
}