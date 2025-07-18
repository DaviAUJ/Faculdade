#include <stdio.h>
#include <stdint.h>
#include <string.h>
#include <time.h>

#define PLN printf("\n")
#define P2K(var) printf("%X ", var.palavras[var.qtdPalavrasUsadas]); for(int32_t i = var.qtdPalavrasUsadas - 1; i >= 0; i--) { printf("%08X ", var.palavras[i]); } PLN

/*


            WHY SO CURIOUS?


*/

FILE* inputF;
FILE* outputF;


#define MAX_PALAVRA 4*64 // 64 * 32 == 2048 bits
#define ALIGN32 __attribute__((aligned(32)))
#define INDICE_REVERSO(i, arr, tamanho) (arr)[tamanho - 1 - (i)]


typedef struct novoInt {

    uint32_t ALIGN32 palavras[MAX_PALAVRA];
    int32_t qtdPalavrasUsadas;

} uint4096_t;


typedef struct p {
    uint4096_t segredo;
    uint4096_t chaveCompartilhada;
    int versao;
} Pessoa;

uint4096_t ZERO;


uint4096_t CHAVE_COMPARTILHADA_EXPANDIDA;
uint4096_t GERADOR;
uint4096_t MOD_PRIMO_GRANDE;

Pessoa pessoaA;
Pessoa pessoaB;


const uint8_t SBOX[256] = {
    0x63, 0x7C, 0x77, 0x7B, 0xF2, 0x6B, 0x6F, 0xC5,
    0x30, 0x01, 0x67, 0x2B, 0xFE, 0xD7, 0xAB, 0x76,
    0xCA, 0x82, 0xC9, 0x7D, 0xFA, 0x59, 0x47, 0xF0,
    0xAD, 0xD4, 0xA2, 0xAF, 0x9C, 0xA4, 0x72, 0xC0,
    0xB7, 0xFD, 0x93, 0x26, 0x36, 0x3F, 0xF7, 0xCC,
    0x34, 0xA5, 0xE5, 0xF1, 0x71, 0xD8, 0x31, 0x15,
    0x04, 0xC7, 0x23, 0xC3, 0x18, 0x96, 0x05, 0x9A,
    0x07, 0x12, 0x80, 0xE2, 0xEB, 0x27, 0xB2, 0x75,
    0x09, 0x83, 0x2C, 0x1A, 0x1B, 0x6E, 0x5A, 0xA0,
    0x52, 0x3B, 0xD6, 0xB3, 0x29, 0xE3, 0x2F, 0x84,
    0x53, 0xD1, 0x00, 0xED, 0x20, 0xFC, 0xB1, 0x5B,
    0x6A, 0xCB, 0xBE, 0x39, 0x4A, 0x4C, 0x58, 0xCF,
    0xD0, 0xEF, 0xAA, 0xFB, 0x43, 0x4D, 0x33, 0x85,
    0x45, 0xF9, 0x02, 0x7F, 0x50, 0x3C, 0x9F, 0xA8,
    0x51, 0xA3, 0x40, 0x8F, 0x92, 0x9D, 0x38, 0xF5,
    0xBC, 0xB6, 0xDA, 0x21, 0x10, 0xFF, 0xF3, 0xD2,
    0xCD, 0x0C, 0x13, 0xEC, 0x5F, 0x97, 0x44, 0x17,
    0xC4, 0xA7, 0x7E, 0x3D, 0x64, 0x5D, 0x19, 0x73,
    0x60, 0x81, 0x4F, 0xDC, 0x22, 0x2A, 0x90, 0x88,
    0x46, 0xEE, 0xB8, 0x14, 0xDE, 0x5E, 0x0B, 0xDB,
    0xE0, 0x32, 0x3A, 0x0A, 0x49, 0x06, 0x24, 0x5C,
    0xC2, 0xD3, 0xAC, 0x62, 0x91, 0x95, 0xE4, 0x79,
    0xE7, 0xC8, 0x37, 0x6D, 0x8D, 0xD5, 0x4E, 0xA9,
    0x6C, 0x56, 0xF4, 0xEA, 0x65, 0x7A, 0xAE, 0x08,
    0xBA, 0x78, 0x25, 0x2E, 0x1C, 0xA6, 0xB4, 0xC6,
    0xE8, 0xDD, 0x74, 0x1F, 0x4B, 0xBD, 0x8B, 0x8A,
    0x70, 0x3E, 0xB5, 0x66, 0x48, 0x03, 0xF6, 0x0E,
    0x61, 0x35, 0x57, 0xB9, 0x86, 0xC1, 0x1D, 0x9E,
    0xE1, 0xF8, 0x98, 0x11, 0x69, 0xD9, 0x8E, 0x94,
    0x9B, 0x1E, 0x87, 0xE9, 0xCE, 0x55, 0x28, 0xDF,
    0x8C, 0xA1, 0x89, 0x0D, 0xBF, 0xE6, 0x42, 0x68,
    0x41, 0x99, 0x2D, 0x0F, 0xB0, 0x54, 0xBB, 0x16
};

const uint8_t SBOX_INV[256] = {
    0x52, 0x09, 0x6A, 0xD5, 0x30, 0x36, 0xA5, 0x38,
    0xBF, 0x40, 0xA3, 0x9E, 0x81, 0xF3, 0xD7, 0xFB,
    0x7C, 0xE3, 0x39, 0x82, 0x9B, 0x2F, 0xFF, 0x87,
    0x34, 0x8E, 0x43, 0x44, 0xC4, 0xDE, 0xE9, 0xCB,
    0x54, 0x7B, 0x94, 0x32, 0xA6, 0xC2, 0x23, 0x3D,
    0xEE, 0x4C, 0x95, 0x0B, 0x42, 0xFA, 0xC3, 0x4E,
    0x08, 0x2E, 0xA1, 0x66, 0x28, 0xD9, 0x24, 0xB2,
    0x76, 0x5B, 0xA2, 0x49, 0x6D, 0x8B, 0xD1, 0x25,
    0x72, 0xF8, 0xF6, 0x64, 0x86, 0x68, 0x98, 0x16,
    0xD4, 0xA4, 0x5C, 0xCC, 0x5D, 0x65, 0xB6, 0x92,
    0x6C, 0x70, 0x48, 0x50, 0xFD, 0xED, 0xB9, 0xDA,
    0x5E, 0x15, 0x46, 0x57, 0xA7, 0x8D, 0x9D, 0x84,
    0x90, 0xD8, 0xAB, 0x00, 0x8C, 0xBC, 0xD3, 0x0A,
    0xF7, 0xE4, 0x58, 0x05, 0xB8, 0xB3, 0x45, 0x06,
    0xD0, 0x2C, 0x1E, 0x8F, 0xCA, 0x3F, 0x0F, 0x02,
    0xC1, 0xAF, 0xBD, 0x03, 0x01, 0x13, 0x8A, 0x6B,
    0x3A, 0x91, 0x11, 0x41, 0x4F, 0x67, 0xDC, 0xEA,
    0x97, 0xF2, 0xCF, 0xCE, 0xF0, 0xB4, 0xE6, 0x73,
    0x96, 0xAC, 0x74, 0x22, 0xE7, 0xAD, 0x35, 0x85,
    0xE2, 0xF9, 0x37, 0xE8, 0x1C, 0x75, 0xDF, 0x6E,
    0x47, 0xF1, 0x1A, 0x71, 0x1D, 0x29, 0xC5, 0x89,
    0x6F, 0xB7, 0x62, 0x0E, 0xAA, 0x18, 0xBE, 0x1B,
    0xFC, 0x56, 0x3E, 0x4B, 0xC6, 0xD2, 0x79, 0x20,
    0x9A, 0xDB, 0xC0, 0xFE, 0x78, 0xCD, 0x5A, 0xF4,
    0x1F, 0xDD, 0xA8, 0x33, 0x88, 0x07, 0xC7, 0x31,
    0xB1, 0x12, 0x10, 0x59, 0x27, 0x80, 0xEC, 0x5F,
    0x60, 0x51, 0x7F, 0xA9, 0x19, 0xB5, 0x4A, 0x0D,
    0x2D, 0xE5, 0x7A, 0x9F, 0x93, 0xC9, 0x9C, 0xEF,
    0xA0, 0xE0, 0x3B, 0x4D, 0xAE, 0x2A, 0xF5, 0xB0,
    0xC8, 0xEB, 0xBB, 0x3C, 0x83, 0x53, 0x99, 0x61,
    0x17, 0x2B, 0x04, 0x7E, 0xBA, 0x77, 0xD6, 0x26,
    0xE1, 0x69, 0x14, 0x63, 0x55, 0x21, 0x0C, 0x7D
};

