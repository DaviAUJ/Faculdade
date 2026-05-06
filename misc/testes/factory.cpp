#include <iostream>
#include <cmath>
#include <vector>

class vec2nc {
    struct M {
        float posX;
        float posY;
    } m;

    explicit vec2nc(M m) : m(std::move(m)) {}

    public:
    static vec2nc fromCartesian(float posX, float posY);
    static vec2nc fromPolar(float radians, float length);
    
    inline void print(); 
};

[[nodiscard]] vec2nc vec2nc::fromCartesian(float posX, float posY) {
    return vec2nc(
        M {
            .posX = posX,
            .posY = posY,
        }
    );
}

[[nodiscard]] vec2nc vec2nc::fromPolar(float radians, float length) {
    return vec2nc(M {
        .posX = length * cosf(radians),
        .posY = length * sinf(radians),
    });
}

inline void vec2nc::print() {
    std::cout << "{ x: " << m.posX << ", y: " << m.posY << " }\n";  
}

int main() {
    vec2nc a = vec2nc::fromCartesian(5.2f, 10.68f);
    vec2nc b = vec2nc::fromPolar(2.13f, 22.1f);

    a.print();
    b.print();

    std::vector<vec2nc> v(5, vec2nc::fromCartesian(0.0f, 0.0f));

    v[2] = vec2nc::fromPolar(3.1415f, 5.0f);

    for(int i = 0; i < v.size(); i++) {
        v[i].print();
    }
    
    return 0;
}