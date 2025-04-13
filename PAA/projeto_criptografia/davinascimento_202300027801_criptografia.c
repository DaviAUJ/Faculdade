#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include <stdbool.h>

#define PINT(var) printf("%d\n", var)
#define PLINT(var) printf("%ld\n", var)
#define PHEX(var) printf("%2X\n", var)
#define PLHEX(var) printf("%lX\n", var)
#define PSTRING(ptr) printf("%s\n", ptr)
#define PLN printf("\n")
#define TESTE printf("Teste\n")





// SEÇÃO PARA ENCRIPTAÇÃO AES

#define PHEXSEQ(ptr, x, y) for(uint16_t i = 0; i < x; i++) { printf("%2.2X%c", ptr[i], ((i+1)%y) ? ' ' : '\n'); }

typedef enum keySize {
    SIZE_16 = 16,
    SIZE_24 = 24,
    SIZE_32 = 32
} keySize_m;

typedef enum expandedKeySize {
    EXPANDED_SIZE_16 = 176,
    EXPANDED_SIZE_24 = 208,
    EXPANDED_SIZE_32 = 240
} expandedKeySize_m;

typedef enum roundsNumber {
    ROUNDS_NUMBER_16 = 10,
    ROUNDS_NUMBER_24 = 12,
    ROUNDS_NUMBER_32 = 14
} roundsNumber_m;

typedef struct AESkey {
    uint8_t* sequence;
    keySize_m size;
} AESkey_t;

typedef struct expandedAESkey {
    uint8_t* sequence;
    expandedKeySize_m size;
} expandedAESkey_t;

const uint8_t sbox[256] = {
    //0     1    2      3     4    5     6     7      8    9     A      B    C     D     E     F
    0x63, 0x7c, 0x77, 0x7b, 0xf2, 0x6b, 0x6f, 0xc5, 0x30, 0x01, 0x67, 0x2b, 0xfe, 0xd7, 0xab, 0x76, //0
    0xca, 0x82, 0xc9, 0x7d, 0xfa, 0x59, 0x47, 0xf0, 0xad, 0xd4, 0xa2, 0xaf, 0x9c, 0xa4, 0x72, 0xc0, //1
    0xb7, 0xfd, 0x93, 0x26, 0x36, 0x3f, 0xf7, 0xcc, 0x34, 0xa5, 0xe5, 0xf1, 0x71, 0xd8, 0x31, 0x15, //2
    0x04, 0xc7, 0x23, 0xc3, 0x18, 0x96, 0x05, 0x9a, 0x07, 0x12, 0x80, 0xe2, 0xeb, 0x27, 0xb2, 0x75, //3
    0x09, 0x83, 0x2c, 0x1a, 0x1b, 0x6e, 0x5a, 0xa0, 0x52, 0x3b, 0xd6, 0xb3, 0x29, 0xe3, 0x2f, 0x84, //4
    0x53, 0xd1, 0x00, 0xed, 0x20, 0xfc, 0xb1, 0x5b, 0x6a, 0xcb, 0xbe, 0x39, 0x4a, 0x4c, 0x58, 0xcf, //5
    0xd0, 0xef, 0xaa, 0xfb, 0x43, 0x4d, 0x33, 0x85, 0x45, 0xf9, 0x02, 0x7f, 0x50, 0x3c, 0x9f, 0xa8, //6
    0x51, 0xa3, 0x40, 0x8f, 0x92, 0x9d, 0x38, 0xf5, 0xbc, 0xb6, 0xda, 0x21, 0x10, 0xff, 0xf3, 0xd2, //7
    0xcd, 0x0c, 0x13, 0xec, 0x5f, 0x97, 0x44, 0x17, 0xc4, 0xa7, 0x7e, 0x3d, 0x64, 0x5d, 0x19, 0x73, //8
    0x60, 0x81, 0x4f, 0xdc, 0x22, 0x2a, 0x90, 0x88, 0x46, 0xee, 0xb8, 0x14, 0xde, 0x5e, 0x0b, 0xdb, //9
    0xe0, 0x32, 0x3a, 0x0a, 0x49, 0x06, 0x24, 0x5c, 0xc2, 0xd3, 0xac, 0x62, 0x91, 0x95, 0xe4, 0x79, //A
    0xe7, 0xc8, 0x37, 0x6d, 0x8d, 0xd5, 0x4e, 0xa9, 0x6c, 0x56, 0xf4, 0xea, 0x65, 0x7a, 0xae, 0x08, //B
    0xba, 0x78, 0x25, 0x2e, 0x1c, 0xa6, 0xb4, 0xc6, 0xe8, 0xdd, 0x74, 0x1f, 0x4b, 0xbd, 0x8b, 0x8a, //C
    0x70, 0x3e, 0xb5, 0x66, 0x48, 0x03, 0xf6, 0x0e, 0x61, 0x35, 0x57, 0xb9, 0x86, 0xc1, 0x1d, 0x9e, //D
    0xe1, 0xf8, 0x98, 0x11, 0x69, 0xd9, 0x8e, 0x94, 0x9b, 0x1e, 0x87, 0xe9, 0xce, 0x55, 0x28, 0xdf, //E
    0x8c, 0xa1, 0x89, 0x0d, 0xbf, 0xe6, 0x42, 0x68, 0x41, 0x99, 0x2d, 0x0f, 0xb0, 0x54, 0xbb, 0x16  //F
};

