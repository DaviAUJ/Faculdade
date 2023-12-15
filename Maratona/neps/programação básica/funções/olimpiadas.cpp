#include <bits/stdc++.h>

using namespace std;

struct Pais {
    int id = 0;

    int 
    ouro = 0,
    prata = 0,
    bronze = 0;
};

bool compararPaises(Pais a, Pais b) {
    if(a.ouro == b.ouro) { 
        if(a.prata == b.prata) {
            if(a.bronze == b.bronze) {
                return a.id < b.id;

            } else { return a.bronze > b.bronze; }
        } else { return a.prata > b.prata; }
    } else { return a.ouro > b.ouro; }
}

int main() {
    int npais, nesportes;
    cin >> npais >> nesportes;

    Pais paises[npais];

    for(int i = 0; i < npais; i++) {
        paises[i].id = i + 1;
    }

    int idpais;
    for(int i = 0; i < nesportes; i++) {
        for(int j = 0; j < 3; j++) {
            cin >> idpais;
            idpais--;

            if(j == 0) { paises[idpais].ouro++; }
            if(j == 1) { paises[idpais].prata++; }
            if(j == 2) { paises[idpais].bronze++; }
        }
    }
    
    sort(paises, paises + npais, compararPaises);

    for(int i = 0; i < npais; i++) {
        cout << paises[i].id << " ";
    }
}