#include <vector>
#include <iostream>

using namespace std;

void vectorState(vector<int> const& v) {
    cout << "Tamanho: " << v.size();
    cout << "\nCapacidade: " << v.capacity();
    cout << "\nElementos:\n";
    
    for(auto const& e : v) {
        cout << e << '\n';
    }

    cout << '\n';
}

int main(void) {
    vector<int> vec(10);

    {
        vector<int>::iterator it;
        int i;

        for(it = vec.begin(), i = 0; it != vec.end(); i++, ++it) {
            *it = i;
        }
    }

    vectorState(vec);

    vec.clear();

    vectorState(vec);
}
