#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define TAMPLACA 8
#define TAMCODIGO 14

#define TESTE printf("TESTE\n")
#define PINT(var) printf("%d\n", var)
#define PFLOAT(var) printf("%f\n", var)
#define PSTRING(var) printf("%s\n", var)
#define PCOORD(var1, var2, var3) printf("(%d, %d, %d)\n", var1, var2, var3)

#define PEGARCAMINHAO(var) fscanf(arqEntrada, "%s %d %d ", var.placa, &var.cargaMax, &var.volumeMax)
#define PEGARPACOTE(var) fscanf(arqEntrada, "%s %f %f %f ", var.codigo, &var.valor, &var.peso, &var.volume)
#define PEGARINT(var) fscanf(arqEntrada, "%d ", &var)
#define MAX(val1, val2) val1 > val2 ? val1 : val2
#define ACCESS(x, y, z) tabela[x + y * numPacotes + z * numCaminhoes * maiorCarga]



typedef struct caminhao {
    char placa[TAMPLACA];
    int32_t cargaMax;
    int32_t volumeMax;
} caminhao_t;

typedef struct pacote {
    char codigo[TAMCODIGO];
    float valor;
    float peso;
    float volume;
    bool disponivel;
} pacote_t;

typedef struct encadeado {
    pacote_t* pacote;
    struct encadeado* proximo;
} encadeado_t;

typedef struct tabela {
    float valor;
    encadeado_t* inicio;
    encadeado_t* fim;
    bool disponivel;
} tabela_t;



FILE* arqEntrada;
FILE* arqSaida;
tabela_t* tabela;
int32_t maiorCarga;
int32_t maiorVolume;
int32_t numCaminhoes;
int32_t numPacotes;



int main(int argc, char** argv) {
    arqEntrada = fopen(argv[1], "r");
    
    PEGARINT(numCaminhoes);

    caminhao_t caminhoes[numCaminhoes];
    for(int32_t i = 0; i < numCaminhoes; i++) {
        PEGARCAMINHAO(caminhoes[i]);
        maiorCarga = MAX(maiorCarga, caminhoes[i].cargaMax);
        maiorVolume = MAX(maiorVolume, caminhoes[i].volumeMax);
    }

    numCaminhoes++;
    maiorCarga++;
    maiorVolume++;

    PEGARINT(numPacotes);

    pacote_t* pacotes = (pacote_t*)malloc(sizeof(pacote_t) * numPacotes);
    for(int32_t i = 0; i < numPacotes; i++) {
        PEGARPACOTE(pacotes[i]);
        pacotes[i].disponivel = true;
    }
    
    fclose(arqEntrada);

    tabela = (tabela_t*)malloc(sizeof(tabela_t) * maiorCarga * maiorVolume * numPacotes);

    for(int32_t i = 0; i < maiorVolume; i++) {
        for(int32_t j = 0; j < maiorCarga; j++) {
            ACCESS(0, j, i).valor = 0;
            ACCESS(0, j, i).inicio = NULL;
            ACCESS(0, j, i).fim = NULL;
            ACCESS(0, j, i).disponivel = false;
        }
    }

    for(int32_t i = 0; i < numPacotes; i++) {
        for(int32_t j = 0; j < maiorCarga; j++) {
            ACCESS(i, j, 0).valor = 0;
            ACCESS(i, j, 0).inicio = NULL;
            ACCESS(i, j, 0).fim = NULL;
            ACCESS(i, j, 0).disponivel = false;
        }
    }

    for(int32_t i = 0; i < numPacotes; i++) {
        for(int32_t j = 0; j < maiorVolume; j++) {
            ACCESS(i, 0, j).valor = 0;
            ACCESS(i, 0, j).inicio = NULL;
            ACCESS(i, 0, j).fim = NULL;
            ACCESS(i, 0, j).disponivel = false;
        }
    }
    
    tabela_t entrada;
    for(int32_t i_Id = 1; i_Id < numPacotes; i_Id++) {
        for(int32_t i_Peso = 1; i_Peso < maiorCarga; i_Peso++) {
            for(int32_t i_Volume = 1; i_Volume < maiorVolume; i_Volume++) {
                if(i_Peso < pacotes[i_Id].peso || i_Volume < pacotes[i_Id].volume) {
                    entrada = ACCESS(i_Id - 1, i_Peso, i_Volume);
                }
                else {
                    tabela_t a = ACCESS(i_Id - 1, i_Peso, i_Volume);
                    tabela_t b = ACCESS(i_Id - 1, (int) ceilf(i_Peso - pacotes[i_Id].peso), (int) ceilf(i_Volume - pacotes[i_Id].volume));
                    b.valor += pacotes[i_Id].valor;

                    if(a.valor >= b.valor) {
                        entrada = a;
                    }
                    else {
                        entrada = b;
                        entrada.inicio = (encadeado_t*) malloc(sizeof(encadeado_t));
                        entrada.inicio->pacote = &pacotes[i_Id];
                        entrada.inicio->proximo = b.inicio;
                        entrada.fim = b.fim;
                    }
                }
                
                entrada.disponivel = true;
                ACCESS(i_Id, i_Peso, i_Volume) = entrada;
            }
        }
    }
    

    arqSaida = fopen(argv[2], "w");

    fclose(arqSaida);
    
    free(tabela);
    free(pacotes);

    return 0;
}