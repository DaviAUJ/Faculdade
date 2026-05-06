#include <bits/stdc++.h>

using namespace std;

int main() {
    int nquestao, nacertos = 0;
    cin >> nquestao;

    string gabarito, aluno;
    cin >> gabarito >> aluno;

    for(int i = 0; i < nquestao; i++) {
        if(gabarito[i] == aluno[i]) { nacertos++; }
    } 

    cout << nacertos << endl;
}