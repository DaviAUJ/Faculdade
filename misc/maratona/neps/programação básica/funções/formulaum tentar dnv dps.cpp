#include <bits/stdc++.h>

using namespace std;

struct Piloto { 
    int 
    id, 
    pontos = 0;
};

bool compararPilotos(Piloto a, Piloto b) { return a.pontos > b.pontos; }

int main() {
    int 
    nprix, 
    npilotos,
    nsistemas, 
    pontuacao,
    ultimo; 

    cin >> nprix >> npilotos;

    while(nprix != 0 && npilotos != 0) {
        Piloto colocacao[nprix][npilotos];
        Piloto aux[nprix][npilotos];

        for(int i = 0; i < nprix; i++) {
            for(int j = 0; j < npilotos; j++) {
                cin >> colocacao[i][j].id;
            }
        }

        cin >> nsistemas;

        for(int i = 0; i < nsistemas; i++) {
            for(int j = 0; j < nprix; j++) {
                copy(colocacao[j], colocacao[j] + npilotos, aux[j]);
            }

            cin >> ultimo;

            for(int j = 0; j < ultimo; j++) {
                cin >> pontuacao;

                aux[j].pontos += pontuacao;
            }

            sort(aux, aux + npilotos, compararPilotos);

            for(int j = 0; j < npilotos; j++) {
                if(j == 0) {
                    cout << aux[j].id << " ";

                } else {
                    if(aux[0].pontos == aux[j].pontos) {
                        cout << aux[j].id << " ";

                    }
                }
            }

            cout << endl;
        }

        cin >> nprix >> npilotos;
    }
}