const uint8_t rcon[255] = {
    0x8d, 0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8,
    0xab, 0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3,
    0x7d, 0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f,
    0x25, 0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d,
    0x01, 0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab,
    0x4d, 0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d,
    0xfa, 0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25,
    0x4a, 0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01,
    0x02, 0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d,
    0x9a, 0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa,
    0xef, 0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a,
    0x94, 0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02,
    0x04, 0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a,
    0x2f, 0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef,
    0xc5, 0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94,
    0x33, 0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb, 0x8d, 0x01, 0x02, 0x04,
    0x08, 0x10, 0x20, 0x40, 0x80, 0x1b, 0x36, 0x6c, 0xd8, 0xab, 0x4d, 0x9a, 0x2f,
    0x5e, 0xbc, 0x63, 0xc6, 0x97, 0x35, 0x6a, 0xd4, 0xb3, 0x7d, 0xfa, 0xef, 0xc5,
    0x91, 0x39, 0x72, 0xe4, 0xd3, 0xbd, 0x61, 0xc2, 0x9f, 0x25, 0x4a, 0x94, 0x33,
    0x66, 0xcc, 0x83, 0x1d, 0x3a, 0x74, 0xe8, 0xcb
};

expandedKeySize_m getExpandedSize(AESkey_t key) {
    switch(key.size) {
        case SIZE_16: return EXPANDED_SIZE_16;
        case SIZE_24: return EXPANDED_SIZE_24;
        case SIZE_32: return EXPANDED_SIZE_32;
        
        default:      return EXPANDED_SIZE_16;
    }
}

roundsNumber_m getRoundsNumber(AESkey_t key) {
    switch(key.size) {
        case SIZE_16: return ROUNDS_NUMBER_16;
        case SIZE_24: return ROUNDS_NUMBER_24;
        case SIZE_32: return ROUNDS_NUMBER_32;

        default:      return ROUNDS_NUMBER_16;
    }
}

void rotate(uint8_t* word) {
    uint8_t a = word[0];

    for(uint8_t i = 0; i < 3; i++) {
        word[i] = word[i + 1];
    }

    word[3] = a;
}

uint8_t* createRoundKey(expandedAESkey_t expandedKey, uint8_t section) {
    uint8_t* output = (uint8_t*) malloc(sizeof(uint8_t) * 16);

    for(uint8_t i = 0; i < 4; i++) {
        for(uint8_t j = 0; j < 4; j++) {
            output[i + (j * 4)] = expandedKey.sequence[section * 16 + i * 4 + j];
        }
    }

    return output;
}

void addRoundKey(uint8_t* state, uint8_t* roundKey) {
    for(uint8_t i = 0; i < 16; i++) {
        state[i] ^= roundKey[i];
    }
}

void substituteBytes(uint8_t* state) {
    for(uint8_t i = 0; i < 16; i++) {
        state[i] = sbox[state[i]];
    }
}

