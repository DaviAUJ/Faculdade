#ifndef DYN_INTEGER
#define DYN_INTEGER

#include "../Aliases/Integers.hpp"

struct DynUint {
private:
    u32* _integer;
    u64  _size; 

public:
    using Primitive = u32;
    using Helper = u64;

    DynUint(u32 value, u8 exp_size);
    DynUint(u64 value, u8 exp_size);
    ~DynUint();

    //void operator+=(const DynUint& other);
    //void operator+=(u64 other);
    void doubleSize(u8 n_times);
    void printHex() const;
    u64  size() const;
    
};

#endif // !DYN_INTEGER