const uint32_t RCON[11] = {
    0x01000000,
    0x02000000,
    0x04000000,
    0x08000000,
    0x10000000,
    0x20000000,
    0x40000000,
    0x80000000,
    0x1B000000,
    0x36000000,
    0x00000000 // Reservado ou para completar arrays
};

const uint8_t hex_lookup[256] = {
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 0-15
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 16-31
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 32-47
    0,   1,   2,   3,   4,   5,   6,   7,   8,   9,  255, 255, 255, 255, 255, 255, // 48-63 ('0'-'9')
    255, 10,  11,  12,  13,  14,  15, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 64-79 ('A'-'F')
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 80-95
    255, 10,  11,  12,  13,  14,  15, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 96-111 ('a'-'f')
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 112-127
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 128-143
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 144-159
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 160-175
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 176-191
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 192-207
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 208-223
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, // 224-239
    255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255, 255  // 240-255
};




static inline void zeraGrande(uint4096_t* num) {
    memset(num->palavras, 0, MAX_PALAVRA * sizeof(uint32_t));
    num->qtdPalavrasUsadas = 1;
}

static inline void imprimeHexGrande( uint4096_t* num) {
    if (num->qtdPalavrasUsadas == 0) {
        printf("0x0\n");
        return;
    }

    printf("0x");
    for (int i = num->qtdPalavrasUsadas - 1; i >= 0; i--) {
        printf("%08X", num->palavras[i]);
    }
    printf("\n");
}

static inline int comparaGrande(uint4096_t* numA, uint4096_t* numB) {
    if (numA->qtdPalavrasUsadas > numB->qtdPalavrasUsadas) return 1;
    if (numA->qtdPalavrasUsadas < numB->qtdPalavrasUsadas) return -1;

    for (int i = numA->qtdPalavrasUsadas - 1; i >= 0; i--) {
        if (numA->palavras[i] > numB->palavras[i]) return 1;
        if (numA->palavras[i] < numB->palavras[i]) return -1;
    }

    return 0;
}


static inline void somaGrande (uint4096_t* numA, uint4096_t* numB, uint4096_t* resultado){

    uint32_t carryOut = 0;
    uint64_t soma;

    int maiorUso = (numA->qtdPalavrasUsadas > numB->qtdPalavrasUsadas) ? numA->qtdPalavrasUsadas : numB->qtdPalavrasUsadas;

    for (int i = 0; i < maiorUso; i++){
        soma = 0;
        soma = ((uint64_t) numB->palavras[i]) + numA->palavras[i] + carryOut;
        resultado->palavras[i] = (uint32_t)(soma & 0xFFFFFFFF);

        carryOut = soma >> 32;

    }

    if (carryOut){
        resultado->palavras[maiorUso] = carryOut;
        resultado->qtdPalavrasUsadas = maiorUso + 1;
    }
    else{
        resultado->qtdPalavrasUsadas = maiorUso;
    }

}


//A ideia é fazer um NUMERO >> 1;
static inline void dividirPorDoisGrande (uint4096_t* num){

    uint32_t sobra = 0;

    for (int i = num->qtdPalavrasUsadas - 1; i >= 0; i--){

        uint32_t novaSobra = num->palavras[i] & 1;
        num->palavras[i] >>= 1;


        if (sobra){
            num->palavras[i] |= (1U << 31);

        }

        sobra = novaSobra;

    }

    if (num->qtdPalavrasUsadas > 1 && num->palavras[num->qtdPalavrasUsadas - 1] == 0) {
        num->qtdPalavrasUsadas--;
    }


}

void multiplicaGrande(const uint4096_t* A, const uint4096_t* B, uint4096_t* resultado) {
    
    zeraGrande(resultado);
    resultado->qtdPalavrasUsadas = A->qtdPalavrasUsadas + B->qtdPalavrasUsadas;

    for (int i = 0; i < A->qtdPalavrasUsadas; i++) {
        uint64_t a = A->palavras[i];
        uint64_t carry = 0;

        for (int j = 0; j < B->qtdPalavrasUsadas; j++) {
            int k = i + j;

            uint64_t b = B->palavras[j];
            uint64_t acumulado = (uint64_t)resultado->palavras[k] + a * b + carry;

            resultado->palavras[k] = (uint32_t)(acumulado & 0xFFFFFFFF);
            carry = acumulado >> 32;
        }

        // Carry final
        int k = i + B->qtdPalavrasUsadas;
        while (carry != 0) {
            uint64_t soma = (uint64_t)resultado->palavras[k] + carry;
            resultado->palavras[k] = (uint32_t)(soma & 0xFFFFFFFF);
            carry = soma >> 32;
            k++;
        }
    }

    // Remove zeros à esquerda
    while (resultado->qtdPalavrasUsadas > 1 &&
           resultado->palavras[resultado->qtdPalavrasUsadas - 1] == 0) {
        resultado->qtdPalavrasUsadas--;
    }
}




int numeroDeBits(uint4096_t* num) {
    if (num->qtdPalavrasUsadas == 0) return 0;

    int i = num->qtdPalavrasUsadas - 1;
    uint32_t palavra = num->palavras[i];
    int bits = 32 * i;

    while (palavra) {
        palavra >>= 1;
        bits++;
    }

    return bits;
}

