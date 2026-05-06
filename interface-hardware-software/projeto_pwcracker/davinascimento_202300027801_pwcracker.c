#include <stdio.h>
#include <stdint.h>
#include <math.h>
#include <stdlib.h>
#include <string.h>
#include <pthread.h>

#define READ_MODE "r"
#define WRITE_MODE "w"

#define NAME_LEN 8
#define HASH_LEN 8
#define PASSWORD_LEN 4
#define BUFFER_LEN 1000000
#define CHARDEC_OFFSET 48
#define CHARHEX_OFFSET 87
#define PW_CHARS_LEN 63
#define DIC_LEN 15018508
#define N_THREADS 4



typedef struct User {
    char name[NAME_LEN + 1];
    uint8_t hash[HASH_LEN];
    char password[PASSWORD_LEN];
} User_t;

typedef struct HashRow {
    char password[PASSWORD_LEN];
    uint8_t hash[HASH_LEN];
} HashRow_t;

typedef struct FileBuffer {
    FILE* file;
    char buffer[BUFFER_LEN];
    uint32_t cursor;
} FileBuffer_t;



FileBuffer_t input;
FileBuffer_t output;

const char PW_CHARS[] = {
     2 , '0', '1', '2', '3', '4', '5', '6', '7', '8', 
    '9', 'A', 'B', 'C', 'D', 'E', 'F', 'G', 'H', 'I', 
    'J', 'K', 'L', 'M', 'N', 'O', 'P', 'Q', 'R', 'S', 
    'T', 'U', 'V', 'W', 'X', 'Y', 'Z', 'a', 'b', 'c', 
    'd', 'e', 'f', 'g', 'h', 'i', 'j', 'k', 'l', 'm', 
    'n', 'o', 'p', 'q', 'r', 's', 't', 'u', 'v', 'w', 
    'x', 'y', 'z'
};

HashRow_t dic[DIC_LEN];
User_t* all_users;
uint32_t n_users;



// --------------- Funções de Burno ---------------

uint8_t hrand(uint32_t* seed) {
    uint8_t* p = (uint8_t*) seed;

    // Calculando próximo número
    *seed = (1103515245u * *seed) + 12345u;

    return p[0] ^ p[1] ^ p[2] ^ p[3];
}

void GOU_64(uint8_t* hash, const char* senha) {
    // Declarando variáveis auxiliares
    uint32_t i, seed = 0;

    // Geração da semente a partir da senha
    for(i = 0; i < PASSWORD_LEN; i++){
        seed = (seed << 8) | ((seed >> 24) ^ (senha[i] <= 2 ? 0 : senha[i]));
    }

    // Executando rodadas sobre os bytes do hash
    for(i = 0; i < 32; i++)
        hash[i & 0b111] = hash[i & 0b111] ^ hrand(&seed);
}

// ------------------------------------------------


FileBuffer_t fileBuffer_Init(const char* file_name, const char* mode) {
    FileBuffer_t output;

    output.file = fopen(file_name, mode);
    output.cursor = 0;

    return output;
}

uint32_t readDec() {
    uint8_t num_char = 0;
    uint32_t integer = 0;

    while(input.buffer[input.cursor] > ' ') {
        num_char++;
        input.cursor++;
    }

    input.cursor -= num_char;

    while(num_char--) {
        integer += (input.buffer[input.cursor++] - CHARDEC_OFFSET) * (uint32_t)pow(10, num_char);
    }

    input.cursor++;

    return integer;
}

User_t readUser() {
    User_t user_output;
    uint8_t index = 0;

    while(input.buffer[input.cursor] != ':') {
        user_output.name[index++] = input.buffer[input.cursor++];
    }

    input.cursor++;
    user_output.name[index] = '\0';
    index = 0;

    while(input.buffer[input.cursor] != '\n') {
        user_output.hash[index] = (input.buffer[input.cursor] - (input.buffer[input.cursor] >= 'a' ? CHARHEX_OFFSET : CHARDEC_OFFSET)) << 4;
        input.cursor++;

        user_output.hash[index] += input.buffer[input.cursor] - (input.buffer[input.cursor] >= 'a' ? CHARHEX_OFFSET : CHARDEC_OFFSET);
        input.cursor++;

        index++;
    }

    input.cursor++;

    return user_output;
}

void writePassword(User_t user, const char password[PASSWORD_LEN]) {
    uint8_t name_len = strlen(user.name);
    uint8_t empty_pw_space = 2;

    memcpy(output.buffer + output.cursor, user.name, name_len);
    output.cursor += name_len;
    output.buffer[output.cursor++] = ':';

    if(password[0] != 2) {
        empty_pw_space = 0;
    }
    else if(password[1] != 2) {
        empty_pw_space = 1;
    }

    memcpy(output.buffer + output.cursor, password + empty_pw_space, PASSWORD_LEN - empty_pw_space);
    output.cursor += PASSWORD_LEN - empty_pw_space;
    output.buffer[output.cursor++] = '\n';
}

