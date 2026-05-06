#include <stdio.h>
#include <stdint.h>

#define PLN_LU(n) printf("%lu\n", n)

uint64_t rcsFactorial(uint64_t n) {
    if(n <= 1) {
        return 1;
    }

    return n * rcsFactorial(n - 1);
}

uint64_t itrFactorial(uint64_t n) {
    uint64_t output = 1;

    for(uint64_t f = 2; f <= n; f++) {
        output *= f;
    }

    return output;
}

int main() {
    uint64_t fi, fr;

    for(uint64_t i = 0; i < 1000000; i++) {
        fi = itrFactorial(15);
        fr = rcsFactorial(15);
    }

    printf("fi = %lu, fr = %lu\n", fi, fr);

    return 0;
}