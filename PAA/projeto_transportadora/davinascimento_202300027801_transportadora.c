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
#define MAX(val1, val2) val1 >= val2 ? val1 : val2
#define ACCESS(x, y, z) tabela[(x) + (y) * numPacotes + (z) * numPacotes * maiorCarga]



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



FILE* arqEntrada;
FILE* arqSaida;
float* tabela;
int32_t maiorCarga;
int32_t maiorVolume;
int32_t numCaminhoes;
int32_t numPacotes;
char bufferSaida[1000000];



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

    tabela = (float*)malloc(sizeof(float) * maiorCarga * maiorVolume * numPacotes);

    for(int32_t i = 0; i < maiorVolume; i++) {
        for(int32_t j = 0; j < maiorCarga; j++) {
            ACCESS(0, j, i) = 0;
        }
    }

    for(int32_t i = 0; i < numPacotes; i++) {
        for(int32_t j = 0; j < maiorCarga; j++) {
            ACCESS(i, j, 0) = 0;
        }
    }

    for(int32_t i = 0; i < numPacotes; i++) {
        for(int32_t j = 0; j < maiorVolume; j++) {
            ACCESS(i, 0, j) = 0;
        }
    }
    
    float entrada;
    for(int32_t i_Id = 1; i_Id < numPacotes; i_Id++) {
        for(int32_t i_Peso = 1; i_Peso < maiorCarga; i_Peso++) {
            for(int32_t i_Volume = 1; i_Volume < maiorVolume; i_Volume++) {
                if(i_Peso < pacotes[i_Id].peso || i_Volume < pacotes[i_Id].volume) {
                    entrada = ACCESS(i_Id - 1, i_Peso, i_Volume);
                }
                else {
                    float a = ACCESS(i_Id - 1, i_Peso, i_Volume);
                    float b = ACCESS(i_Id - 1, (int) ceilf(i_Peso - pacotes[i_Id].peso), (int) ceilf(i_Volume - pacotes[i_Id].volume));
                    b += pacotes[i_Id].valor;

                    entrada = MAX(a, b);
                }
                
                ACCESS(i_Id, i_Peso, i_Volume) = entrada;
            }
        }
    }
    
    arqSaida = fopen(argv[2], "w");

    int32_t ultimoPacote = numPacotes - 1;
    for(int32_t i_caminhao = 0; i_caminhao < numCaminhoes; i_caminhao++) {
        int32_t encaminhados[100];
        int32_t numEncaminhados = 0;
        caminhao_t caminhao = caminhoes[i_caminhao];
        int32_t i_volume = caminhao.volumeMax;
        int32_t i_carga = caminhao.cargaMax;
        int32_t i_pacote;
        float volumeTotal = 0;
        float cargaTotal = 0;
        char* ptr = bufferSaida;

        

        while(ultimoPacote >= 0 && !pacotes[ultimoPacote].disponivel) {
            ultimoPacote--;
            i_pacote = ultimoPacote;

            while(i_volume >= 0 && i_carga >= 0 && i_pacote >= 1) {
                if(ACCESS(i_pacote, i_carga, i_volume) != ACCESS(i_pacote - 1, i_carga, i_volume)) {
                    i_carga -= (int32_t) ceilf(pacotes[i_pacote].peso);
                    i_volume -= (int32_t) ceilf(pacotes[i_pacote].volume);
                }
    
                i_pacote--;

                if(!pacotes[i_pacote].disponivel) {
                    pacotes[ultimoPacote].disponivel = false;
                    break;
                }
            }
        }

        i_pacote = ultimoPacote;

        while(i_volume >= 0 && i_carga >= 0 && i_pacote >= 1) {
            if(ACCESS(i_pacote, i_carga, i_volume) != ACCESS(i_pacote - 1, i_carga, i_volume)) {
                i_carga -= (int32_t) ceilf(pacotes[i_pacote].peso);
                i_volume -= (int32_t) ceilf(pacotes[i_pacote].volume);

                cargaTotal += pacotes[i_pacote].peso;
                volumeTotal += pacotes[i_pacote].volume;
                encaminhados[numEncaminhados++] = i_pacote;
            }

            i_pacote--;
        }

        

        ptr += sprintf(ptr, "[%s]R$%.2f,%.0fKG(%.0f%%),%.0f(%.0f%%)->",
            caminhao.placa,
            ACCESS(ultimoPacote, caminhao.cargaMax, caminhao.volumeMax),
            cargaTotal,
            ceilf(cargaTotal / caminhao.cargaMax * 100),
            volumeTotal,
            ceilf(volumeTotal / caminhao.volumeMax * 100)
        );

        

        while(numEncaminhados - 1) {
            numEncaminhados--;
            ptr += sprintf(ptr, "%s,", pacotes[encaminhados[numEncaminhados]].codigo);
        }

        ptr += sprintf(ptr, "%s\n", pacotes[encaminhados[numEncaminhados]].codigo);

        fprintf(arqSaida, "%s", bufferSaida);
    }


    fclose(arqSaida);
    
    free(tabela);
    free(pacotes);

    return 0;
}