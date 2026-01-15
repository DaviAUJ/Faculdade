#include <stdio.h>
#include <math.h>
#include <stdint.h>

int64_t intpow(int64_t base, uint64_t exp) {
    int64_t output = 1;

    for(uint64_t i = 0; i < exp; i++) {
        output *= base;
    }

    return output;
}

int main(int argc, char** argv) {
    FILE* input = fopen(argv[1], "r");
    FILE* output = fopen(argv[2], "w");
    int a;

    fscanf(input, "%d ", &a);

    while(a--) {
        int b, e;

        fscanf(input, "%d^%d\n", &b, &e);

        if(a != 2) {
            e--;
        }

        fprintf(output, "%lld\n", intpow(b, e));
    }

    fclose(input);
    fclose(output);

    return 0;
}