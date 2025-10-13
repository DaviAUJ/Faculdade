#include "DynInteger.hpp"
#include "../Utils/MinMax.hpp"
#include <cstdio>

DynUint::DynUint(u32 value, u8 exp_size = 0) { 
    _size = 0b1llu << min(exp_size, (u8)63);

    _integer = new u32[_size];
    _integer[0] = value;
}

DynUint::DynUint(u64 value, u8 exp_size = 1) {
    _size = 0b1llu << interval((u8)1, exp_size, (u8)63);

    _integer = new u32[_size];
    *(u64*)&_integer[0] = value;
}

DynUint::~DynUint() {
    delete[] _integer;
}

//void DynUint::operator+=(const DynUint& other) {
//    u64 result;
//
//    for(u64 i = 0; i < _size; i++) {
//        
//    }
//}
//
//void DynUint::operator+=(u64 other) {
//
//}

void DynUint::doubleSize(u8 n_times = 1) {
    if(n_times == 0) {
        return;
    }

    u32* new_integer = new u32[_size << n_times];
    
}

void DynUint::printHex() const {
    for(u64 i = _size - 1; i >= 1; i--) {
        printf("%08X", _integer[i]);
    }

    printf("%u\n", _integer[0]);
}

u64 DynUint::size() const {
    return _size;
}
