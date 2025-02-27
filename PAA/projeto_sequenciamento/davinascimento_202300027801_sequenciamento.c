#include <stdint.h>
#include <stdio.h>

int main(int argc, char** argv) {
    const FILE* ENTRADA = fopen(argv[1], "r");
    const FILE* SAIDA = fopen(argv[2], "w");

    return 0;
}