void shiftRows(uint8_t* state) {
    uint8_t shifted[16] = {
        state[0], state[1], state[2], state[3],
        state[5], state[6], state[7], state[4],
        state[10], state[11], state[8], state[9],
        state[15], state[12], state[13], state[14],
    };

    memcpy(state, shifted, 16);
}

uint8_t galoisMult(uint8_t a, uint8_t b) {
    uint8_t output = 0;
    uint8_t m = 0x1B;

    while(b > 0) {
        output ^= (b & 1) * a;
        a = (a << 1) ^ ((a >> 7) * m);
        b >>= 1;
    }

    return output;
}

void mixColumns(uint8_t* state) {
    uint8_t column[4];

    for(uint8_t i = 0; i < 4; i++) {
        column[0] = state[0 + i];
        column[1] = state[4 + i];
        column[2] = state[8 + i];
        column[3] = state[12 + i];
        
        state[0 + i] = 
        galoisMult(column[0], 2) ^
        galoisMult(column[3], 1) ^
        galoisMult(column[2], 1) ^
        galoisMult(column[1], 3);

        state[4 + i] =
        galoisMult(column[1], 2) ^
        galoisMult(column[0], 1) ^
        galoisMult(column[3], 1) ^
        galoisMult(column[2], 3);

        state[8 + i] =
        galoisMult(column[2], 2) ^
        galoisMult(column[1], 1) ^
        galoisMult(column[0], 1) ^
        galoisMult(column[3], 3);

        state[12 + i] =
        galoisMult(column[3], 2) ^
        galoisMult(column[2], 1) ^
        galoisMult(column[1], 1) ^
        galoisMult(column[0], 3);
    }
}

expandedAESkey_t expandKey(AESkey_t originalkey) {
    expandedAESkey_t expandedKey;
    uint8_t temp[4] = {0};
    uint8_t currentSize = originalkey.size;
    uint8_t rcon_I = 1;

    expandedKey.size = getExpandedSize(originalkey);
    expandedKey.sequence = (uint8_t*) malloc(sizeof(uint8_t) * expandedKey.size);

    for(uint8_t i = 0; i < originalkey.size; i++) {
        expandedKey.sequence[i] = originalkey.sequence[i];
    }
    
    while(currentSize < expandedKey.size) {
        for(uint8_t i = 0; i < 4; i++) {
            temp[i] = expandedKey.sequence[(currentSize - 4) + i];
        }

        if(currentSize % originalkey.size == 0) {
            rotate(temp);

            for(uint8_t i = 0; i < 4; ++i) {
                temp[i] = sbox[temp[i]]; 
            }

            temp[0] ^= rcon[rcon_I++];
        }

        if(originalkey.size == SIZE_32 && (currentSize % originalkey.size == 16)) {
            for(uint8_t i = 0; i < 4; i++) {
                temp[i] = sbox[temp[i]];
            }
        }

        for(uint8_t i = 0; i < 4; i++) {
            expandedKey.sequence[currentSize] = expandedKey.sequence[currentSize - originalkey.size] ^ temp[i];
            currentSize++;
        }
    }

    return expandedKey;
}

void encrypt(uint8_t* state, AESkey_t key) {
    expandedAESkey_t expandedKey = expandKey(key);
    uint8_t* roundKey = createRoundKey(expandedKey, 0);
    roundsNumber_m rounds = getRoundsNumber(key);

    addRoundKey(state, roundKey);
    free(roundKey);

    for(uint8_t i = 1; i < rounds; i++) {
        roundKey = createRoundKey(expandedKey, i);

        substituteBytes(state);
        shiftRows(state);
        mixColumns(state);
        addRoundKey(state, roundKey);

        free(roundKey);
    }

    roundKey = createRoundKey(expandedKey, rounds);
    substituteBytes(state);
    shiftRows(state);
    addRoundKey(state, roundKey);

    free(roundKey);
    free(expandedKey.sequence);
}

// FIM SEÇÃO





// SEÇÃO PARA ARITMÉTICA

#define P2K(var) printf("%X ", var.value[var.end]); for(int8_t i = var.end - 1; i >= 0; i--) { printf("%08X ", var.value[i]); } PLN

