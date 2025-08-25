#include <iostream>
#include <list>
#include <vector>
#include <cstdint>

using namespace std;

template <typename T = uint16_t>
class Graph {
    struct Vertice {
        list<Vertice&> edges;
        T value;
        
        Vertice(T value);
    };

    vector<Vertice> all_vertices;
    
};

int main() {

}
