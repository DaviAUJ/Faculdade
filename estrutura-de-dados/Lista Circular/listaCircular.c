// Feito por:
// Davi Araújo do Nascimento
// Lucas Emanuel Siqueira Costa
// Wemerson da Silva Soares
// William Gabriel Yckson Araújo Braga

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define TAMSTR 64

typedef struct no {
    char nome[TAMSTR];
    struct no *ponteiro;
} no;



int criarNoInicial(no **noInicial, char nome[]) {
    no *novoNo = (no*) malloc(sizeof(no));
    if(novoNo == NULL) { return 0; }

    strcpy(novoNo->nome, nome);
    novoNo->ponteiro = novoNo;
    *noInicial = novoNo;

    return 1;
}

int adicionarNoFrente(no **noInicial, char nome[]){
    no *noFinal = (*noInicial);
    no *novoNo = (no*) malloc(sizeof(no));

    if(novoNo == NULL){ return 0;}



    while (noFinal->ponteiro != (*noInicial)){
        noFinal = noFinal->ponteiro;
    }

    strcpy(novoNo->nome, nome);
    novoNo->ponteiro = (*noInicial);
    noFinal->ponteiro = novoNo;
    *noInicial = novoNo;


    return 1;
}

int adicionarNoFinal(no **noInicial, char nome[]) {
    no *novoNo, *noLoop;

    if(*noInicial == NULL) { criarNoInicial(noInicial, nome); }
    else {
        novoNo = (no*) malloc(sizeof(no));
        if(novoNo == NULL) { return 0; }

        noLoop = *noInicial;

        // Encontrando o ultimo nó da lista
        while(noLoop->ponteiro != *noInicial) { noLoop = noLoop->ponteiro; }

        strcpy(novoNo->nome, nome);
        novoNo->ponteiro = *noInicial;
        noLoop->ponteiro = novoNo;
    }

    return 1;
}

int removerNoFrente (no **noInicial){
    no *noFinal = (*noInicial);

    while (noFinal->ponteiro != (*noInicial)){
        noFinal = noFinal->ponteiro;
    }

    (*noInicial) = (*noInicial)->ponteiro;
    noFinal->ponteiro = (*noInicial);


    return 1;
}

void exibirLista(no **noInicial) {
    no *noLoop;

    noLoop = *noInicial;

    if((*noInicial)->ponteiro == NULL) { printf("Lista vazia"); return; }

    do {
        printf("%s -> ", noLoop->nome);
        noLoop = noLoop->ponteiro;

    } while(noLoop != *noInicial);

    //Coloquei essa linha pra poder mostrar o primeiro nó dnv, lembrar de remover depois
    //printf("%s", (*noInicial)->nome);

    //------------------------------------------------------------------------------------
}

void destruirLista(no **noInicial){
    if (*noInicial == NULL)
        return;              // se a lista estiver vazia, não há nada a se fazer

    no *noAtual = *noInicial;              // começa do nó inicial
    no *proxNo;                          // guarda o próximo nó para continuar a percorrer a lista
    do                                 // percorre a lista circular até voltar ao inicio
    {
        proxNo = noAtual->ponteiro;        // guarda o próximo nó
        free(noAtual);                    // libera a memória do nó atual
        noAtual = proxNo;                // avança para o próximo nó
    } while (noAtual != *noInicial);    // continua até voltar ao nó inicial

    *noInicial = NULL;

} /*Basicamente funciona da msm forma q na lista encadeada normal
    oq muda msm é a condição do 'do while' vcs tao ligado;
    quando termina de excluir a glr, garante com q o inicio
    esteja apontando pra NULL ou seja lista vazia... RECEBA 
    APAGUEM ISSO AQ DPS TA SO VOU DEIXAR PQ SOU GAIATO*/

no* pesquisarElemento(no **noInicial, const char *nome){
    no *noLoop;

    if (*noInicial == NULL) return NULL; //se o nó inicial é NULL a lista está vazia

    noLoop = *noInicial;

    do{ //percorre a lista circular
        int i = 0;
        int iguais = 1; //assume que as strings são iguais

        while (nome[i] != '\0' && noLoop->nome[i] != '\0'){ //compara os caracteres das duas strings
            if (nome[i] != noLoop->nome[i]) {
                iguais = 0; // Strings são diferentes
                break; // Interrompe a comparação
            }
            i++;
        }

        if (nome[i] != '\0' || noLoop->nome[i] != '\0'){ //se ambas as strings terminaram ao mesmo tempo
            iguais = 0; //comprimentos diferentes
        }

        if (iguais){
            return noLoop; //se as strings são iguais, retorna o nó encontrado
        }
        
        noLoop = noLoop->ponteiro; //move para o próximo nó na lista circular
    } while (noLoop != *noInicial); //continua até voltar ao início

    return NULL; //se não encontrou, retorna NULL
}

void rodarJosephus(no **noInicial, int m) {
    no *eliminado;
    no *noAtual;
    no *noAnterior;
    int count;
    int i = 1;  //contador de eliminados

    if (*noInicial == NULL) return; //se não houver nó

    printf("\n");
    exibirLista(noInicial); //para exibir a lista inicial
    noAtual = *noInicial; //começa a partir do nó inicial
    
    while (*noInicial != (*noInicial)->ponteiro) {
        count = 1;

        while (count < m) { //encontrar o nó a ser eliminado
            noAnterior = noAtual;
            noAtual = noAtual->ponteiro;
            count++;
        }
        
        eliminado = noAtual; //elimina o nó
        if (noAtual == *noInicial) {
            *noInicial = (*noInicial)->ponteiro;
        }
        noAnterior->ponteiro = noAtual->ponteiro; //ajusta o ponteiro do nó anterior para pular o nó atual que está sendo eliminado
        printf("\n%d° ELIMINADO: %s\n\n", i, eliminado->nome);
        i++; //incrementa contagem de eliminados

        exibirLista(noInicial); //lista atualizada

        free(eliminado); //libera a memória do eliminado

        if (*noInicial == (*noInicial)->ponteiro) { //se houver apenas um nó restante será o vencedor
            break;
        }

        noAtual = noAnterior->ponteiro; //a contagem deve começar a partir do próximo nó
    }

    if (*noInicial != NULL) {
        printf("\n\nVENCEDOR: %s\n", (*noInicial)->nome);
    }
}

int main() {
    no *noInicial = NULL;
    int n, m, i;
    char nome[TAMSTR];

    printf( "-----------------------------\n"
            " JOSEPHUS VIAGEM DE CRUZEIRO\n"
            "--------- ☆ ☆ ☆ ☆ ☆ ---------\n\n"
            "Número de clientes que participarão do sorteio: ");
    scanf("%d", &n);
    printf("\nCADASTRO DOS NOMES\n\n");
    for (i = 0; i < n; i++) {
        printf("Cliente %d: ", i + 1);
        scanf("%s", nome);
        adicionarNoFinal(&noInicial, nome);
    }

    printf("\nDigite o número m sorteado: ");
    scanf("%d", &m);

    rodarJosephus(&noInicial, m);
    destruirLista(&noInicial); //falta a implementação desse!!!

    return 0;
}