#define MAX(a, b) a > b ? a : b
#define MIN(a, b) a < b ? a : b
#define CEIL_DIV(a, b) a / b + (a % b ? 1 : 0)

#define BITS 32
#define DIGITS 96
#define LAST_POS 95
#define HEX_PER_DIGIT 8
#define UINT2K_INIT { {0}, 0 }

const uint64_t BASE = (uint64_t)UINT32_MAX + 1;

typedef enum comparison {
    LESS = 0,
    EQUAL = 1,
    GREATER = 2
} comparison_m;

typedef struct uint2k {
    uint32_t value[DIGITS];
    uint_t8 end;
} uint2k_t;

uint2k_t add(uint2k_t* x, uint2k_t* y) {
    uint2k_t output = UINT2K_INIT;
    uint64_t result = 0;

    output.end = MAX(x->end, y->end);

    for(uint8_t i = 0; i <= output.end; i++) {
        result = (uint64_t)x->value[i] + y->value[i] + (result >> BITS);
        output.value[i] = result;
    }
    
    if(result >> BITS && output.end < DIGITS) {
        output.value[++output.end] = result >> BITS;
    }

    return output;
}

uint2k_t sub(uint2k_t* x, uint2k_t* y) {
    uint2k_t output;
    uint32_t carry = 0;

    output.end = MAX(x->end, y->end);

    for(uint8_t i = 0; i <= output.end; i++) {
        if(x->value[i] >= (y->value[i] + carry)) {
            output.value[i] = x->value[i] - (y->value[i] + carry);
        }
        else {
            uint64_t borrowed = 0;
            borrowed += x->value[i + 1];
            borrowed <<= BITS;
            borrowed += x->value[i];

            borrowed -= y->value[i] + carry;
            output.value[i] = borrowed;
            borrowed >>= BITS;
            carry = x->value[i + 1] - borrowed;
        }
    }

    while(!output.value[output.end] && output.end != 0) {
        output.end--;
    }

    return output;
}

uint2k_t shiftLeft(uint2k_t* x, uint8_t y) {
    if(!y) return *x;

    uint2k_t output = UINT2K_INIT;
    output.end = MIN(DIGITS - 1, x->end + y);

    for(uint8_t i = 0; i <= x->end; i++) {
        uint8_t index = i + y;

        if(index >= DIGITS) {
            break;
        }

        output.value[index] = x->value[i];
    }

    return output;
}

uint2k_t shiftRight(uint2k_t* x, uint8_t y) {
    if(!y) return *x;

    uint2k_t output = UINT2K_INIT;
    
    if(y >= x->end) {
        return output;
    }

    for(uint8_t i = 0; i <= x->end; i++) {
        output.value[i] = x->value[i + y];
    }

    return output;
}

uint2k_t binShiftRight(uint2k_t* x) {
    uint2k_t output = UINT2K_INIT;
    output.end = x->end;
    
    for(uint8_t i = 0; i <= x->end; i++) {
        output.value[i] = (x->value[i] >> 1) + (x->value[i + 1] << (BITS - 1));
    }

    while(!output.value[output.end] && output.end > 0) {
        output.end--;
    }

    return output;
}

comparison_m compare(uint2k_t* x, uint2k_t* y) {
    if(x->end > y->end) {
        return GREATER;
    }

    if(x->end < y->end) {
        return LESS;
    }

    for(int8_t i = x->end; i >= 0; i--) {
        if(x->value[i] == y->value[i]) {
            continue;
        }

        if(x->value[i] > y->value[i]) {
            return GREATER;
        }

        if(x->value[i] < y->value[i]) {
            return LESS;
        }
    }

    return EQUAL;
}

comparison_m compareImm32(uint2k_t* x, uint32_t y) {
    if(x->end > 0 || x->value[0] > y) {
        return GREATER;
    }

    if(x->value[0] < y) {
        return LESS;
    }

    return EQUAL;
}

uint2k_t divImm32(uint2k_t* x, uint32_t y) {
    uint2k_t output = UINT2K_INIT;

    if(!y) return output;

    output.end = x->end;
    output.value[output.end] = x->value[x->end] / y;
    uint64_t r = ((uint64_t)x->value[x->end] % y) << BITS;

    for(int8_t i = x->end - 1; i >= 0; i--) {
        r += x->value[i];
        output.value[i] = r / y;
        r = (r % y) << BITS;
    }

    while(!output.value[output.end]) {
        output.end--;
    } 

    return output;
}