void setBit(uint4096_t* num, int bitPos) {
    int indexPalavra = bitPos / 32;
    int indexBit = bitPos % 32;

    if (indexPalavra >= MAX_PALAVRA) return;

    num->palavras[indexPalavra] |= (1U << indexBit);

    if ((uint32_t)(indexPalavra + 1) > num->qtdPalavrasUsadas) {
        num->qtdPalavrasUsadas = indexPalavra + 1;
    }
}

static inline void copiaBit(uint4096_t* origem, int posOrigem, uint4096_t* destino) {
    int indexPalavra = posOrigem / 32;
    int indexBit = posOrigem % 32;

    uint32_t bit = 0;
    if (indexPalavra < origem->qtdPalavrasUsadas) {
        bit = (origem->palavras[indexPalavra] >> indexBit) & 1U;
    }

    // Shift destino pra esquerda e insere bit
    uint32_t carry = 0;
    for (int i = 0; i < destino->qtdPalavrasUsadas; i++) {
        uint64_t temp = ((uint64_t)destino->palavras[i] << 1) | carry;
        destino->palavras[i] = (uint32_t)(temp & 0xFFFFFFFF);
        carry = (uint32_t)(temp >> 32);
    }

    if (carry != 0 && destino->qtdPalavrasUsadas < MAX_PALAVRA) {
        destino->palavras[destino->qtdPalavrasUsadas++] = carry;
    }

    // Inserir o bit copiado no bit 0
    destino->palavras[0] |= bit;
}

static inline void copiaGrande(uint4096_t* origem, uint4096_t* destino) {
    destino->qtdPalavrasUsadas = origem->qtdPalavrasUsadas;

    // Copia as palavras usadas da origem para o destino
    memcpy(destino->palavras, origem->palavras, origem->qtdPalavrasUsadas * sizeof(uint32_t));

    // Zera o restante das palavras (opcional)
    if (origem->qtdPalavrasUsadas < MAX_PALAVRA) {
        memset(&destino->palavras[origem->qtdPalavrasUsadas], 0, 
               (MAX_PALAVRA - origem->qtdPalavrasUsadas) * sizeof(uint32_t));
    }
}

static inline void preparaExpansao(uint4096_t* origem, uint4096_t* destino) {
    destino->qtdPalavrasUsadas = origem->qtdPalavrasUsadas;

    for (uint32_t i = 0; i < origem->qtdPalavrasUsadas; i++) {
        destino->palavras[i] = INDICE_REVERSO(i, origem->palavras, origem->qtdPalavrasUsadas);
    }

    // Zera as palavras restantes (opcional, para evitar lixo)
    for (uint32_t i = origem->qtdPalavrasUsadas; i < MAX_PALAVRA; i++) {
        destino->palavras[i] = 0;
    }
}


void subtraiGrande(uint4096_t* a, uint4096_t* b, uint4096_t* resultado) {
    zeraGrande(resultado);

    uint64_t borrow = 0;
    int i;

    for (i = 0; i < a->qtdPalavrasUsadas; i++) {
        uint64_t palavraA = a->palavras[i];
        uint64_t palavraB = (i < b->qtdPalavrasUsadas) ? b->palavras[i] : 0;

        uint64_t sub = palavraA - palavraB - borrow;

        if (palavraA < palavraB + borrow) {
            borrow = 1;
        } else {
            borrow = 0;
        }

        resultado->palavras[i] = (uint32_t)(sub & 0xFFFFFFFF);
    }

    // Remove zeros à esquerda
    int ult = a->qtdPalavrasUsadas - 1;
    while (ult > 0 && resultado->palavras[ult] == 0) {
        ult--;
    }

    resultado->qtdPalavrasUsadas = ult + 1;
}





static inline void multiplicaPorUint32(const uint4096_t* grande, uint32_t pequeno, uint4096_t* resultado) {
    uint64_t carry = 0;
    uint32_t i;

    for (i = 0; i < grande->qtdPalavrasUsadas; i++) {
        uint64_t produto = (uint64_t)grande->palavras[i] * pequeno + carry;
        resultado->palavras[i] = (uint32_t)(produto & 0xFFFFFFFF);
        carry = produto >> 32;
    }

    if (carry != 0 && i < MAX_PALAVRA) {
        resultado->palavras[i++] = (uint32_t)carry;
    }

    // Atualiza qtdPalavrasUsadas corretamente
    while (i > 1 && resultado->palavras[i - 1] == 0) {
        i--;
    }
    resultado->qtdPalavrasUsadas = i;
    // Zera o resto, se sobrar lixo de uso anterior
    for (uint32_t j = i; j < resultado->qtdPalavrasUsadas; j++) {
        resultado->palavras[j] = 0;
    }
}


static inline void divideGrandeComResto(uint4096_t* dividendo, uint4096_t* divisor, uint4096_t* quociente, uint4096_t* resto) {
    zeraGrande(quociente);
    zeraGrande(resto);

    if (comparaGrande(divisor, &ZERO) == 0) {
        printf("Erro: divisão por zero.\n");
        return;
    }

    if (comparaGrande(dividendo, divisor) < 0) {
        // Se dividendo < divisor, quociente = 0 e resto = dividendo
        copiaGrande(dividendo, resto);
        return;
    }

    int n = dividendo->qtdPalavrasUsadas;

    static uint4096_t tempMultiplo, tempSub, tempCandidato;
    zeraGrande(&tempMultiplo);
    zeraGrande(&tempSub);
    zeraGrande(&tempCandidato);

    for (int i = n - 1; i >= 0; i--) {
        // Deslocar o resto para a esquerda em 32 bits (uma palavra) e adicionar nova palavra
        for (int j = resto->qtdPalavrasUsadas; j > 0; j--) {
            if (j < MAX_PALAVRA)
                resto->palavras[j] = resto->palavras[j - 1];
        }
        resto->palavras[0] = dividendo->palavras[i];

        if (resto->qtdPalavrasUsadas < MAX_PALAVRA)
            resto->qtdPalavrasUsadas++;

        // Normalização: garantir que não tenha palavras altas zeradas
        while (resto->qtdPalavrasUsadas > 1 && resto->palavras[resto->qtdPalavrasUsadas - 1] == 0)
            resto->qtdPalavrasUsadas--;

        // Estimar quociente parcial com busca binária
        uint32_t q = 0;
        uint32_t low = 0, high = 0xFFFFFFFF;
        while (low <= high) {
            uint32_t mid = low + ((high - low) / 2);
            multiplicaPorUint32(divisor, mid, &tempMultiplo);
            if (comparaGrande(&tempMultiplo, resto) <= 0) {
                q = mid;
                copiaGrande(&tempMultiplo, &tempCandidato);
                low = mid + 1;
            } else {
                high = mid - 1;
            }
        }

        subtraiGrande(resto, &tempCandidato, &tempSub);
        copiaGrande(&tempSub, resto);

        // Armazena q na posição correta do quociente
        quociente->palavras[i] = q;
        if (q != 0 && quociente->qtdPalavrasUsadas < i + 1)
            quociente->qtdPalavrasUsadas = i + 1;
    }

    // Corrigir o tamanho final do quociente
    if (quociente->qtdPalavrasUsadas == 0)
        quociente->qtdPalavrasUsadas = 1;

    // Corrigir o tamanho do resto
    for (int i = MAX_PALAVRA - 1; i >= 0; i--) {
        if (resto->palavras[i] != 0) {
            resto->qtdPalavrasUsadas = i + 1;
            return;
        }
    }
    resto->qtdPalavrasUsadas = 1;
}


