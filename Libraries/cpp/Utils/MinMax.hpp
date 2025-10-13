#ifndef MIN_MAX
#define MIN_MAX

template<typename T>
T min(T a, T b) {
    return a > b ? b : a;
}

template<typename T>
T max(T a, T b) {
    return a < b ? b : a;
}

template<typename T>
T interval(T lower, T value, T upper) {
    if(value <= lower) {
        return lower;
    }

    if(value >= upper) {
        return upper;
    }

    return value;
}

#endif
