#include <stdint.h>
#include <stdio.h>
#include <math.h>
#include <stdbool.h>



#define TAMDNA 40001
#define TAMGENE 1001

#define TESTE printf("TESTE\n")
#define PSTRING(var) printf("%s\n", var)
#define PINT(var) printf("%d\n", var)
#define PFLOAT(var) printf("%f\n", var)

#define PEGARINT(var) fscanf(arqEntrada, "%d ", &var)
#define PEGARDNA(ptr) fscanf(arqEntrada, "%40000s  ", ptr)
#define PEGARGENE(ptr) fscanf(arqEntrada, "%1000s ", ptr)
#define PFRESULTADO(var) fprintf(arqSaida, "%s->%d%%\n", var.nome, var.chance)



typedef struct resultado {
    char nome[TAMGENE];
    int32_t chance;
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

int main(int argc, char** argv) {
    int32_t subcadeia;
    int32_t numDoencas;
    
    arqEntrada = fopen(argv[1], "r");
    PEGARINT(subcadeia);
    PEGARDNA(DNA);
    PEGARINT(numDoencas);
    
    resultado_t tabela[numDoencas];

    for(int32_t i_Doencas = 0; i_Doencas < numDoencas; i_Doencas++) {
        resultado_t resultado;
        int32_t numGenes;
        float parcela;
        float chance = 1;
        
        PEGARGENE(resultado.nome);
        PEGARINT(numGenes);
        parcela = 1 / (float) numGenes;
        
        for(int32_t i_Gene = 0; i_Gene < numGenes; i_Gene++) {
            char gene[TAMGENE];
            int32_t i_CharGene = 0;
            int32_t i_CharDNA = 0;
            int32_t sequencia = 0;
            int32_t encontrados = 0;
            int32_t limite;
            
            PEGARGENE(gene);
            
            while(gene[i_CharGene] != '\0') {
                i_CharGene++;
            }

            limite = (int32_t) ceilf(i_CharGene * 0.9f);
            
            i_CharGene = 0;
            while(gene[i_CharGene] != '\0') {
                if(gene[i_CharGene] == DNA[i_CharDNA]) {
                    i_CharGene++;
                    sequencia++;
                }
                else {
                    if(sequencia >= subcadeia) {
                        encontrados += sequencia;
                        i_CharDNA--;
                    }
                    else {
                        i_CharGene -= sequencia;
                        i_CharDNA -= sequencia;
                    }

                    sequencia = 0;

                    if(encontrados >= limite) {
                        break;
                    }

                    if(TAMDNA - (i_CharDNA + 2) + encontrados < limite) {
                        encontrados = 0;
                        break;
                    }
                }
                
                i_CharDNA++;
            }

            encontrados += sequencia >= subcadeia ? sequencia : 0;
            chance -= encontrados < limite ? parcela : 0;
        }
        
        resultado.chance = (int32_t)roundf(chance * 100);
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