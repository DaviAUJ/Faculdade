#include <stdio.h>

int bbinaria (int chave, int inicio, int fim, int vetor[30]) {
if (fim < inicio)
return -1;
else {
int meio = (inicio + fim)/2;
if (vetor[meio]==chave)
return meio;
else{
if (vetor[meio] < chave)
return bbinaria (chave, meio+1, fim, vetor);
else
return bbinaria (chave, inicio, meio-1, vetor);}
}
}