void extrairPalavrasMaisAltas(uint4096_t* numero, int32_t quantidade, uint4096_t* resultado) {
    zeraGrande(resultado);

    if (quantidade <= 0 || quantidade > MAX_PALAVRA) {
        return;
    }

    if (quantidade > numero->qtdPalavrasUsadas) {
        quantidade = numero->qtdPalavrasUsadas;
    }

    int32_t inicio = numero->qtdPalavrasUsadas - quantidade;

    for (int32_t i = 0; i < quantidade; i++) {
        resultado->palavras[i] = numero->palavras[inicio + i];
    }

    resultado->qtdPalavrasUsadas = quantidade;
}

void extrairPalavrasMaisBaixas(uint4096_t* numero, int32_t quantidade, uint4096_t* resultado) {
    // Zera todo o bigint de saída
    zeraGrande(resultado);

    // Se pediram 0 ou mais que o máximo permitido, nada a fazer
    if (quantidade <= 0 || quantidade > MAX_PALAVRA) {
        return;
    }

    // Se pediram mais do que o número real de palavras usadas, limita
    if (quantidade > numero->qtdPalavrasUsadas) {
        quantidade = numero->qtdPalavrasUsadas;
    }

    // Copia as palavras de índice 0 até quantidade-1
    for (int32_t i = 0; i < quantidade; i++) {
        resultado->palavras[i] = numero->palavras[i];
    }

    // Ajusta o contador de palavras usadas em resultado
    resultado->qtdPalavrasUsadas = quantidade;
}



void deslocarParaDireita(uint4096_t* numero, int32_t bits, uint4096_t* resultado) {
    zeraGrande(resultado);

    if (bits <= 0 || numero->qtdPalavrasUsadas == 0) {
        copiaGrande(numero, resultado);
        return;
    }

    int32_t palavrasADeslocar = bits / 32;
    int32_t bitsRestantes   = bits % 32;

    // Se desloca tudo, fica zero
    if (palavrasADeslocar >= numero->qtdPalavrasUsadas) {
        return;
    }

    int32_t novaQtd = numero->qtdPalavrasUsadas - palavrasADeslocar;

    for (int32_t i = 0; i < novaQtd; i++) {
        uint32_t low  = numero->palavras[i + palavrasADeslocar];
        if (bitsRestantes == 0) {
            // sem “overflow” de shift
            resultado->palavras[i] = low;
        } else {
            uint32_t high = (i + palavrasADeslocar + 1 < numero->qtdPalavrasUsadas)
                          ? numero->palavras[i + palavrasADeslocar + 1]
                          : 0;
            resultado->palavras[i] = (low >> bitsRestantes)
                                   | (high << (32 - bitsRestantes));
        }
    }

    // ajusta qtdPalavrasUsadas e “trim” de zeros no topo
    resultado->qtdPalavrasUsadas = novaQtd;
    while (resultado->qtdPalavrasUsadas > 0
           && resultado->palavras[resultado->qtdPalavrasUsadas - 1] == 0) {
        resultado->qtdPalavrasUsadas--;
    }
}


static inline uint32_t pegarQtdBits(uint4096_t* numero){

    uint32_t ultimaPalavra = numero->palavras[numero->qtdPalavrasUsadas - 1];
    if (ultimaPalavra == 0) return 0;

    int zerosSobrando = __builtin_clz(ultimaPalavra);
    int msbNaUltimaPalavra = 32 - zerosSobrando;


    return (numero->qtdPalavrasUsadas - 1) * 32 + msbNaUltimaPalavra;

}

/*
*
*   ATENÇÃO!!!!
*   SE VOCÊ CHEGOU ATÉ AQUI, SAIBA QUE ESSE TRABALHO É INSALUBRE
*   BRUNO SAFADO
*   TEM QUE DIVIDIR ISSO AQUI EM DUAS OBRAS DO GOVERNO DOIDO
*   Dito isso, o código vai ficar com as váriveis e funções menos explicativas porque eu já estava extremamente cansado desse período
*
*
*   Demorei 100 horas totais nesse projeto, espero que tenha valido a pena
*
*
*   Obrigado.
*
*/




// b = base de cada palavra: 2^32
// mu = floor(b^{2k} / mod) = usado para reduzir T mod M sem divisão cara

void precomputarMuBarrett(uint4096_t* mod, uint4096_t* fatorDeReducaoBarrett) {
    static uint4096_t baseElev2k;
    static uint4096_t restoLixo;
    zeraGrande(&baseElev2k);
    int k = mod->qtdPalavrasUsadas;

    baseElev2k.palavras[2 * k] = 1;
    baseElev2k.qtdPalavrasUsadas = 2 * k + 1;

    divideGrandeComResto(&baseElev2k, mod, fatorDeReducaoBarrett, &restoLixo);
    
}

void reduzirModuloBarret(uint4096_t* numeroAlvo, uint4096_t* modulo, uint4096_t* fatorDeReducaoBarrett, uint4096_t* resultadoFinal) {
    

    if (comparaGrande(numeroAlvo, modulo) < 0){
        copiaGrande(numeroAlvo, resultadoFinal);
        return;
    }

    
    zeraGrande(resultadoFinal);

    int k = modulo->qtdPalavrasUsadas;

    static uint4096_t q1;
    zeraGrande(&q1);

    deslocarParaDireita(numeroAlvo, (k - 1) * 32, &q1);

    static uint4096_t q2;
    zeraGrande(&q2);

    multiplicaGrande(&q1, fatorDeReducaoBarrett, &q2);

    static uint4096_t q3;
    zeraGrande(&q3);

    deslocarParaDireita(&q2, (k + 1) * 32, &q3);

    static uint4096_t r1;
    zeraGrande(&r1);
    extrairPalavrasMaisBaixas(numeroAlvo, (k+1), &r1);

    static uint4096_t q3m, r2;
    zeraGrande(&q3m);
    zeraGrande(&r2);

    multiplicaGrande(&q3, modulo, &q3m);
    extrairPalavrasMaisBaixas(&q3m, k + 1, &r2);


    static uint4096_t r, rtemp;
    zeraGrande(&r);
    zeraGrande(&rtemp);

    

    if(comparaGrande(&r1, &r2) >= 0){
        subtraiGrande(&r1, &r2, &r);
    }
    else{
        static uint4096_t temp;
        zeraGrande(&temp);
        subtraiGrande(&r2, &r1, &temp);  // temp = r2 - r1
        subtraiGrande(modulo, &temp, &r); // r = modulo - temp
    }

    
    while (comparaGrande(&r, modulo) >= 0){
        zeraGrande(&rtemp);
        //printf("Quantidade de palavras do numero: %d\n", r.qtdPalavrasUsadas);
        //printf("Quantidade de palavras do modulo: %d\n", modulo->qtdPalavrasUsadas);
        
        subtraiGrande(&r, modulo, &rtemp);
        
        copiaGrande(&rtemp, &r);
        
        
    }

    copiaGrande(&r, resultadoFinal);
    
}