bool isOdd(uint2k_t* x) {
    return x->value[0] & 0x00000001;
}

uint2k_t multImm32(uint2k_t* x, uint32_t y) {
    uint2k_t output = UINT2K_INIT;
    uint64_t t = 0;
    output.end = x->end;

    if(!y) return output;

    for(uint8_t i = 0; i <= x->end; i++) {
        t = (uint64_t)x->value[i] * y + (t >> BITS);
        output.value[i] = t;
    }

    if(t >> BITS && output.end < LAST_POS) {
        output.value[++output.end] = t >> BITS; 
    }

    return output;
}

uint2k_t mult(uint2k_t* x, uint2k_t* y) {
    uint2k_t output = UINT2K_INIT;
    uint2k_t t = UINT2K_INIT;
    uint64_t r = 0;

    if(!y->end) return multImm32(x, y->value[y->end]);

    for(uint8_t ix = 0; ix <= x->end; ix++) {
        t.end = -1;

        for(uint8_t iy = 0; iy <= y->end; iy++) {
            r = (uint64_t)x->value[ix] * y->value[iy] + (r >> BITS);
            t.value[++t.end] = r;

            if(t.end >= LAST_POS) {
                t = shiftLeft(&t, ix);
                output = add(&output, &t);

                return output;
            }
        }

        if((r >> BITS) && (t.end < LAST_POS)) {
            t.value[++t.end] = r >> BITS;
        }

        t = shiftLeft(&t, ix);
        output = add(&output, &t);
    }

    return output;
}

uint2k_t modImm32(uint2k_t* x, uint32_t y) {
    uint2k_t output = UINT2K_INIT;

    if(!y) return output;

    uint64_t r = x->value[0];

    for(int8_t i = x->end; i >= 1; i--) {
        r = ((uint64_t)x->value[i] % y) << BITS;
        r += x->value[i - 1];
    }

    output.value[0] = r % y;
    output.end = 0;

    return output;
}

uint2k_t divb(uint2k_t* u, uint2k_t* v) {
    uint2k_t q = UINT2K_INIT;

    if(!v->end) return divImm32(u, v->value[0]);
    
    comparison_m c = compare(u, v);

    if(c == LESS) 
        return q;

    if(c == EQUAL) {
        q.value[0] = 1;
        return q;
    }

    uint32_t f = BASE / ((uint64_t)v->value[v->end] + 1);
    uint2k_t x = multImm32(u, f);
    uint2k_t y = multImm32(v, f);
    uint2k_t r;
    q.end = u->end - v->end;

    for(int8_t i = q.end; i >= 0; i--) {
        uint64_t xx = (uint64_t)x.value[v->end + i + 1] * BASE + (uint64_t)x.value[v->end + i];
        uint64_t qc = xx / y.value[v->end];
        uint64_t rc = xx % y.value[v->end];
        
        if(qc == BASE || (qc * y.value[y.end - 1]) > (rc * BASE + x.value[y.end + i - 1])) {
            qc--;
            rc += y.value[y.end];
        }

        if(rc < BASE) {
            if(qc == BASE || (qc * y.value[y.end - 1]) > (rc * BASE + x.value[y.end + i - 1])) {
                qc--;
                rc += y.value[y.end];
            }
        }

        r = multImm32(&y, qc);
        r = shiftLeft(&r, i);
        x = sub(&x, &r);
        q.value[i] = qc;

        if(x.value[y.end + i + 2] != 0) {
            q.value[i]--;
            y.value[y.end + 1] = 0;
            y = shiftLeft(&y, i);
            x = add(&x, &y);
        }
    }

    while(!q.value[q.end]) {
        q.end--;
    }

    return q;
}

