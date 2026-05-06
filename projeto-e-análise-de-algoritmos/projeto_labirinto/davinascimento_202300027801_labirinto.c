#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <math.h>

#define TAMBUFFER 17000000
#define TESTE printf("TESTE\n")
#define PSTRING(ptr) printf("%s\n", ptr)
#define PINT(var) printf("%d\n", var)
#define PCHAR(var) printf("%c\n", var)
//#define PHEXSEQ(ptr, x, y) for(uint16_t i = 0; i < x; i++) { printf("%2.2X%c", ptr[i], ((i+1)%y) ? ' ' : '\n'); }

typedef struct buffer {
    char armazenamento[TAMBUFFER];
    int32_t cursor;
} buffer_t;

typedef struct vector2 {
    int8_t x;
    int8_t y;
} vector2_t;

typedef struct backtrack {
    vector2_t posicao;
    uint8_t nivel;
} backtrack_t;

typedef struct pilha {
    backtrack_t* vetor;
    int16_t topo;
} pilha_t;

buffer_t bufferEntrada;  
buffer_t bufferSaida;
const vector2_t checagem[4] = {
    {1, 0}, // D
    {0, -1}, // F
    {-1, 0}, // E
    {0, 1} // T
};

uint16_t pegarInt() {
    uint8_t numChar = 0;
    uint16_t saida = 0;

    while(bufferEntrada.armazenamento[bufferEntrada.cursor] > ' ') {
        numChar++;
        bufferEntrada.cursor++;
    }

    bufferEntrada.cursor -= numChar;

    while(numChar--) {
        saida += (bufferEntrada.armazenamento[bufferEntrada.cursor++] - 48) * pow(10, numChar);
    }

    bufferEntrada.cursor += 1;

    return saida;
}

vector2_t pegarLabirinto(int8_t n_Colunas, int8_t n_Linhas, char local[n_Linhas][n_Colunas]) {
    vector2_t saida;

    for(int8_t i_Linhas = 0; i_Linhas < n_Linhas; i_Linhas++) {
        for(int8_t i_Colunas = 0; i_Colunas < n_Colunas; i_Colunas++) {
            local[i_Linhas][i_Colunas] = bufferEntrada.armazenamento[bufferEntrada.cursor];
            
            if(bufferEntrada.armazenamento[bufferEntrada.cursor] == 'X') {
                saida.x = i_Colunas;
                saida.y = i_Linhas;
            }

            bufferEntrada.cursor += 2;
        }

        bufferEntrada.cursor++;
    }

    return saida;
}

void escrever(char* string) {
    for(uint8_t i = 0; string[i] != '\0'; i++) {
        bufferSaida.armazenamento[bufferSaida.cursor++] = string[i]; 
    }
}

void escreverInt(uint16_t numero) {
    if(numero) {
        uint8_t divisor = 100;
        uint16_t d;

        do {
            d = numero / divisor;
            
            if(d) {
                bufferSaida.armazenamento[bufferSaida.cursor++] = d % 10 + 48;
            }
            
            switch(divisor) {
                case 100: divisor = 10; break;
                case 10: divisor = 1; break;
                
                default: numero = 0; break;
            }
        } while(numero);
    }
    else {
        bufferSaida.armazenamento[bufferSaida.cursor++] = '0';
    }
}

void escreverVector2(vector2_t valor) {
    escreverInt(valor.y);
    escrever(","); 
    escreverInt(valor.x); 
}

void escreverLn() {
    bufferSaida.armazenamento[bufferSaida.cursor++] = '\n';
}

int main(int argc, char** argv) {
    FILE* arquivo = fopen(argv[1], "r");
    fread(bufferEntrada.armazenamento, sizeof(char), TAMBUFFER, arquivo);
    fclose(arquivo);

    for(uint16_t l = 0, n_Labirintos = pegarInt(); l < n_Labirintos; l++) {
        int8_t n_Colunas = pegarInt();
        int8_t n_Linhas = pegarInt();
    
        char labirinto[n_Linhas][n_Colunas];
        vector2_t saida = {-1, -1};
        pilha_t pilha = {
            (backtrack_t*)malloc(sizeof(backtrack_t) * (((uint32_t)n_Linhas - 2) * (n_Colunas - 2)) + 1), 
            0
        };
        
        pilha.vetor[0].posicao = pegarLabirinto(n_Colunas, n_Linhas, labirinto);
        pilha.vetor[0].nivel = 0;

        escrever("L"); escreverInt(l); escrever(":");
        escrever("INI@"); escreverVector2(pilha.vetor[0].posicao);
        
        while(1) {
            backtrack_t* topo = &pilha.vetor[pilha.topo];

            if(topo->nivel >= 4) {
                pilha.topo--;

                if(pilha.topo < 0) {
                    escrever("|FIM@-,-\n");
                    break;
                }
                
                escrever("|BT@"); escreverVector2(topo->posicao); escrever("->");
                escreverVector2(pilha.vetor[pilha.topo].posicao);

                continue;
            }

            vector2_t proxPos = {
                topo->posicao.x + checagem[topo->nivel].x,
                topo->posicao.y + checagem[topo->nivel].y
            };

            if(labirinto[proxPos.y][proxPos.x] >= '1') {
                topo->nivel++;
                continue;
            }

            switch(topo->nivel) {
                case 0: escrever("|D->"); break;
                case 1: escrever("|F->"); break;
                case 2: escrever("|E->"); break;
                case 3: escrever("|T->");
            }

            topo->nivel++;
            
            labirinto[proxPos.y][proxPos.x] = 'X';
            topo = &pilha.vetor[++pilha.topo];
            topo->nivel = 0;
            topo->posicao = proxPos;

            escreverVector2(topo->posicao);
            
            if(topo->posicao.x == 0 || topo->posicao.x == (n_Colunas - 1) || topo->posicao.y == 0 || topo->posicao.y == (n_Linhas - 1)) {
                saida = topo->posicao;

                escrever("|FIM@");
                escreverVector2(saida);
                escreverLn();

                break;
            }
        }

        free(pilha.vetor);
    }

    arquivo = fopen(argv[2], "w");
    fwrite(bufferSaida.armazenamento, sizeof(char), bufferSaida.cursor, arquivo);
    fclose(arquivo);
    
    
    return 0;
}