static inline int ehImpar (uint4096_t* num){

    return (num->qtdPalavrasUsadas >= 1 && num->palavras[0] % 2);
}



static inline void setValor(uint64_t valor, uint4096_t* num) {
    zeraGrande(num);
    num->palavras[0] = (uint32_t)(valor & 0xFFFFFFFF);
    num->palavras[1] = (uint32_t)(valor >> 32);
    num->qtdPalavrasUsadas = (num->palavras[1] != 0) ? 2 : 1;
}

/*
Esqueleto de como eu quero que fique a função (a^b) mod c:

BigInteger mod_exp(BigInteger base, BigInteger exp, BigInteger mod) {
    BigInteger result = 1;
    base = base % mod;

    while (exp > 0) {
        if (exp % 2 == 1)
            result = (result * base) % mod;

        exp = exp / 2;
        base = (base * base) % mod;
    }

    return result;
}

*/



static inline void modExpGrande(uint4096_t* base, uint4096_t* expoente, uint4096_t* mod, uint4096_t* resultadoFinal){
    
    static uint4096_t fatorDeBarret;
    static uint4096_t resultado;
    static uint4096_t baseMod;
    static uint4096_t expoenteTemp;
    static uint4096_t tempMul;
    static uint4096_t tempReduzido;
    static uint4096_t baseModTemp;

    //printf("-------------------------------------\n");

    //printf("A: ");
    //imprimeHexGrande(base);
    //printf("Elevado a: ");
    //imprimeHexGrande(expoente);
    //printf("Mod: ");
    //imprimeHexGrande(mod);

    setValor(1, &resultado);
    


    precomputarMuBarrett(mod, &fatorDeBarret);
    copiaGrande(base, &baseMod);

    //printf("Comecou barret ----------------------------------\n");
    reduzirModuloBarret(&baseMod, mod, &fatorDeBarret, &baseModTemp);
    copiaGrande(&baseModTemp, &baseMod);
    copiaGrande(expoente, &expoenteTemp);

    for (int i = 0; i < expoenteTemp.qtdPalavrasUsadas; i++) {
        uint32_t palavraAtual = expoenteTemp.palavras[i];
        for (int bit = 0; bit < 32; bit++) {
            if (palavraAtual & 1) {
                // resultado = (resultado * baseMod) % mod
                multiplicaGrande(&resultado, &baseMod, &tempMul);
                reduzirModuloBarret(&tempMul, mod, &fatorDeBarret, &tempReduzido);
                copiaGrande(&tempReduzido, &resultado);
            }

            // baseMod = (baseMod * baseMod) % mod
            multiplicaGrande(&baseMod, &baseMod, &tempMul);
            reduzirModuloBarret(&tempMul, mod, &fatorDeBarret, &tempReduzido);
            copiaGrande(&tempReduzido, &baseMod);

            palavraAtual >>= 1;
        }
    }

    copiaGrande(&resultado, resultadoFinal);
    //printf("Igual a: ");
    //imprimeHexGrande(resultadoFinal);

}

static inline void trucarGrandePalavra (uint4096_t* origem, uint4096_t* destino, int numeroPalavra){
    numeroPalavra = (numeroPalavra > origem->qtdPalavrasUsadas) ? origem->qtdPalavrasUsadas : numeroPalavra;
    for (int i = 0; i < numeroPalavra; i++){
        destino->palavras[i] = origem->palavras[i];
    }

    destino->qtdPalavrasUsadas = numeroPalavra;
}

void Diffie_HellmanC (Pessoa* p1, Pessoa* p2, uint4096_t* numG, uint4096_t* numMP){

    static uint4096_t S0, S1, S2, S3, S4, S5;

    copiaGrande(numG, &S0);
    copiaGrande(numMP, &S1);

    copiaGrande(&p1->segredo, &S2);
    copiaGrande(&p2->segredo, &S3);


    //Pessoa 1 calcula e envia a chave intermediária para Pessoa 2
    modExpGrande(&S0, &S2, &S1, &S4);

    copiaGrande(numG, &S0);
    copiaGrande(numMP, &S1);

    //Pessoa 2 calcula e envia a chave intermediária para Pessoa 1
    modExpGrande(&S0, &S3, &S1, &S5);

    copiaGrande(numMP, &S1);

    copiaGrande(&p1->segredo, &S2);
    copiaGrande(&p2->segredo, &S3);



    //Agora com as chaves intermediárias, calcular a chave completa

    //Pessoa 1 calcula a chave compartilhada a partir da chave intermediária da Pessoa 2
    modExpGrande(&S5, &p1->segredo, &S1, &p1->chaveCompartilhada);
    P2K(p1->chaveCompartilhada);

    if (p2->segredo.qtdPalavrasUsadas <= 4){
        trucarGrandePalavra(&p1->chaveCompartilhada, &p2->chaveCompartilhada, 4);
        p1->versao = 128;
        p2->versao = 128;
    }
    else if (p2->segredo.qtdPalavrasUsadas <= 6){
        trucarGrandePalavra(&p1->chaveCompartilhada, &p2->chaveCompartilhada, 6);
        p1->versao = 192;
        p2->versao = 192;
    }

    else{
        trucarGrandePalavra(&p1->chaveCompartilhada, &p2->chaveCompartilhada, 8);
        p1->versao = 256;
        p2->versao = 256;
    }

    copiaGrande(&p2->chaveCompartilhada, &p1->chaveCompartilhada);

    //Agora as duas pessoas possuem a mesma chave privada compartilhada de forma segura.

}


//Implementação do AES


//AES CIPHER:

static inline void rotacionarPalavra (uint32_t* palavraOriginal, uint32_t* palavraRotacionada){
    //Tenho que pegar o primeiro byte (bits) da palavra (32-bits)

    uint32_t primeiroByte = (*palavraOriginal) & 0xFF000000;
    (*palavraRotacionada) = (*palavraOriginal) << 8;
    (*palavraRotacionada) |= ((uint32_t) primeiroByte) >> 24; 
}

uint32_t trocarPalavraSBOX (uint32_t palavra){
    uint8_t byte0 = SBOX[(palavra >> 24) & 0xFF];
    uint8_t byte1 = SBOX[(palavra >> 16) & 0xFF];
    uint8_t byte2 = SBOX[(palavra >> 8) & 0xFF];
    uint8_t byte3 = SBOX[(palavra) & 0xFF];

    return (byte0 << 24 | byte1 << 16 | byte2 << 8 | byte3);
}

