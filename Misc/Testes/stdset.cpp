#include <set>
#include <unordered_set>
#include <iostream>
#include <utility>

using namespace std;

struct vec2 {
    float x;
    float y;

    vec2() {
        this->x = 0;
        this->y = 0;
    }

    vec2(float x, float y) {
        this->x = x;
        this->y = y;
    }

    bool operator==(vec2 const& other) const {
        return (this->x == other.x && this->y == other.y);
    }

    struct Hash {
        bool operator()(vec2 const& vec2) const {
            size_t xHash = hash<float>()(vec2.x);
            size_t yHash = hash<float>()(vec2.y) << 1;

            return xHash ^ yHash;
        }
    };

    void print() const {
        cout << '(' << x << ", " << y << ")\n";
    }
};

typedef pair<int, int> ii;

int main() {
    //unordered_set<vec2, vec2::Hash> set1;
    //set1.reserve(100);

    //vec2 a(2.0f, 5.0f);
    //set1.insert(a);

    //set1.emplace(3.5f, 5.0f);
    //set1.emplace(2.0f, 5.3f);
    //set1.emplace(10.2f, 1.1f);
    //set1.emplace(15.3f, 1.1f);
    //set1.emplace(1.9f, 2.1f);
    //set1.emplace(8.1f, 1.9f);
    //set1.emplace(3.5f, 5.0f);
    //set1.emplace(3.5f, 5.0f);
    //set1.emplace(3.5f, 5.0f);
    //set1.emplace(3.5f, 5.0f);

    //set1.erase( { 1.9f, 2.1f } );

    //cout << set1.size() << '\n';

    //for(vec2 const& v : set1) {
    //    v.print();
    //}
    
    set<ii> set2;

    set2.emplace(2, 1);
    set2.emplace(1, 10);
    set2.emplace(2, 6);
    set2.emplace(1, 2);
    set2.emplace(23, 12);
    set2.emplace(2, 11);
    
    for(ii const& l : set2) {
        cout << '(' << l.first << ", " << l.second << ")\n";
    }

    return 0;
}