void* generatePasswords(void* offset) {
    const uint8_t offset_but_integer = *(uint8_t*)offset;

    uint8_t pw_counter[4] = {0, 0, 1, 1 + offset_but_integer};

    for(uint32_t i = offset_but_integer; i < DIC_LEN; i += N_THREADS) {
        dic[i].password[0] = PW_CHARS[pw_counter[0]];
        dic[i].password[1] = PW_CHARS[pw_counter[1]];
        dic[i].password[2] = PW_CHARS[pw_counter[2]];
        dic[i].password[3] = PW_CHARS[pw_counter[3]];

        GOU_64(dic[i].hash, dic[i].password);

        pw_counter[3] += N_THREADS;

        if(pw_counter[3] > PW_CHARS_LEN - 1) {
            pw_counter[3] -= PW_CHARS_LEN - 1;
            pw_counter[2]++;
        }

        if(pw_counter[2] > PW_CHARS_LEN - 1) {
            pw_counter[2] = 1;
            pw_counter[1]++;
        }

        if(pw_counter[1] > PW_CHARS_LEN - 1) {
            pw_counter[1] = 1;
            pw_counter[0]++;
        }
    }

    return NULL;
}

HashRow_t* searchUser(const User_t user) {
    uint32_t low = 0;
    uint32_t high = DIC_LEN - 1;

    while(low <= high) {
        const uint32_t mid = (low + high) / 2;
        const int32_t cmp = strncmp((char*)dic[mid].hash, (char*)user.hash, 8);

        if(cmp > 0) {
            high = mid - 1;
        }
        else if(cmp < 0) {
            low = mid + 1;
        }
        else {
            return &dic[mid];
        }
    }

    return NULL;
}

HashRow_t* buchaSearchUser(const User_t user) {
    for(uint32_t i = 0; i < DIC_LEN; i++) {
        // obg wyckson por me mostrar memcmp
        if(memcmp((char*)dic[i].hash, (char*)user.hash, 8) == 0) {
            return &dic[i];
        }
    }

    return NULL;
}

void* parallelSearch(void* offset) {
    const uint8_t offset_but_integer = *(uint8_t*)offset;

    for(uint32_t i = offset_but_integer; i < n_users; i += N_THREADS) {
        HashRow_t* row = buchaSearchUser(all_users[i]);

        memcpy(all_users[i].password, row->password, PASSWORD_LEN);
    }

    return NULL;
}



int main(int argc, char **argv) {
    // Me mate logo
    const uint8_t ZERO = 0;
    const uint8_t ONE = 1;
    const uint8_t TWO = 2;
    const uint8_t THREE = 3;

    pthread_t my_threads[N_THREADS];

    input = fileBuffer_Init(argv[1], READ_MODE);
    output = fileBuffer_Init(argv[2], WRITE_MODE);
    fread(input.buffer, sizeof(uint8_t), BUFFER_LEN, input.file);

    pthread_create(&my_threads[0], NULL, generatePasswords, (void*)&ZERO);
    pthread_create(&my_threads[1], NULL, generatePasswords, (void*)&ONE);
    pthread_create(&my_threads[2], NULL, generatePasswords, (void*)&TWO);
    pthread_create(&my_threads[3], NULL, generatePasswords, (void*)&THREE);

    pthread_join(my_threads[0], NULL);
    pthread_join(my_threads[1], NULL);
    pthread_join(my_threads[2], NULL);
    pthread_join(my_threads[3], NULL);

    n_users = readDec();
    all_users = (User_t*)malloc(sizeof(User_t) * n_users);

    for(uint32_t i = 0; i < n_users; i++) {
        all_users[i] = readUser();
    }

    pthread_create(&my_threads[0], NULL, parallelSearch, (void*)&ZERO);
    pthread_create(&my_threads[1], NULL, parallelSearch, (void*)&ONE);
    pthread_create(&my_threads[2], NULL, parallelSearch, (void*)&TWO);
    pthread_create(&my_threads[3], NULL, parallelSearch, (void*)&THREE);

    pthread_join(my_threads[0], NULL);
    pthread_join(my_threads[1], NULL);
    pthread_join(my_threads[2], NULL);
    pthread_join(my_threads[3], NULL);

    for(uint32_t i = 0; i < n_users; i++) {
        writePassword(all_users[i], all_users[i].password);
    }

    fwrite(output.buffer, 1, output.cursor, output.file);

    free(all_users);
    fclose(input.file);
    fclose(output.file);

    return 0;
}