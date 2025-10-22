#include <stdio.h>
#include <iostream>
#include <cstdint>

using namespace std;

uint64_t gcd(uint64_t a, uint64_t b) {
    uint64_t t;

    while(b) {
        a %= b;
        
        t = a;
        a = b;
        b = t;
    }

    return a;
}

uint64_t lcm(uint64_t a, uint64_t b) {
    return (a / gcd(a, b)) * b;
}

int main() {
    uint64_t a, b;

    cin >> a >> b;

    printf("GCD(%lu, %lu) = %lu\n", a, b, gcd(a, b));
    printf("LCM(%lu, %lu) = %lu\n", a, b, lcm(a, b));
}