uint2k_t modb(uint2k_t* u, uint2k_t* v) {
    uint2k_t r = UINT2K_INIT;

    if(!v->end) return modImm32(u, v->value[0]);

    comparison_m c = compare(u, v);

    if(c == LESS) 
        return *u;

    if(c == EQUAL) {
        return r;
    }

    uint32_t f = BASE / ((uint64_t)v->value[v->end] + 1);
    uint2k_t x = multImm32(u, f);
    uint2k_t y = multImm32(v, f);

    for(int8_t i = u->end - v->end; i >= 0; i--) {
        uint64_t xx = (uint64_t)x.value[v->end + i + 1] * BASE + (uint64_t)x.value[v->end + i];
        uint64_t qc = xx / y.value[v->end];
        uint64_t rc = xx % y.value[v->end];
        
        if(qc == BASE || (qc * y.value[y.end - 1]) > (rc * BASE + x.value[y.end + i - 1])) {
            qc--;
            rc += y.value[y.end];
        }

        if(rc < BASE) {
            if(qc == BASE || (qc * y.value[y.end - 1]) > (rc * BASE + x.value[y.end + i - 1])) {
                qc--;
                rc += y.value[y.end];
            }
        }

        r = multImm32(&y, qc);
        r = shiftLeft(&r, i);
        x = sub(&x, &r);

        uint8_t m = y.end + i + 2;
        if(m <= DIGITS && x.value[m] != 0) {
            y.value[y.end + 1] = 0;
            y = shiftLeft(&y, i);
            x = add(&x, &y);
        }
    }

    r = divImm32(&x, f);

    return r;
}

// uint2k_t mod(uint2k_t* x, uint2k_t* y) {
//     uint2k_t output = UINT2K_INIT;

//     if(compare(x, y) == LESS || compareImm32(y, 0) == EQUAL) {
//         return output;
//     }
    
//     int8_t shift = x->end - y->end;
//     uint2k_t divisor = shiftLeft(y, shift);
//     uint2k_t estimativa;
//     output = *x;
    
//     while(shift >= 0) {
//         P2K(output);
//         if(compare(&output, &divisor) == GREATER) {
//             estimativa = multImm32(&output, output.value[output.end] / divisor.value[divisor.end] + 1);
//             comparison_m c = compare(&output, &estimativa);
    
//             if(c == GREATER) {
//                 estimativa = add(&estimativa, &divisor);
    
//                 while(compare(&output, &estimativa) == GREATER) {
//                     estimativa = add(&estimativa, &divisor);
//                 }
    
//                 estimativa = sub(&estimativa, &divisor);
//                 output = sub(&output, &estimativa);
//             }
//             else if(c == LESS) {
//                 estimativa = sub(&estimativa, &divisor);
    
//                 while(compare(&output, &estimativa) == LESS) {
//                     estimativa = sub(&estimativa, &divisor);
//                 }
    
//                 output = sub(&output, &estimativa);
//             }
//             else {
//                 uint2k_t o = UINT2K_INIT;
//                 return o;
//             }
//         } 

//         divisor = shiftRight(&divisor, 1);
//         shift--;
//     }

//     return output;
// }

uint2k_t modpow(uint2k_t* base, uint2k_t* exponent, uint2k_t* modulus) {
    uint2k_t output = UINT2K_INIT;
    uint2k_t exponentCopy = *exponent;

    output.value[0] = 1;
    uint2k_t newBase = modb(base, modulus);

    while(true) {
        if(isOdd(&exponentCopy)) {
            output = mult(&output, &newBase);
            output = modb(&output, modulus);
        }
        
        exponentCopy = binShiftRight(&exponentCopy);
        
        if(compareImm32(&exponentCopy, 0) == EQUAL) {
            break;
        }

        //TESTE;
        //P2K(newBase);
        newBase = mult(&newBase, &newBase);
        //P2K(newBase);
        newBase = modb(&newBase, modulus);
    }

    return output;
}

//FIM SEÇÃO





// SEÇÃO PARA DIFFIE-HELLMAN

uint2k_t diffieHellman(uint2k_t* secretA, uint2k_t* secretB, uint2k_t* base, uint2k_t* mod) {
    uint2k_t output = UINT2K_INIT;
    
    output = modpow(base, secretA, mod);
    output = modpow(&output, secretB, mod);
    
    return output;
}

// AESkey_t formatKey(uint2k_t* n) {

// }

// FIM SEÇÃO





// SEÇÃO PARA I/O

