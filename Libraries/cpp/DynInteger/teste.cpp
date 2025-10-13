#include "DynInteger.hpp"
#include <cstdio>

int main() {
    DynUint a(1llu << 63, 1);

    a.printHex();
    printf("Tamanho: %llu", a.size());

    return 0;
}
