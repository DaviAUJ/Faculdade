#include <iostream>

using namespace std;

// função feia do djabo
string title(string F){
	for(int i = 0; i < F.size(); i++) {
        if(i == 0) {
            if(F[i] >= 97 && F[i] <= 122) { F[i] -= 32; }
        } else if(F[i] == ' ') {
            if(F[i + 1] >= 97 && F[i + 1] <= 122) { F[i + 1] -= 32; }
        } else {
            if(F[i] >= 65 && F[i] <= 90 && F[i - 1] != ' ') { F[i] += 32; }
        }
    }

    return F;
}

int main() { 
	string F;

	getline(cin, F);

	cout << title(F) << "\n";
}