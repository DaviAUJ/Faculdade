#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <stdbool.h>
#include <math.h>

#define TAMPLACA 8
#define TAMCODIGO 14

#define A printf("a\n")
#define PINT(var) printf("%d\n", var)
#define PSTRING(var) printf("%s\n", var)

#define PEGARCAMINHAO(var) fscanf(arqEntrada, "%s %d %d ", var.placa, &var.cargaMax, &var.volumeMax)
#define PEGARPACOTE(var) fscanf(arqEntrada, "%s %f %f %f ", var.codigo, &var.valor, &var.peso, &var.volume)
#define PEGARINT(var) fscanf(arqEntrada, "%d ", &var)
#define MAX(val1, val2) val1 > val2 ? val1 : val2
#define ACCESS(vetor, x, y, z) vetor[z][y][x]

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

typedef struct controle {
    encadeado_t* inicio;
    encadeado_t* fim;
} controle_t;

typedef struct tabela {
    float valor;
    controle_t lista;
    bool disponivel;
} tabela_t;

FILE* arqEntrada;
FILE* arqSaida;

int main(int argc, char** argv) {
    arqEntrada = fopen(argv[1], "r");
    
    int32_t numCaminhoes;
    PEGARINT(numCaminhoes);

    int32_t maiorCarga = 0;
    int32_t maiorVolume = 0;
    caminhao_t caminhoes[numCaminhoes];
    for(int32_t i = 0; i < numCaminhoes; i++) {
        PEGARCAMINHAO(caminhoes[i]);
        maiorCarga = MAX(maiorCarga, caminhoes[i].cargaMax);
        maiorVolume = MAX(maiorVolume, caminhoes[i].volumeMax);
    }

    int32_t numPacotes;
    PEGARINT(numPacotes);

    pacote_t pacotes[numPacotes];
    for(int32_t i = 0; i < numPacotes; i++) {
        PEGARPACOTE(pacotes[i]);
        pacotes[i].disponivel = true;
    }
    
    fclose(arqEntrada);

    PINT(maiorVolume);
    PINT(maiorCarga);
    tabela_t tabela[maiorVolume][maiorCarga][numPacotes];
    A;

    
    for(int32_t i = 0; i <= maiorVolume; i++) {
        for(int32_t j = 0; j <= maiorCarga; j++) {
            ACCESS(tabela, 0, j, i).valor = 0;
            ACCESS(tabela, 0, j, i).lista.inicio = NULL;
            ACCESS(tabela, 0, j, i).lista.fim = NULL;
            ACCESS(tabela, 0, j, i).disponivel = false;
        }
    }

    for(int32_t i = 0; i <= numPacotes; i++) {
        for(int32_t j = 0; j <= maiorCarga; j++) {
            ACCESS(tabela, i, j, 0).valor = 0;
            ACCESS(tabela, i, j, 0).lista.inicio = NULL;
            ACCESS(tabela, i, j, 0).lista.fim = NULL;
            ACCESS(tabela, i, j, 0).disponivel = false;
        }
    }

    for(int32_t i = 0; i <= numPacotes; i++) {
        for(int32_t j = 0; j <= maiorVolume; j++) {
            ACCESS(tabela, i, 0, j).valor = 0;
            ACCESS(tabela, i, 0, j).lista.inicio = NULL;
            ACCESS(tabela, i, 0, j).lista.fim = NULL;
            ACCESS(tabela, i, 0, j).disponivel = false;
        }
    }

    tabela_t entrada;
    for(int32_t i_Id = 1; i_Id <= numPacotes; i_Id++) {
        for(int32_t i_Peso = 1; i_Peso <= maiorCarga; i_Peso++) {
            for(int32_t i_Volume = 1; i_Volume <= maiorVolume; i_Volume++) {
                if(i_Peso < pacotes[i_Id].peso) {
                    if(i_Volume < pacotes[i_Id].volume) {
                        entrada = ACCESS(tabela, i_Id - 1, i_Peso, i_Volume);
                    }
                    else {
                        tabela_t a = ACCESS(tabela, i_Id - 1, i_Peso, i_Volume);
                        tabela_t b = ACCESS(tabela, i_Id - 1, i_Peso, (int) ceilf(i_Volume - pacotes[i_Id].volume));
                        b.valor += pacotes[i_Id].valor;

                        if(a.valor >= b.valor) {
                            entrada = a;
                        }
                        else {
                            entrada = b;
                            entrada.lista.fim->proximo = (encadeado_t*) malloc(sizeof(encadeado_t));
                            entrada.lista.fim->proximo->pacote = &pacotes[i_Id];
                            entrada.lista.fim = entrada.lista.fim->proximo;
                        }
                    }
                }
                else {
                    tabela_t a = ACCESS(tabela, i_Id - 1, i_Peso, i_Volume);
                    tabela_t b = ACCESS(tabela, i_Id - 1, (int) ceilf(i_Peso - pacotes[i_Id].peso), i_Volume);
                    b.valor += pacotes[i_Id].valor;

                    if(a.valor >= b.valor) {
                        entrada = a;
                    }
                    else {
                        entrada = b;
                        entrada.lista.fim->proximo = (encadeado_t*) malloc(sizeof(encadeado_t));
                        entrada.lista.fim->proximo->pacote = &pacotes[i_Id];
                        entrada.lista.fim = entrada.lista.fim->proximo;
                    }
                }

                entrada.disponivel = true;
                ACCESS(tabela, i_Id, i_Peso, i_Volume) = entrada;
            }
        }
    }

    arqSaida = fopen(argv[2], "w");

    fclose(arqSaida);

    return 0;
}