#define PIN(n) for(int16_t i = -n; i <= n; i++) { printf("%02X ", bufferIn.data[bufferIn.cursor + i]); } PLN
#define POUT(n) for(int16_t i = -n; i <= n; i++) { printf("%02X ", bufferOut.data[bufferOut.cursor + i]); } PLN

#define OPEN_INPUT_FILE fileHandler = fopen(argv[1], "r")
#define OPEN_OUTPUT_FILE fileHandler = fopen(argv[2], "w")
#define CLOSE_FILE fclose(fileHandler)
#define READ_FILE fread(bufferIn.data, sizeof(char), BUFFER_IN_SIZE, fileHandler)
#define WRITE_FILE fread(bufferOut.data, sizeof(char), bufferOut.cursor, fileHandler)

#define BUFFER_IN_SIZE 5000000
#define BUFFER_OUT_SIZE 5000000
#define CHARINT_OFFSET 48
#define CHARHEX_OFFSET 55

typedef struct bufferIn {
    char data[BUFFER_IN_SIZE];
    uint32_t cursor;
} bufferIn_t;

typedef struct bufferOut {
    char data[BUFFER_OUT_SIZE];
    uint32_t cursor;
} bufferOut_t;

FILE* fileHandler;
bufferIn_t bufferIn;
bufferOut_t bufferOut;

uint8_t getOperationsQuantity() {
    uint8_t n_digits = 0;
    uint8_t output = 0;
    uint8_t multiplier = 1;

    while(bufferIn.data[bufferIn.cursor] >= '0') {
        n_digits++;
        bufferIn.cursor++;
    }

    for(uint8_t i = 1; i <= n_digits; i++) {
        output += (bufferIn.data[bufferIn.cursor - i] - CHARINT_OFFSET) * multiplier;
        multiplier *= 10;
    }

    bufferIn.cursor++;

    return output;
}

int16_t getUint2k(uint2k_t *dest) {
    uint2k_t output = UINT2K_INIT;
    int16_t r;
    int16_t n_hex = 0;

    while(bufferIn.data[bufferIn.cursor] >= '0') {
        n_hex++;
        bufferIn.cursor++;
    }

    r = n_hex;
    bufferIn.cursor -= n_hex;
    output.end = CEIL_DIV(n_hex, HEX_PER_DIGIT) - 1;
    n_hex--;

    for(int8_t i_digit = output.end; i_digit >= 0;) {
        uint32_t digit = bufferIn.data[bufferIn.cursor];
        output.value[i_digit] += (digit - (digit >= 'A' ? CHARHEX_OFFSET : CHARINT_OFFSET)) << ((n_hex % HEX_PER_DIGIT) * 4);
        // PINT(bufferIn.data[bufferIn.cursor]);

        bufferIn.cursor++;
        i_digit -= n_hex % HEX_PER_DIGIT ? 0 : 1;
        n_hex--;
    }

    bufferIn.cursor++;

    *dest = output;
    return r;
}

// FIM SEÇÃO



// SEÇÃO PARA MAIN

uint8_t n_operations;
int16_t sizeSecret;
uint2k_t a;
uint2k_t b;
uint2k_t genator;
uint2k_t prime;
AESkey_t key;
expandedAESkey_t expandedKey;

uint2k_t teste;

int main(int argc, char** argv) {
    OPEN_INPUT_FILE;
    READ_FILE;
    CLOSE_FILE;

    n_operations = getOperationsQuantity();

    for(uint8_t i = 0; i < 1; i++) {
        bufferIn.cursor += 3;

        getUint2k(&a);
        getUint2k(&b);
        getUint2k(&genator);
        getUint2k(&prime);
        // P2K(a);
        // P2K(b);
        // P2K(genator);
        // P2K(prime);

        // a.value[1] = 1;
        // a.value[0] = 1480040264;
        // a.end = 1;
        // b.value[1] = 2;
        // b.value[0] = 2154684645;
        // b.end = 1;
        // genator.value[1] = 3;
        // genator.value[0] = 528571556;
        // genator.end = 1;

        teste = diffieHellman(&a, &b, &genator, &prime);
        P2K(teste);
    }

    return 0;
}

// FIM SEÇÃO