static inline void trocaByteSBOX (uint8_t estado[4][4]){
    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++){
            estado[r][c] = SBOX[estado[r][c]];
        }
    }
}

static inline void inverterTrocaByteSBOX (uint8_t estado[4][4]){
    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++){
            estado[r][c] = SBOX_INV[estado[r][c]];
        }
    }
}


static inline void girarLinhas (uint8_t estado[4][4]){

    uint8_t temp1 = estado [1][0];
    estado[1][0] = estado[1][1];
    estado[1][1] = estado[1][2];
    estado[1][2] = estado[1][3];
    estado[1][3] = temp1;


    temp1 = estado[2][0];
    uint8_t temp2 = estado[2][1];
    estado[2][0] = estado[2][2];
    estado[2][1] = estado[2][3];
    estado[2][2] = temp1;
    estado[2][3] = temp2;

    temp1 = estado[3][0];
    temp2 = estado[3][1];
    uint8_t temp3 = estado[3][2];
    estado[3][0] = estado[3][3];
    estado[3][1] = temp1;
    estado[3][2] = temp2;
    estado[3][3] = temp3;

}

static inline void inverterGirarLinhas (uint8_t estado[4][4]){

    uint8_t temp1 = estado [1][3];
    estado[1][3] = estado[1][2];
    estado[1][2] = estado[1][1];
    estado[1][1] = estado[1][0];
    estado[1][0] = temp1;

    temp1 = estado[2][3];
    uint8_t temp2 = estado[2][2];
    estado[2][3] = estado[2][1];
    estado[2][2] = estado[2][0];
    estado[2][1] = temp1;
    estado[2][0] = temp2;

    temp1 = estado[3][3];
    temp2 = estado[3][2];
    uint8_t temp3 = estado[3][1];
    estado[3][3] = estado[3][0];
    estado[3][2] = temp1;
    estado[3][1] = temp2;
    estado[3][0] = temp3;

   
}

static inline uint8_t multiplicarEmGF(uint8_t numA, uint8_t numB){

    uint8_t resultado = 0;

    while (numB > 0){
        if (numB & 1) resultado ^= numA;

        uint8_t overflow = numA & 0x80;
        numA <<= 1;

        if (overflow){
            numA ^= 0x1B;

        }

        numB >>= 1;
    }

    return resultado;
}

static inline void misturarColunas (uint8_t estado[4][4]){
    for(int c = 0; c < 4; c++){

        uint8_t s0 = estado[0][c];
        uint8_t s1 = estado[1][c];
        uint8_t s2 = estado[2][c];
        uint8_t s3 = estado[3][c];

        estado[0][c] = multiplicarEmGF(2, s0) ^ multiplicarEmGF(3, s1) ^ s2 ^ s3;
        estado[1][c] = s0 ^ multiplicarEmGF(2, s1) ^ multiplicarEmGF(3, s2) ^ s3;
        estado[2][c] = s0 ^ s1 ^ multiplicarEmGF(2, s2) ^ multiplicarEmGF(3, s3);
        estado[3][c] = multiplicarEmGF(3, s0) ^ s1 ^ s2 ^ multiplicarEmGF(2, s3);

    }
}

static inline void inverterMisturarColunas (uint8_t estado[4][4]){

    for(int c = 0; c < 4; c++){

        uint8_t s0 = estado[0][c];
        uint8_t s1 = estado[1][c];
        uint8_t s2 = estado[2][c];
        uint8_t s3 = estado[3][c];

        estado[0][c] = multiplicarEmGF(14, s0) ^ multiplicarEmGF(11, s1) ^ multiplicarEmGF(13, s2) ^ multiplicarEmGF(9, s3);
        estado[1][c] = multiplicarEmGF(9, s0) ^ multiplicarEmGF(14, s1) ^ multiplicarEmGF(11, s2) ^ multiplicarEmGF(13, s3);
        estado[2][c] = multiplicarEmGF(13, s0) ^ multiplicarEmGF(9, s1) ^ multiplicarEmGF(14, s2) ^ multiplicarEmGF(11, s3);
        estado[3][c] = multiplicarEmGF(11, s0) ^ multiplicarEmGF(13, s1) ^ multiplicarEmGF(9, s2) ^ multiplicarEmGF(14, s3);

    }
}

static inline void expansaoDeChave (uint4096_t* chaveOriginal, uint4096_t* chaveExpandida, int versao){
    int numeroDeRodadas = 0;
    int quantidadePalavrasChave = 0;

    switch (versao) {
        case 128:
            numeroDeRodadas = 10;
            quantidadePalavrasChave = 4;
            break;
        case 192:
            numeroDeRodadas = 12;
            quantidadePalavrasChave = 6;
            break;
        case 256:
            numeroDeRodadas = 14;
            quantidadePalavrasChave = 8;
            break;
        default:
            printf("Versao AES invalida: %d\n", versao);
            return;
    }

    int tamanhoChaveExp = 4 * (numeroDeRodadas + 1);

    preparaExpansao(chaveOriginal, chaveExpandida);
    chaveExpandida->qtdPalavrasUsadas = tamanhoChaveExp;

    for (int i = quantidadePalavrasChave; i < tamanhoChaveExp; i++){
        uint32_t temp = chaveExpandida->palavras[i-1];
        uint32_t tempRotacionada = 0;
        if (i % quantidadePalavrasChave == 0){
            rotacionarPalavra(&temp, &tempRotacionada);
            temp = trocarPalavraSBOX(tempRotacionada) ^ RCON [i / quantidadePalavrasChave - 1];
        }
        else if (quantidadePalavrasChave > 6 && (i % quantidadePalavrasChave == 4)){
            //Condição extra para o AES-256
            temp = trocarPalavraSBOX(temp);
        }

        chaveExpandida->palavras[i] = chaveExpandida->palavras[i - quantidadePalavrasChave] ^ temp;


    }


}

static inline void dadosParaEstado (uint8_t* dados, uint8_t estado[4][4]){

    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++){
            estado[r][c] = dados[r + 4*c];
        }
    }

}

static inline void estadoParaDados (uint8_t* dados, uint8_t estado[4][4]){

    for (int r = 0; r < 4; r++){
        for (int c = 0; c < 4; c++){
            dados [r + 4 * c] = estado[r][c];
        }
    }

}


static inline void adicionarChaveDaRodada (uint8_t estado[4][4], uint4096_t* chaveExpandida, int rodada){

    for (int c = 0; c < 4; c++){
        uint32_t palavra = chaveExpandida->palavras[4 * rodada + c];
        for (int r = 0; r < 4; r++){
            uint32_t byteDaVez = ((palavra >> (24 - 8 * r)) & 0xFF);
            estado[r][c] = estado[r][c] ^ byteDaVez;
        }
    }
}

