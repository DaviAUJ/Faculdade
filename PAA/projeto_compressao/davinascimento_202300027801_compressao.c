#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <time.h>

#define SET_BIT(arr, bit) (arr[(bit) / 8] |= (1 << (7 - (bit) % 8)))
#define CHECK_BIT(arr, bit) ((arr[(bit) / 8] & (1 << (7 - (bit) % 8))) ? 1 : 0)
#define CLEAR_BIT(arr, bit) (arr[(bit) / 8] &= ~(1 << (7 - (bit) % 8)))
#define PEGARPROXTAM(var) fscanf(arqEntrada, "%hu ", &var)
#define PEGARPROXHEX(var) fscanf(arqEntrada, "%hhX ", &var)



typedef struct frequencia {
    uint8_t caracter;
    uint16_t frequencia;
    struct frequencia* filhoEsq;
    struct frequencia* filhoDir;
    struct frequencia* parente;
    bool naDir;
} st_Frequencia;

typedef struct tabela {
    st_Frequencia* no;
    uint16_t codigo;
    uint8_t numShifts;
} st_Tabela;

typedef struct string {
    uint8_t* string;
    uint16_t tamanho;
} st_String;



FILE* arqEntrada;
FILE* arqSaida;



st_String pegarLinha() {
    st_String saida;

    PEGARPROXTAM(saida.tamanho);

    saida.string = (uint8_t*) malloc(sizeof(uint8_t) * (saida.tamanho + 1));
    saida.string[saida.tamanho] = '\0';

    for(uint16_t a = 0; a < saida.tamanho; a++) {
        PEGARPROXHEX(saida.string[a]);
    }

    return saida;
}

void printarLinha(st_String rle, st_String huffman, uint16_t tamanhoOriginal) {
    static uint32_t linhasPrintadas = 0;

    if(huffman.tamanho <= rle.tamanho) {
        char buffer[huffman.tamanho * 2 + 100];
        char* at = buffer;
        at += sprintf(at, "%u->HUF(%.2f%%)=", linhasPrintadas, huffman.tamanho * 100 / (float)tamanhoOriginal);

        for(uint16_t k = 0; k < huffman.tamanho; k++) {
            at += sprintf(at, "%02X", huffman.string[k]);
        }
        
        fprintf(arqSaida, "%s\n", buffer);
    }

    if(huffman.tamanho >= rle.tamanho) {
        char buffer[rle.tamanho * 2 + 100];
        char* at = buffer;
        at += sprintf(at, "%u->RLE(%.2f%%)=", linhasPrintadas, rle.tamanho * 100 / (float)tamanhoOriginal);

        for(uint16_t k = 0; k < rle.tamanho; k++) {
            at += sprintf(at, "%02X", rle.string[k]);
        }
    
        fprintf(arqSaida, "%s\n", buffer);
    }
    

    linhasPrintadas++;

    free(rle.string);
    free(huffman.string);
}

void trocar(st_Frequencia** var1, st_Frequencia** var2) {
    st_Frequencia* aux = *var1;
    *var1 = *var2;
    *var2 = aux;
}

void heapifyMin(st_Frequencia** vetor, int16_t inicio, int16_t fim, int16_t index) {
    uint8_t pai = index;
    uint16_t filhoEsq = 2 * index + 1 - inicio;
    uint16_t filhoDir = 2 * (index + 1) - inicio;

    if(filhoEsq <= fim && vetor[filhoEsq]->frequencia < vetor[pai]->frequencia) {
        pai = filhoEsq;
    }

    if(filhoDir <= fim && vetor[filhoDir]->frequencia < vetor[pai]->frequencia) {
        pai = filhoDir;
    }

    if(pai != index) {
        trocar(&vetor[pai], &vetor[index]);
        heapifyMin(vetor, inicio, fim, pai);
    }
}

st_Frequencia* deletarRaiz(st_Frequencia** heap, int16_t* fim) {
    st_Frequencia* removido = heap[0];

    heap[0] = heap[*fim];
    (*fim)--;

    heapifyMin(heap, 0, *fim, 0);
    
    return removido;
}

void inserirHeap(st_Frequencia** heap, int16_t* fim, st_Frequencia* inserir) {
    (*fim)++;

    heap[*fim] = inserir;

    int16_t index = *fim;
    while(index > 0) {
        int16_t parente = (index - 1) / 2;

        if(heap[index]->frequencia >= heap[parente]->frequencia) { break; }

        trocar(&heap[index], &heap[parente]);
        index = parente;
    }
}

void liberarArvore(st_Frequencia* raiz) {
    if(raiz != NULL) {
        liberarArvore(raiz->filhoEsq);
        liberarArvore(raiz->filhoDir);
        free(raiz);
    }
}

