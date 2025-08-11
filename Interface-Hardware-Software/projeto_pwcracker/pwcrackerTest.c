#include <stdio.h>
#include <stdint.h>
#include <string.h>


static uint32_t ri = 0;

// Função para ajuste de semente
void hsrand(uint32_t seed) {
    ri = seed;
}


// Função de número pseudo-aleatório
uint8_t hrand() {
    // Calculando próximo número
    uint8_t* p = (uint8_t*)(&ri);
    // Calculando próximo número
    ri = (1103515245 * ri) + 12345;
    // Retornando byte de checksum

    return p[0] ^ p[1] ^ p[2] ^ p[3];
}





// Função de hash MAO-64
void MAO_64(uint8_t* hash, const char* senha) {
    // Declarando variáveis auxiliares
    uint32_t i, n = strlen(senha), nr = 32, seed = 0;

    printf("Seed pre-rounds: %02X\n", seed);

    // Geração da semente a partir da senha
    for(i = 0; i < n; i++){
        seed = (seed << 8) | ((seed >> 24) ^ senha[i]);
        printf("Seed round %d: %02X\n", i+1, seed);
    }
    

    
    // Semente dos números pseudo-aleatórios
    hsrand(seed);

     // Executando rodadas sobre os bytes do hash
    for(i = 0; i < nr; i++)
        hash[i & 0b111] = hash[i & 0b111] ^ hrand();


}





int main (int argc, char* argv[]){

    printf("Quantidade argc: %d\n", argc);

    for (int j = 1; j < argc; j++) {

        uint8_t hashGerado[8] = {0};

        char senha[40];
        strcpy(senha, argv[j]);

        MAO_64(hashGerado, senha);


        printf("Hash da senha %s [%d]: ", senha, j);
        for (int i = 0; i < 8; i++){
            printf("%02X", hashGerado[i]);
        }
        printf("\n");

    }





}