void AES_ENCRIPTADOR (uint8_t estado[4][4], uint8_t* dados, uint4096_t* chaveExpandida, int versao){
    int numeroDeRodadas = 0;
    switch (versao) {
        case 128:
            numeroDeRodadas = 10;
            break;
        case 192:
            numeroDeRodadas = 12;
            break;
        case 256:
            numeroDeRodadas = 14;
            break;
        default:
            printf("Versao AES invalida: %d\n", versao);
            return;
    }

    dadosParaEstado(dados, estado);
    adicionarChaveDaRodada(estado, chaveExpandida, 0);

    for (int rodada = 1; rodada < numeroDeRodadas; rodada++){
        trocaByteSBOX(estado);
        girarLinhas(estado);
        misturarColunas(estado);
        adicionarChaveDaRodada(estado, chaveExpandida, rodada);
    }

    trocaByteSBOX(estado);
    girarLinhas(estado);
    adicionarChaveDaRodada(estado, chaveExpandida, numeroDeRodadas);


}

void AES_DECRIPTADOR (uint8_t estado[4][4], uint8_t* dados, uint4096_t* chaveExpandida, int versao){
    int numeroDeRodadas = 0;

    switch (versao) {
        case 128:
            numeroDeRodadas = 10;
            break;
        case 192:
            numeroDeRodadas = 12;
            break;
        case 256:
            numeroDeRodadas = 14;
            break;
        default:
            printf("Versao AES invalida: %d\n", versao);
            return;
    }

    dadosParaEstado(dados, estado);
    adicionarChaveDaRodada(estado, chaveExpandida, numeroDeRodadas);

    for (int rodada = numeroDeRodadas - 1; rodada > 0; rodada--){
        inverterGirarLinhas(estado);
        inverterTrocaByteSBOX(estado);
        adicionarChaveDaRodada(estado, chaveExpandida, rodada);
        inverterMisturarColunas(estado);
    }

    inverterGirarLinhas(estado);
    inverterTrocaByteSBOX(estado);
    adicionarChaveDaRodada(estado, chaveExpandida, 0);

    


}

static inline uint32_t hexParaUINT32(const char* s, int len) {
    uint32_t valor = 0;
    for (int i = 0; i < len; i++) {
        unsigned char c = (unsigned char)s[i];
        if (hex_lookup[c] == 255) {
            return 0; // Erro: caractere inválido
        }
        valor = (valor << 4) | hex_lookup[c];
    }
    return valor;
}

static inline void preencherINT2048(uint4096_t* numDestino, char* entradaHex){

    int pos = 0;
    numDestino->qtdPalavrasUsadas = 0;
    int tamanhoDaEntrada = strlen(entradaHex);
    //printf("Tamanho da entrada: %d", tamanhoDaEntrada);

    for (int i = tamanhoDaEntrada; i > 0; i -= 8){
        char miniBuffer[9] = {0};

        int inicio = (i >= 8) ? i - 8 : 0;
        int tamanho = (i >= 8) ? 8 : i;

        memcpy(miniBuffer, &entradaHex[inicio], tamanho);
        miniBuffer[tamanho] = '\0';
        numDestino->palavras[pos++] = hexParaUINT32(miniBuffer, tamanho);
    }

    numDestino->qtdPalavrasUsadas = pos;

}

static inline void converterBytesParaInt2048(uint8_t* chaveBytes, int tamanhoEmBits, uint4096_t* chave) {
    int numPalavras = tamanhoEmBits / 32;
    chave->qtdPalavrasUsadas = numPalavras;

    for (int i = 0; i < numPalavras; i++) {
        chave->palavras[i] = (chaveBytes[i * 4] << 24) |
                             (chaveBytes[i * 4 + 1] << 16) |
                             (chaveBytes[i * 4 + 2] << 8) |
                             (chaveBytes[i * 4 + 3]);
    }

    for (int i = numPalavras; i < MAX_PALAVRA; i++) {
        chave->palavras[i] = 0;
    }
}

void imprimirChave( char* titulo,  uint4096_t* chave) {
    printf("%s\n", titulo);
    for (int i = 0; i < chave->qtdPalavrasUsadas; i++) {
        printf("%08X ", chave->palavras[i]);
    }
    printf("\n");
}

static inline void imprimirChaveInvertida(uint4096_t* chave) {
    fprintf(outputF, "s=");
    for (int i = 0; i < chave->qtdPalavrasUsadas; i++) {
        fprintf(outputF, "%08X", INDICE_REVERSO(i, chave->palavras, chave->qtdPalavrasUsadas));
    }
    fprintf(outputF, "\n");
}

void imprimirChaveInvertidaTerminal( char* titulo,  uint4096_t* chave) {
    printf("s=");
    for (int i = 0; i < chave->qtdPalavrasUsadas; i++) {
        printf("%08X", INDICE_REVERSO(i, chave->palavras, chave->qtdPalavrasUsadas));
    }
    printf("\n");
}

static inline void completarEntrada(char* entradaHex) {
    int tamanhoHex = strlen(entradaHex);
    int qtdBytes = tamanhoHex / 2;
    int paddingBytes = (16 - (qtdBytes % 16)) % 16; // quantidade de bytes necessários
    int paddingHex = paddingBytes * 2; // em caracteres hexadecimais

    if (paddingHex == 0) return; // já é múltiplo de 16

    int novoTamanho = tamanhoHex + paddingHex;

    // move os dados para o final da string, abrindo espaço no início
    for (int i = tamanhoHex - 1; i >= 0; i--) {
        entradaHex[i + paddingHex] = entradaHex[i];
    }

    // preenche o início com '0's
    for (int i = 0; i < paddingHex; i++) {
        entradaHex[i] = '0';
    }

    entradaHex[novoTamanho] = '\0'; // garante término da string
}





static inline uint8_t hexParaUINT8(const char* stringHex) {
    unsigned char letra0 = (unsigned char) stringHex[0];
    unsigned char letra1 = (unsigned char) stringHex[1]; 
    
    // Verifica se os caracteres são válidos
    if (hex_lookup[letra0] == 255 || hex_lookup[letra1] == 255) {
        return 0; 
    }
    
    uint8_t high = hex_lookup[letra0]; 
    uint8_t low = hex_lookup[letra1];  
    return (high << 4) | low;      
}

typedef struct ch {
    char A[515];
    char B[515];
    char G[515];
    char P[515];
} BufferNumerosImportantes;


char bufferLinhaDados [8192];
BufferNumerosImportantes bNmerosImportantes;



