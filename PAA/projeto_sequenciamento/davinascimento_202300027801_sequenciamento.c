#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>



#define TAMDNA 31
#define TAMGENE 1001

#define PSTRING(var) printf("%s\n", var)
#define PINT(var) printf("%d\n", var)

#define PEGARINT(var) fscanf(arqEntrada, "%d ", &var)
#define PEGARDNA(ptr) fscanf(arqEntrada, "%30s ", ptr)
#define PEGARGENE(ptr) fscanf(arqEntrada, "%1000s ", ptr)
#define PFRESULTADO(var) fscanf(arqSaida, "%s->%d%%\n", var.nome, (int32_t)roundf(var.chance))



typedef struct resultado {
    char nome[TAMGENE];
    float chance;
} resultado_t;

FILE* arqEntrada;
FILE* arqSaida;
char DNA[TAMDNA];

static inline void merge(resultado_t* vetor, int32_t inicio, int32_t meio, int32_t fim) {
    int32_t i, j, k;
    int32_t n1 = meio - inicio + 1;
    int32_t n2 = fim - meio;

    resultado_t vetorEsq[n1], vetorDir[n2];

    for(i = 0; i < n1; i++) {
        vetorEsq[i] = vetor[inicio + i];
    }

    for(j = 0; j < n2; j++) {
        vetorDir[j] = vetor[meio + j + 1];
    }

    i = 0;
    j = 0;
    k = inicio;

    while(i < n1 && j < n2) {
        if(vetorEsq[i].chance >= vetorDir[j].chance) {
            vetor[k] = vetorEsq[i];
            i++;
        }
        else {
            vetor[k] = vetorDir[j];
            j++;
        }

        k++;
    }

    while(i < n1) {
        vetor[k] = vetorEsq[i];
        i++;
        k++;
    }

    while(j < n2) {
        vetor[k] = vetorDir[j];
        j++;
        k++;
    }
}

void mergeSort(resultado_t* vetor, int32_t inicio, int32_t fim) {
    if(inicio < fim) {
        int32_t meio = inicio + (fim - inicio) / 2;

        mergeSort(vetor, inicio, meio);
        mergeSort(vetor, meio + 1, fim);

        merge(vetor, inicio, meio, fim);
    }
}

bool kmp(char* encontrar, int32_t inicio, int32_t fim) {

}

int main(int argc, char** argv) {
    int32_t subcadeia;
    int32_t numDoencas;
    
    arqEntrada = fopen(argv[1], "r");
    PEGARINT(subcadeia);
    PEGARDNA(DNA);
    PEGARINT(numDoencas);
    
    resultado_t tabela[numDoencas];

    for(int32_t i_Doencas; i_Doencas < numDoencas; i_Doencas++) {
        resultado_t resultado;
        int32_t numGenes;
        float parcela;
        
        PEGARGENE(resultado.nome);
        resultado.chance = 1;
        PEGARINT(numGenes);
        parcela = 1 / (float) numGenes;
        
        for(int32_t i_Gene = 0; i_Gene < numGenes; i_Gene++) {
            char gene[TAMGENE];
            int32_t subcadeiasValidas;
            int32_t i_Subcadeia = 0;
            int32_t limite;
            
            PEGARGENE(gene);
            
            while(gene[i_Subcadeia] != '\0') {
                i_Subcadeia++;
            }
            
            subcadeiasValidas = i_Subcadeia;
            limite = (int32_t) ceilf(i_Subcadeia * 0.9f);
            
            i_Subcadeia = 0;
            while(gene[i_Subcadeia] != '\0') {
                if(!kmp(gene, i_Subcadeia, i_Subcadeia + subcadeia - 1)) {
                    subcadeiasValidas--;
                    resultado.chance -= subcadeiasValidas >= limite ? 0 : parcela;
                    break;
                }
                
                i_Subcadeia++;
            }
        }
        
        tabela[i_Doencas] = resultado;
    }
    
    fclose(arqEntrada);

    arqSaida = fopen(argv[2], "w");

    mergeSort(tabela, 0, numDoencas - 1);
    
    for(int32_t i_Doenca = 0; i_Doenca < numDoencas; i_Doenca++) {
        PFRESULTADO(tabela[i_Doenca]);
    }

    fclose(arqSaida);

    return 0;
}