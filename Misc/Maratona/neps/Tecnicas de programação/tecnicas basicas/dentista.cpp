#include <bits/stdc++.h>

using namespace std;

struct Consulta {
    int inicio;
    int fim;
};

int menorConsulta(Consulta l[], int tamanho, int horario) {
    int numConsulta = 0;
    int menorFim = 0;

    for(int i = 0; i < tamanho; i++) {
        if(l[i].inicio == horario) {
            if(menorFim == 0 || menorFim < l[i].fim) { menorFim = l[i].fim; }
        }
    }

    for(int i = 0; i < tamanho; i++) {
        if(l[i].fim == menorFim) { return i; }
    }

    return -1;
}

int main() {
    int nconsulta, proxDisponivel = 10;
    cin >> nconsulta;

    Consulta lista[nconsulta];

    for(int i = 0; i < nconsulta; i++) {
        cin >> lista[i].inicio >> lista[i].fim;
    }

    int ultimo = lista[nconsulta - 1].fim;
    bool funcionando = true;
    int horarioDaVez = 10, dia = 0;

    while(funcionando) {
        if(menorConsulta(lista, nconsulta, horarioDaVez) != -1) {
            dia++;

            horarioDaVez = lista[menorConsulta(lista, nconsulta, horarioDaVez)].fim;
        } else { horarioDaVez += 10; }

        if(horarioDaVez == ultimo) { funcionando = false; }

    }

    cout << dia;
}