int main (int argc, char* argv[]){

    clock_t inicio, fim;
    double tempoGasto;

    inicio = clock();

    printf("Esse trabalho eh insalubre meo irmao\n");
    printf("Fuja enquanto eh tempo\n");
    printf("Vulgo muito facil.\n");

    inputF = fopen(argv[1], "r");
    outputF = fopen(argv[2], "w");

    zeraGrande(&ZERO);

    int numeroDeOperacoes = 0;

    fscanf(inputF, "%d\n", &numeroDeOperacoes);

    printf("Numero total de operacoes: %d\n", numeroDeOperacoes);

    for (int i = 0; i < numeroDeOperacoes; i++){

        char operacao[5];

        fscanf(inputF, "%s", operacao);

        if (!strcmp("dh", operacao)){
            //printf("IF dh -----------------------\n");
            memset(bNmerosImportantes.A, 0, sizeof(bNmerosImportantes.A));
            memset(bNmerosImportantes.B, 0, sizeof(bNmerosImportantes.B));
            memset(bNmerosImportantes.G, 0, sizeof(bNmerosImportantes.G));
            memset(bNmerosImportantes.P, 0, sizeof(bNmerosImportantes.P));

            fscanf(inputF, "%s %s %s %s \n", bNmerosImportantes.A, bNmerosImportantes.B, bNmerosImportantes.G, bNmerosImportantes.P);
                
            //printf("Tamanho A: %llu\n", (long long unsigned) strlen(bNmerosImportantes.A));
            //printf("Tamanho B: %llu\n", (long long unsigned) strlen(bNmerosImportantes.B));
            //printf("Tamanho G: %llu\n", (long long unsigned) strlen(bNmerosImportantes.G));
            //printf("Tamanho P: %llu\n", (long long unsigned) strlen(bNmerosImportantes.P));

            preencherINT2048(&pessoaA.segredo, bNmerosImportantes.A);
            preencherINT2048(&pessoaB.segredo, bNmerosImportantes.B);
            preencherINT2048(&GERADOR, bNmerosImportantes.G);
            preencherINT2048(&MOD_PRIMO_GRANDE, bNmerosImportantes.P);

            // if (i == 0){
            //     printf("Segredo A: ");
            //     imprimeHexGrande(&pessoaA.segredo);
            //     printf("Segredo B: ");
            //     imprimeHexGrande(&pessoaB.segredo);
            //     printf("Gerador g: ");
            //     imprimeHexGrande(&GERADOR);
            //     printf("Primo p: ");
            //     imprimeHexGrande(&MOD_PRIMO_GRANDE);
            // }

            //printf("Segredo da Pessoa A: ");
            //imprimeHexGrande(&pessoaA.segredo);

                    
            //printf("Segredo da Pessoa B: ");
            //imprimeHexGrande(&pessoaB.segredo);

                    
            //printf("Gerador: ");
            //imprimeHexGrande(&GERADOR);

                    
            //printf("PRIMO GRANDE: ");
            //imprimeHexGrande(&MOD_PRIMO_GRANDE);

            Diffie_HellmanC(&pessoaA, &pessoaB, &GERADOR, &MOD_PRIMO_GRANDE);

            imprimirChaveInvertida(&pessoaA.chaveCompartilhada);
            // if (i==0){
            //     imprimirChave("Chave sem inverter: ", &pessoaA.chaveCompartilhada);
            //     printf("Qtd palavras chave compartilhada: %d\n", pessoaA.chaveCompartilhada.qtdPalavrasUsadas);
            //     imprimirChaveInvertidaTerminal("Chave compartilhada: ", &pessoaA.chaveCompartilhada);
            // }

            
            expansaoDeChave(&pessoaA.chaveCompartilhada, &CHAVE_COMPARTILHADA_EXPANDIDA, pessoaA.versao);

            //if(i==0) imprimirChave("Chave expandida: ", &CHAVE_COMPARTILHADA_EXPANDIDA);
        
        }

        else if (!strcmp("d", operacao)){
            fscanf(inputF, "%s \n", bufferLinhaDados);
            completarEntrada(bufferLinhaDados);
            int tamanhoTotalHEX = strlen(bufferLinhaDados);
            int qtdBytes = tamanhoTotalHEX / 2;
        
            int qtdBlocos = (qtdBytes + 15) / 16;
            uint8_t resultado[16 * qtdBlocos];
        
            for (int k = 0; k < qtdBlocos; k++) {
                uint8_t estado[4][4] = {0};
                uint8_t dados[16] = {0};
        
                for (int byte = 0; byte < 16; byte++) {
                    int idx = k * 16 + byte;
                    if (idx < qtdBytes) {
                        int idxHex = idx * 2;
                        char tmp[3] = {
                            bufferLinhaDados[idxHex],
                            bufferLinhaDados[idxHex + 1],
                            '\0'
                        };
                        dados[byte] = hexParaUINT8(tmp);
                    }
                }
        
                AES_DECRIPTADOR(estado, dados, &CHAVE_COMPARTILHADA_EXPANDIDA, pessoaA.versao);
                estadoParaDados(dados, estado);
                memcpy(&resultado[k * 16], dados, 16);
            }
        
            fprintf(outputF, "m=");
            for (int i = 0; i < qtdBytes; i++) { // só imprime os bytes reais
                fprintf(outputF, "%02X", resultado[i]);
            }
            fprintf(outputF, "\n");
        }

        else{
            memset(bufferLinhaDados, 0, sizeof(bufferLinhaDados));
            fscanf(inputF, "%s \n", bufferLinhaDados);
            //printf("Texto %s\n", bufferLinhaDados);
            completarEntrada(bufferLinhaDados);
            int tamanhoTotalHEX = strlen(bufferLinhaDados);
            int qtdBytes = tamanhoTotalHEX / 2;
        
            int qtdBlocos = (qtdBytes + 15) / 16;
            uint8_t resultado[16 * qtdBlocos];
        
            for (int k = 0; k < qtdBlocos; k++) {
                uint8_t estado[4][4] = {0};
                uint8_t dados[16] = {0};
        
                for (int byte = 0; byte < 16; byte++) {
                    int idx = k * 16 + byte;
                    if (idx < qtdBytes) {
                        int idxHex = idx * 2;
                        char tmp[3] = {
                            bufferLinhaDados[idxHex],
                            bufferLinhaDados[idxHex + 1],
                            '\0'
                        };
                        dados[byte] = hexParaUINT8(tmp);
                    }
                }

                /*
                printf("Bloco n %d:\n ", k);

                for (int l = 0; l < 16; l++){
                    printf("%02X ", dados[l]);
                }
                printf("\n");

                */
        
                AES_ENCRIPTADOR(estado, dados, &CHAVE_COMPARTILHADA_EXPANDIDA, pessoaA.versao);
                estadoParaDados(dados, estado);
                memcpy(&resultado[k * 16], dados, 16);
            }
        
            fprintf(outputF, "c=");
            for (int i = 0; i < qtdBytes; i++) { // só imprime os bytes reais
                fprintf(outputF, "%02X", resultado[i]);
            }
            fprintf(outputF, "\n");
        }
        

    }
    fclose(inputF);
    fclose(outputF);

    fim = clock(); // Marca o fim

    tempoGasto = (double)(fim - inicio) / CLOCKS_PER_SEC; // em segundos
    printf("Tempo total de execucao: %.6f segundos\n", tempoGasto);

    return 0;
}
