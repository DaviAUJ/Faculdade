#include <stdio.h>

int remedio(int comMes, int comCaixa ) {
    if(comMes % comCaixa == 0) { return comMes / comCaixa; }
    else { return comMes / comCaixa - (comMes / comCaixa) % 1 + 1; }
}

int aluno(int totalAlunos, int maxAlunos) {
    if(totalAlunos % maxAlunos == 0) { return totalAlunos / maxAlunos; }
    else { return totalAlunos / maxAlunos - (totalAlunos / maxAlunos) % 1 + 1; }
}

// As duas são a mesma função, uma divisão entre duas entradas
// e depois aplicado um arredondamento pra cima

int main() {
    printf("%d", aluno(250, 40));
}