st_String RLE(st_String string) {
    uint8_t* stringComprimida = (uint8_t*) malloc(sizeof(uint8_t) * string.tamanho * 2 + 1);

    uint16_t indexCompressao = 0;
    uint8_t repeticoes = 1;
    uint8_t referencia = string.string[0];

    for(uint16_t b = 1; b < string.tamanho + 1; b++) {
        if(string.string[b] == referencia && repeticoes <= UINT8_MAX) {
            repeticoes++;
        }
        else {
            stringComprimida[indexCompressao++] = repeticoes;
            stringComprimida[indexCompressao++] = referencia;

            repeticoes = 1;
            referencia = string.string[b];
        }
    }

    st_String saida;
    saida.tamanho = indexCompressao;
    stringComprimida[saida.tamanho] = '\0';
    saida.string = stringComprimida;

    return saida;
}

st_String huffman(st_String string) {
    int32_t frequencias[256] = {0};
    st_Frequencia* fila[256];
    st_Tabela tabela[256];
    st_String saida;
    
    for(int16_t e = 0; e < string.tamanho; e++) {
        frequencias[string.string[e]]++;
    }
    
    int16_t fim = -1;
    for(int16_t i = 0; i <= 255; i++) {
        if(frequencias[i]) {
            st_Frequencia* inserir = (st_Frequencia*) malloc(sizeof(st_Frequencia));
            inserir->caracter = i;
            inserir->filhoDir = NULL;
            inserir->filhoEsq = NULL;
            inserir->frequencia = frequencias[i];
            inserir->parente = NULL;

            inserirHeap(fila, &fim, inserir);

            tabela[i].no = inserir;
        }
        else {
            tabela[i].no = NULL;
        }
    }

    st_Frequencia* raiz = fila[0]; 
    tabela[raiz->caracter].numShifts = 1;
    tabela[raiz->caracter].codigo = 0;

    while(fim > 0) {
        raiz = (st_Frequencia*) malloc(sizeof(st_Frequencia));
        raiz->caracter = 0;
        
        fila[0]->parente = raiz;
        fila[0]->naDir = false;
        raiz->frequencia = fila[0]->frequencia;
        raiz->filhoEsq = deletarRaiz(fila, &fim);
        
        fila[0]->parente = raiz;
        fila[0]->naDir = true;
        raiz->frequencia += fila[0]->frequencia;
        raiz->filhoDir = deletarRaiz(fila, &fim);
        
        inserirHeap(fila, &fim, raiz);
    }

    if(raiz->filhoEsq != NULL && raiz->filhoDir != NULL) {
        for(int16_t g = 0; g < UINT8_MAX + 1; g++) {
            st_Frequencia* viajante = tabela[g].no;
            
            if(viajante != NULL) {
                tabela[g].numShifts = 0;
                tabela[g].codigo = 0;
    
                while(viajante != raiz) {
                    if(viajante->naDir) {
                        tabela[g].codigo += 32768;
                    }
                    
                    tabela[g].codigo >>= 1;
                    tabela[g].numShifts++;
                    
                    viajante = viajante->parente;
                }
        
                tabela[g].codigo >>= (16 - tabela[g].numShifts - 1);
            }
        }
    }
    
    uint32_t tamanhoBits = 0;
    for(int16_t i = 0; i < string.tamanho; i++) {
        tamanhoBits += tabela[string.string[i]].numShifts;
    }

    saida.tamanho = tamanhoBits / 8 + (tamanhoBits % 8 ? 1 : 0);

    saida.string = (uint8_t*)calloc(saida.tamanho + 1, sizeof(uint8_t));

    uint32_t posBit = -1;
    for(int m = 0; m < string.tamanho; m++) {
        st_Tabela caracterDaVez = tabela[string.string[m]];
        
        posBit += caracterDaVez.numShifts;
        for(uint8_t n = 0; n < caracterDaVez.numShifts; n++) {
            if(caracterDaVez.codigo % 2) {
                SET_BIT(saida.string, posBit - n);
            }
            else {
                CLEAR_BIT(saida.string, posBit - n);
            }
            
            caracterDaVez.codigo >>= 1;
        }
    }

    liberarArvore(raiz);

    return saida;
}

int main(int argc, char** argv) {
    arqEntrada = fopen(argv[1], "r");
    arqSaida = fopen(argv[2], "w");

    uint32_t linhas;
    fscanf(arqEntrada, "%d ", &linhas);

    for(int l = 0; l < linhas; l++) {
        st_String original = pegarLinha();
        printarLinha(RLE(original), huffman(original), original.tamanho);
        free(original.string);
    }

    fclose(arqEntrada);
    fclose(arqSaida);

    return 0;
}